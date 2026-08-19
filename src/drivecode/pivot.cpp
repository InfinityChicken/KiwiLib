#include "pros/misc.h"
#include "drivecode/objects.hpp"

// true direction is going counterclockwise, false direction is going clockwise
// target is an amount in a floating point value
// optional values: rangeMin and rangeMax define the min and max ranges for how far you can be off; if not set, it will be zero
// optional values: velocity is the base value x, velocityMod is the modifier value y

// given a backwards velocity of some float, you can modify it so it skews the motors in opposite sides to have a turn effect
// while going backwards. define the backwards velocity as x, and the skew modifier as y. x_left = -x+y, x_right = -x-y, vice
// versa for right. May need to be tuned later to be more accurate as this is potentially incorrect
void pivot(bool direction, float target, std::optional<float> rangeMax = 3,
                                         std::optional<float> rangeMin = 3,
                                         std::optional<float> velocity = 9000.00,
                                         std::optional<float> velocityMod = 3000.00) {

    float rangeMaxValue = rangeMax.value_or(3.0f);
    float rangeMinValue = rangeMin.value_or(3.0f);
    float velocityValue = velocity.value_or(9000.0f);
    float velocityModValue = velocityMod.value_or(3000.0f);

    if (!(target - rangeMinValue <= imu.get_yaw() && imu.get_yaw() <= target + rangeMaxValue)) {
        if (direction == true) {
            leftMotors.move_voltage(static_cast<int32_t>(-velocityValue + velocityModValue));
            rightMotors.move_voltage(static_cast<int32_t>(-velocityValue - velocityModValue));
        }
        if (direction == false) {
            leftMotors.move_voltage(static_cast<int32_t>(-velocityValue - velocityModValue));
            rightMotors.move_voltage(static_cast<int32_t>(-velocityValue + velocityModValue));
        }
    }

    leftMotors.move_voltage(0);
    rightMotors.move_voltage(0);
}