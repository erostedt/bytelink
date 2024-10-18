#pragma once
#include <vector>

#include "imago.hpp"
#include "binimg.hpp"
#include "component.hpp"

using ComponentsMap = Image<size_t>;

class ConnectedComponents
{
public:
    ConnectedComponents(size_t width, size_t height);
    void add_component(Component &&component);
    void add_cell_to_background(Cell cell);
    size_t& id(size_t x, size_t y);
    inline const std::vector<Component>& components() const
    {
        return Components;
    }

private:
    ComponentsMap Map;
    std::vector<Component> Components;
};

ConnectedComponents connected_components(const BinImg &binimg);
