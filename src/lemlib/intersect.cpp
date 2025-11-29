#include "lemlib/intersect.hpp"

namespace lemlib{
    lemlib::Pose intersection(lemlib::Pose p1, lemlib::Pose p2, bool rad) {
        //lines defined by y=tan(theta)(x-initX)+initY
        
        //get numbers
        float x1 = p1.x;
        float y1 = p1.y;
        float theta1 = rad ? p1.theta : degToRad(p1.theta);
        float m1 = tan(theta1);

        float x2 = p2.x;
        float y2 = p2.y;
        float theta2 = rad ? p2.theta : degToRad(p2.theta);
        float m2 = tan(theta2);

        //find x coord of intersection by setting lines equal to each other
        float numerator = y2 - y1 + (m1 * x1) - (m2 * x2);
        float denominator = m1 - m2;
        float xFinal = numerator / denominator;

        //find y coord of intersection by plugging into the first line
        float yFinal = (m1 * (xFinal - x1)) + y1;

        lemlib::Pose output(xFinal, yFinal);

        return output;
    }
}