#include "connected_components.hpp"
#include <cassert>
size_t Component::area()
{
    return Cells.size();
}
Point2f Component::center()
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

BoundingBox Component::bounding_box()
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
    return BoundingBox{maxr + 1, minr, minc, maxc + 1}; // Pixel pos is at top left corner, so compensate by adding 1.
}

void dfs(Cell start, size_t id, const BinImg &binimg, ConnectedComponents &cc)
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
ConnectedComponents connected_components(const BinImg &binimg)
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
