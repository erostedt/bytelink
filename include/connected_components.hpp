#pragma once
#include "binimg.hpp"
#include <cstddef>
#include <ostream>
#include <vector>

class ComponentsMap
{
  public:
    ComponentsMap(size_t width, size_t height) : m_width(width), m_height(height)
    {
        m_map.reserve(width * height);
        for (size_t i{0}; i < width * height; i++)
        {
            m_map.push_back(0);
        }
    }
    size_t at(size_t row, size_t col) const
    {
        return m_map.at(row * m_width + col);
    }
    void set(size_t row, size_t col, size_t cls)
    {
        m_map.at(row * m_width + col) = cls;
    }
    size_t width() const
    {
        return m_width;
    }
    size_t height() const
    {
        return m_height;
    }
    friend std::ostream &operator<<(std::ostream &os, const ComponentsMap &map)
    {
        for (size_t r{0}; r < map.height(); r++)
        {
            for (size_t c{0}; c < map.width(); c++)
            {
                os << map.at(r, c) << " ";
            }
            os << std::endl;
        }
        return os;
    }

  private:
    size_t m_width{};
    size_t m_height{};
    std::vector<size_t> m_map{};
};

struct Cell
{
    size_t r, c;
    friend std::ostream &operator<<(std::ostream &os, const Cell &cell)
    {
        os << cell.r << ", " << cell.c;
        return os;
    }
};

struct Point2f
{
    float r, c;
    friend std::ostream &operator<<(std::ostream &os, const Point2f &pt)
    {
        os << pt.r << ", " << pt.c;
        return os;
    }
};

struct BoundingBox
{
    size_t bottom, top, left, right;
    friend std::ostream &operator<<(std::ostream &os, const BoundingBox &box)
    {
        os << "[" << box.left << ", " << box.right << "] x [" << box.top << ", " << box.bottom << "]";
        return os;
    }
};

struct ConnectedComponents
{
    static size_t component_area(const std::vector<Cell> &cluster);
    static Point2f component_center(const std::vector<Cell> &cluster);
    static BoundingBox component_bounding_box(const std::vector<Cell> &cluster);

    ComponentsMap Map;
    std::vector<std::vector<Cell>> Components;
};

ConnectedComponents connected_components(const BinImg &binimg);
