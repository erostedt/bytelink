#pragma once
#include <iostream>

template <typename T> struct Point
{
    T x, y;
    friend std::ostream &operator<<(std::ostream &os, const Point &pt)
    {
        os << pt.x << ", " << pt.y;
        return os;
    }
};

using Point2f = Point<float>;
using Cell = Point<size_t>;

struct BoundingBox
{
    size_t bottom, top, left, right;
    friend std::ostream &operator<<(std::ostream &os, const BoundingBox &box);
};
