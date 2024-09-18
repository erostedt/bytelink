#pragma once
#include <iostream>
#include <vector>

#include "imago.hpp"

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
using ComponentsMap = Image<size_t>;

struct BoundingBox
{
    size_t bottom, top, left, right;
    friend std::ostream &operator<<(std::ostream &os, const BoundingBox &box);
};

struct Component
{
    size_t area();
    Point2f center();
    BoundingBox bounding_box();
    std::vector<Cell> Cells{};
};

struct ConnectedComponents
{
    ComponentsMap Map;
    std::vector<Component> Components;
};

ConnectedComponents connected_components(const BinImg &binimg);
