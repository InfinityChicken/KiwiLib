#include <cmath>
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/logger/logger.hpp"
#include "lemlib/timer.hpp"
#include "lemlib/util.hpp"
#include "pros/misc.hpp"

void lemlib::Chassis::moveToPoint(float x, float y, int timeout, MoveToPointParams params, bool async) {
    params.earlyExitRange = fabs(params.earlyExitRange);
    this->requestMotionStart();
    // were all motions cancelled?
    if (!this->motionRunning) return;
    // if the function is async, run it in a new task
    if (async) {
        pros::Task task([&]() { moveToPoint(x, y, timeout, params, false); });
        this->endMotion();
        pros::delay(10); // delay to give the task time to start
        return;
    }

    // reset PIDs and exit conditions
    lateralPID.reset();
    lateralLargeExit.reset();
    lateralSmallExit.reset();
    angularPID.reset();

    // initialize vars used between iterations
    Pose lastPose = getPose();
    distTraveled = 0;
    Timer timer(timeout);
    // bool close = false; //TODO: close fully doesn't do anything
    float prevLateralOut = 0; // previous lateral power
    float prevAngularOut = 0; // previous angular power
    const int compState = pros::competition::get_status();
    std::optional<bool> prevSide = std::nullopt;

    // calculate target pose in standard form
    Pose target(x, y);
    target.theta = lastPose.angle(target); //TODO: theta value changed to starting error between current position and target

    // main loop
    while (!timer.isDone() && ((!lateralSmallExit.getExit() && !lateralLargeExit.getExit())) && //TODO: removed the || !close condition in while loop
           this->motionRunning) {
        // update position
        const Pose pose = getPose(true, true);

        // update distance traveled
        distTraveled += pose.distance(lastPose);
        lastPose = pose;

        // calculate distance to the target point
        const float distTarget = pose.distance(target);

        //TODO: i don't think there's a point to this

        // // check if the robot is close enough to the target to start settling
        // if (distTarget < 7.5 && close == false) {
        //     close = true;
        //     params.maxSpeed = fmax(fabs(prevLateralOut), 60);
        // }

        // motion chaining
        const bool side =
            (pose.y - target.y) * -sin(target.theta) <= (pose.x - target.x) * cos(target.theta) + params.earlyExitRange;
        if (prevSide == std::nullopt) prevSide = side;
        const bool sameSide = side == prevSide;
        // exit if close
        if (!sameSide && params.minSpeed != 0) break;
        prevSide = side;

        // calculate error
        const float adjustedRobotTheta = params.forwards ? pose.theta : pose.theta + M_PI;
        const float angularError = angleError(adjustedRobotTheta, pose.angle(target)); //*: angular error calculated as error between current heading and the angle between the current position and the target which makes sense
        const float lateralError = pose.distance(target) * cos(angleError(pose.theta, pose.angle(target))); //TODO: added a const here because why wouldn't there be one
        //* lateral is actually LONGITUDINAL error which makes sense

        // update exit conditions
        lateralSmallExit.update(lateralError);
        lateralLargeExit.update(lateralError);

        // get output from PIDs
        float lateralOut = lateralPID.update(lateralError);
        float angularOut = angularPID.update(radToDeg(angularError));
        // if (close) angularOut = 0; //TODO: YO DUDE.

        //TODO: may need to add a hard restriction since we don't have the close variable anymore
        // apply restrictions on angular speed
        angularOut = std::clamp(angularOut, -params.maxSpeed, params.maxSpeed);
        angularOut = slew(angularOut, prevAngularOut, angularSettings.slew);

        // apply restrictions on lateral speed
        lateralOut = std::clamp(lateralOut, -params.maxSpeed, params.maxSpeed);
        // constrain lateral output by max accel
        // but not for decelerating, since that would interfere with settling
        // if (!close) lateralOut = slew(lateralOut, prevLateralOut, lateralSettings.slew); //TODO: another close thing

        // prevent moving in the wrong direction //TODO: gang what does this do (need to disable since could mess with settling since no more close variabnle)
        // if (params.forwards && !close) lateralOut = std::fmax(lateralOut, 0);
        // else if (!params.forwards && !close) lateralOut = std::fmin(lateralOut, 0);

        // constrain lateral output by the minimum speed
        if (params.forwards && lateralOut < fabs(params.minSpeed) && lateralOut > 0) lateralOut = fabs(params.minSpeed);
        if (!params.forwards && -lateralOut < fabs(params.minSpeed) && lateralOut < 0)
            lateralOut = -fabs(params.minSpeed);

        // update previous output
        prevAngularOut = angularOut;
        prevLateralOut = lateralOut;

        infoSink()->debug("Angular Out: {}, Lateral Out: {}", angularOut, lateralOut);

        // ratio the speeds to respect the max speed
        float leftPower = lateralOut + angularOut;
        float rightPower = lateralOut - angularOut;
        const float ratio = std::max(std::fabs(leftPower), std::fabs(rightPower)) / params.maxSpeed;
        if (ratio > 1) {
            leftPower /= ratio;
            rightPower /= ratio;
        }

        // move the drivetrain
        drivetrain.leftMotors->move(leftPower);
        drivetrain.rightMotors->move(rightPower);

        // delay to save resources
        pros::delay(10);
    }

    // stop the drivetrain
    drivetrain.leftMotors->move(0);
    drivetrain.rightMotors->move(0);
    // set distTraveled to -1 to indicate that the function has finished
    distTraveled = -1;
    this->endMotion();
}