#include "lemlib/pid.hpp"
#include "lemlib/util.hpp"
#include "pros/screen.hpp"

namespace lemlib {
PID::PID(float kP, float kI, float kD, float windupRange, bool signFlipReset)
    : kP(kP),
      kI(kI),
      kD(kD),
      windupRange(windupRange),
      signFlipReset(signFlipReset) {}

float PID::update(const float error) {
    //TODO: useWindup
    // calculate integral
    integral += error;

    // if sign changes, reset integral and stop windup
    if ((error < 0 && prevError > 0) || (error > 0 && prevError < 0)) integral = 0;

    // if integral is outside windup range and windup is active, set to 0
    if (std::abs(error) > windupRange) integral = 0;

    // calculate derivative
    float currDerivative = error - prevError;
    float derivative = alpha * currDerivative + (1-alpha) * prevDerivative;
    prevDerivative = currDerivative;
    prevError = error;

    // calculate output
    return error * kP + integral * kI + derivative * kD;
}

void PID::reset() {
    integral = 0;
    prevError = 0;
}
} // namespace lemlib