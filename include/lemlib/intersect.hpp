#include "lemlib/pose.hpp"
#include "lemlib/util.hpp"

namespace lemlib {
    /**
     * @brief Finds the intersection points of pose lines defined by their points and angles
     * @param p1 first point
     * @param p2 second pooint
     * @param rad whether or not pose angle is in radians, false by default
     * @endcode
    */
    lemlib::Pose intersection(lemlib::Pose p1, lemlib::Pose p2, bool rad = false);
}