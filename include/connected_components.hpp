#pragma once
#include "binimg.hpp"
#include <cassert>
#include <cstddef>
#include <ostream>
#include <vector>

class ComponentsMap
{
  public:
    ComponentsMap(size_t width, size_t height) : m_width(width), m_height(height)
    {
        m_map.reserve(width * height);
        std::fill_n(std::back_inserter(m_map), width * height, 0);
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
    std::vector<size_t> m_map;
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
    float x, y;
    friend std::ostream &operator<<(std::ostream &os, const Point2f &pt)
    {
        os << pt.x << ", " << pt.y;
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

struct Component
{
    size_t area()
    {
        return Cells.size();
    }
    Point2f center()
    {
        assert(Cells.size() > 0); // Valid component is never 0
        size_t cr{0}, cc{0};
        for (auto &cell : Cells)
        {
            cr += cell.r;
            cc += cell.c;
        }
        return Point2f{static_cast<float>(cc) / Cells.size(), static_cast<float>(cr) / Cells.size()};
    }
    BoundingBox bounding_box()
    {
        size_t minr = SIZE_MAX;
        size_t maxr = 0;
        size_t minc = SIZE_MAX;
        size_t maxc = 0;
        for (Cell c : Cells)
        {
            if (c.r < minr)
                minr = c.r;
            if (c.r > maxr)
                maxr = c.r;
            if (c.c < minc)
                minc = c.c;
            if (c.c > maxc)
                maxc = c.c;
        }
        return BoundingBox{maxr + 1, minr, minc,
                           maxc + 1}; // Pixel pos is at top left corner, so compensate by adding 1.
    }
    std::vector<Cell> Cells{};
};

struct ConnectedComponents
{
    ComponentsMap Map;
    std::vector<Component> Components;
};


inline void dfs(Cell start, size_t id, const BinImg &binimg, ConnectedComponents &cc)
{
    std::vector<Cell> stack{start};
    ComponentsMap &map = cc.Map;
    Component component{};
    while (!stack.empty())
    {
        Cell cell = stack.back();
        stack.pop_back();
        size_t r = cell.r;
        size_t c = cell.c;
        size_t cid = map.at(r, c);
        if (!(binimg.at(r, c) && cid == 0))
        {
            continue;
        }

        map.set(r, c, id);
        component.Cells.push_back(cell);
        if (r > 0)
        {
            stack.push_back(Cell{r - 1, c});
            if (c > 0)
                stack.push_back(Cell{r - 1, c - 1});
            if (c + 1 < map.width())
                stack.push_back(Cell{r - 1, c + 1});
        }
        if (r + 1 < map.height())
        {

            stack.push_back(Cell{r + 1, c});
            if (cell.c > 0)
                stack.push_back(Cell{r + 1, c - 1});
            if (cell.c + 1 < map.width())
                stack.push_back(Cell{r + 1, c + 1});
        }
        if (c > 0)
            stack.push_back(Cell{r, c - 1});
        if (c + 1 < map.width())
            stack.push_back(Cell{r, c + 1});
    }
    cc.Components.push_back(component);
}

inline ConnectedComponents connected_components(const BinImg &binimg)
{
    ConnectedComponents cc{ComponentsMap(binimg.width(), binimg.height()), std::vector<Component>{}};
    ComponentsMap &map = cc.Map;
    cc.Components.push_back(Component{});
    size_t id = 1;
    for (size_t row{0}; row < binimg.height(); row++)
    {
        for (size_t col{0}; col < binimg.width(); col++)
        {
            if (binimg.at(row, col) && map.at(row, col) == 0)
            {
                dfs(Cell{row, col}, id, binimg, cc);
                id++;
            }
            else
            {
                cc.Components.front().Cells.push_back({row, col});
            }
        }
    }
    return cc;

}

