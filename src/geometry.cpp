#include "geometry.hpp"

std::ostream &operator<<(std::ostream &os, const BoundingBox &box)
{
    os << "[" << box.left << ", " << box.right << "] x [" << box.top << ", " << box.bottom << "]";
    return os;
}

