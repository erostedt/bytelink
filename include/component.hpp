#pragma once
#include <vector>

#include "geometry.hpp"

class Component
{
  public:
    void add_cell(Cell cell);
    size_t area() const;
    Point2f center() const;
    BoundingBox bounding_box() const;

  private:
    std::vector<Cell> Cells;
};
