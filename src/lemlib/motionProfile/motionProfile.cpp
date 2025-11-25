#include "lemlib/motionProfile/motionProfile.hpp"
#include <climits>
#include <cmath>

lemlib::MotionProfile::MotionProfile(double initVel, double maxVel, double maxAccel, double distToTravel)
    : initVel(initVel),
      maxVel(maxVel),
      accel(maxAccel),
      distToTravel(distToTravel) {}

void lemlib::MotionProfile::initialize() {
    //assuming positive maxVel, initVel, finalVel

    double trialAccelTime = (maxVel - initVel) / accel;
    double trialAccelDist = 0.5 * (accel) * std::pow(trialAccelTime, 2) + initVel * trialAccelTime;

    double trialDecelTime = (maxVel - finalVel) / accel;
    double trialDecelDist = 0.5 * (accel * -1) * std::pow(trialDecelTime, 2) + maxVel * trialDecelTime;
    
    if((trialDecelDist + trialAccelDist) > distToTravel) {
        velReached = 0.5 * std::sqrt(4*accel*distToTravel + 2*(std::pow(finalVel, 2)+std::pow(initVel, 2)));

        accelTime = (velReached - initVel) / accel;
        accelDist = 0.5 * (accel) * std::pow(accelTime, 2) + initVel * accelTime;

        decelTime = (velReached - finalVel) / accel;
        decelDist = 0.5 * (accel * -1) * std::pow(decelTime, 2) + velReached * decelTime;

        totalTime = accelTime + decelTime;
    } else {
        accelTime = trialAccelTime;
        accelDist = trialAccelDist;
        decelTime = trialDecelTime;
        decelDist = trialDecelDist;
        velReached = maxVel;

        double cruiseTime = (distToTravel - accelDist - decelDist) / maxVel;
        totalTime = accelTime + decelTime + cruiseTime;
    }

    return;
}

double lemlib::MotionProfile::velAt(double t) {
    //three cases: accel, cruise, decel

    if (t < accelTime) { //accel
        return initVel + (accel * t); 
    } else if (accelTime < t < (totalTime - decelTime)) { //cruise
        return maxVel;
    } else if (t > (totalTime - decelTime)) { //decel
        return velReached - (accel * (t + decelTime - totalTime));
    }

    return -1; //oopsie daisies
}

double lemlib::MotionProfile::accelAt(double t) {
    if (t < accelTime) { //accel
        return accel;
    } else if (accelTime < t < (totalTime - decelTime)) { //cruise
        return 0;
    } else if (t > (totalTime - decelTime)) { //decel
        return -accel;
    }

    return -INT_MAX; //oopsie daisies
}

double lemlib::MotionProfile::posAt(double t) {
    if (t < accelTime) { //accel
        return (0.5 * accel * std::pow(t, 2)) + (initVel * t);
    } else if (accelTime < t < (totalTime - decelTime)) { //cruise, assuming vel reached
        return accelDist + (maxVel * t);
    } else if (t > (totalTime - decelTime)) { //decel
        return distToTravel - decelDist + (0.5 * (-accel) * std::pow(t, 2) + (velReached * t));
    }

    return -1;
}