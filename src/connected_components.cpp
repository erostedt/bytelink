#include <cassert>

#include "connected_components.hpp"

ConnectedComponents::ConnectedComponents(size_t width, size_t height) : Map(ComponentsMap(width, height, 0))
{
}

void ConnectedComponents::add_component(Component &&component)
{
    Components.push_back(component);
}

size_t &ConnectedComponents::id(size_t x, size_t y)
{
    return Map.at(x, y);
}

void ConnectedComponents::add_cell_to_background(Cell cell)
{
    Components.front().add_cell(cell);
}

void dfs(Cell start, size_t id, const BinImg &binimg, ConnectedComponents &cc)
{
    std::vector<Cell> stack{start};
    Component component;
    while (!stack.empty())
    {
        const Cell cell = stack.back();
        stack.pop_back();
        const size_t x = cell.x;
        const size_t y = cell.y;
        const size_t cid = cc.id(x, y);
        if (!(binimg.at(x, y) && cid == 0))
        {
            continue;
        }

        cc.id(x, y) = id;
        component.add_cell(cell);
        if (y > 0)
        {
            stack.push_back({x, y - 1});
            if (x > 0)
            {
                stack.push_back({x - 1, y - 1});
            }
            if (x + 1 < binimg.width())
            {
                stack.push_back({x + 1, y - 1});
            }
        }
        if (y + 1 < binimg.height())
        {
            stack.push_back({x, y + 1});
            if (cell.x > 0)
            {
                stack.push_back({x - 1, y + 1});
            }
            if (cell.x + 1 < binimg.width())
            {
                stack.push_back({x + 1, y + 1});
            }
        }
        if (x > 0)
        {
            stack.push_back({x - 1, y});
        }
        if (x + 1 < binimg.width())
        {
            stack.push_back({x + 1, y});
        }
    }
    cc.add_component(std::move(component));
}

ConnectedComponents connected_components(const BinImg &binimg)
{
    ConnectedComponents cc(binimg.width(), binimg.height());
    cc.add_component({});
    size_t id = 1;
    for (size_t y = 0; y < binimg.height(); ++y)
    {
        for (size_t x = 0; x < binimg.width(); ++x)
        {
            if (binimg.at(x, y) && cc.id(x, y) == 0)
            {
                dfs({x, y}, id, binimg, cc);
                id++;
            }
            else
            {
                cc.add_cell_to_background({x, y});
            }
        }
    }
    return cc;
}
