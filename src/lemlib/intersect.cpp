#include "lemlib/intersect.hpp"

namespace lemlib{
    lemlib::Pose intersection(lemlib::Pose p1, lemlib::Pose p2, bool rad) {
        //lines defined by y=tan(theta)(x-initX)+initY
        
        //get numbers
        double x1 = p1.x;
        double y1 = p1.y;
        double theta1 = rad ? p1.theta : degToRad(p1.theta);

        double x2 = p2.x;
        double y2 = p2.y;
        double theta2 = rad ? p2.theta : degToRad(p2.theta);

        //find x coord of intersection by setting lines equal to each other
        double numerator = y2 - y1 + (tan(theta1) * x1) - (tan(theta2) * x2);
        double denominator = tan(theta1) - tan(theta2);
        double xFinal = numerator / denominator;

        //find y coord of intersectino by plugging into the first line
        double yFinal = (tan(theta1) * (xFinal - x1)) + y1;

        lemlib::Pose output(xFinal, yFinal);

        return output;
    }
}