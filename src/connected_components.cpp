#include <cassert>
#include <iostream>

#include "connected_components.hpp"

std::ostream &operator<<(std::ostream &os, const BoundingBox &box)
{
    os << "[" << box.left << ", " << box.right << "] x [" << box.top << ", " << box.bottom << "]";
    return os;
}

size_t Component::area()
{
    return Cells.size();
}

Point2f Component::center()
{
    assert(Cells.size() > 0); // Valid component is never 0
    size_t cx = 0;
    size_t cy = 0;
    for (auto &cell : Cells)
    {
        cx += cell.x;
        cy += cell.y;
    }
    return Point2f{static_cast<float>(cx) / Cells.size(), static_cast<float>(cy) / Cells.size()};
}

BoundingBox Component::bounding_box()
{
    size_t minx = SIZE_MAX;
    size_t maxx = 0;
    size_t miny = SIZE_MAX;
    size_t maxy = 0;
    for (Cell c : Cells)
    {
        if (c.y < miny)
            miny = c.y;
        if (c.y > maxy)
            maxy = c.y;
        if (c.x < minx)
            minx = c.x;
        if (c.x > maxx)
            maxx = c.x;
    }
    return BoundingBox{maxy + 1, miny, minx, maxx + 1}; // Pixel pos is at top left corner, so compensate by adding 1.
}

void dfs(Cell start, size_t id, const BinImg &binimg, ConnectedComponents &cc)
{
    std::vector<Cell> stack{start};
    ComponentsMap &map = cc.Map;
    Component component{};
    while (!stack.empty())
    {
        const Cell cell = stack.back();
        stack.pop_back();
        const size_t x = cell.x;
        const size_t y = cell.y;
        const size_t cid = map.at(x, y);
        if (!(binimg.at(x, y) && cid == 0))
        {
            continue;
        }

        map.at(x, y) = id;
        component.Cells.push_back(cell);
        if (y > 0)
        {
            stack.push_back({x, y - 1});
            if (x > 0)
            {
                stack.push_back({x - 1, y - 1});
            }
            if (x + 1 < map.width())
            {
                stack.push_back({x + 1, y - 1});
            }
        }
        if (y + 1 < map.height())
        {
            stack.push_back({x, y + 1});
            if (cell.x > 0)
            {
                stack.push_back({x - 1, y + 1});
            }
            if (cell.x + 1 < map.width())
            {
                stack.push_back({x + 1, y + 1});
            }
        }
        if (x > 0)
        {
            stack.push_back({x - 1, y});
        }
        if (x + 1 < map.width())
        {
            stack.push_back({x + 1, y});
        }
    }
    cc.Components.push_back(component);
}

ConnectedComponents connected_components(const BinImg &binimg)
{
    ConnectedComponents cc = {ComponentsMap(binimg.width(), binimg.height(), 0), {}};
    ComponentsMap &map = cc.Map;
    cc.Components.push_back({});
    size_t id = 1;
    for (size_t y = 0; y < binimg.height(); ++y)
    {
        for (size_t x = 0; x < binimg.width(); ++x)
        {
            if (binimg.at(x, y) && map.at(x, y) == 0)
            {
                dfs({x, y}, id, binimg, cc);
                id++;
            }
            else
            {
                cc.Components.front().Cells.push_back({x, y});
            }
        }
    }
    return cc;
}
