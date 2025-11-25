#include "lemlib/pose.hpp"

namespace lemlib {

class MotionProfile {
    public:
        MotionProfile(double initVel, double maxVel, double maxAccel, double distToTravel);

        void initialize();

        double velAt(double t);
        double accelAt(double t);
        double posAt(double t);

        //initial variables
        double initVel;
        double distToTravel;

        //max variables
        double maxVel;
        double accel;
        
        //final variables
        double finalVel;

        //quick access
        double accelTime;
        double decelTime;
        double totalTime;

        double accelDist;
        double decelDist;

        double velReached;
};
}