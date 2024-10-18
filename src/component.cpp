#include <cassert>

#include "component.hpp"

size_t Component::area() const
{
    return Cells.size();
}

Point2f Component::center() const
{
    assert(area() > 0); // Valid component is never 0
    size_t cx = 0;
    size_t cy = 0;
    for (const auto &cell : Cells)
    {
        cx += cell.x;
        cy += cell.y;
    }
    return {static_cast<float>(cx) / area(), static_cast<float>(cy) / area()};
}

BoundingBox Component::bounding_box() const
{
    size_t minx = SIZE_MAX;
    size_t maxx = 0;
    size_t miny = SIZE_MAX;
    size_t maxy = 0;
    for (Cell c : Cells)
    {
        if (c.y < miny)
        {
            miny = c.y;
        }
        if (c.y > maxy)
        {
            maxy = c.y;
        }
        if (c.x < minx)
        {
            minx = c.x;
        }
        if (c.x > maxx)
        {
            maxx = c.x;
        }
    }
    return {maxy + 1, miny, minx, maxx + 1}; // Pixel pos is at top left corner, so compensate by adding 1.
}

void Component::add_cell(Cell cell)
{
    Cells.push_back(cell);
}
