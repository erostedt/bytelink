#pragma once
#include <vector>
#include <iostream>

#include "image.hpp"

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

struct Component
{
    size_t area();
    Point2f center();
    BoundingBox bounding_box();
    std::vector<Cell> Cells{};
};

class ComponentsMap
{
  public:
    ComponentsMap(size_t width, size_t height);
    size_t &at(size_t x, size_t y);
    const size_t &at(size_t x, size_t y) const;
    size_t width() const;
    size_t height() const;
    friend std::ostream &operator<<(std::ostream &os, const ComponentsMap &map);

  private:
    size_t m_width;
    size_t m_height;
    std::vector<size_t> m_map;
};

struct ConnectedComponents
{
    ComponentsMap Map;
    std::vector<Component> Components;
};

ConnectedComponents connected_components(const BinImg &binimg);
