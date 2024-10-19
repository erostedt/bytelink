#include <cassert>

#include "morphology.hpp"

StrElem make_grid(size_t width, size_t height)
{
    std::vector<std::vector<bool>> grid;
    for (size_t y = 0; y < height; ++y)
    {
        grid.push_back(std::vector<bool>(width, true));
    }
    return grid;
}

BinImg eroded(const BinImg &binimg, const StrElem &strelem)
{
    const int str_elem_height = static_cast<int>(strelem.size());
    const int str_elem_width = static_cast<int>(strelem.at(0).size());
    assert(str_elem_height % 2 == 1);
    assert(str_elem_width % 2 == 1);

    const auto erode = [&](int x, int y) {
        for (int dy = -str_elem_height / 2; dy <= str_elem_height / 2; dy++)
        {
            for (int dx = -str_elem_width / 2; dx <= str_elem_width / 2; dx++)
            {
                const int ix = x + dx;
                const int iy = y + dy;
                const int sx = str_elem_width / 2 + dx;
                const int sy = str_elem_height / 2 + dy;
                if (!binimg.at(ix, iy) && strelem.at(sy).at(sx))
                {
                    return false;
                }
            }
        }
        return true;
    };

    const int image_height = static_cast<int>(binimg.height());
    const int image_width = static_cast<int>(binimg.width());
    BinImg eroded_image(image_width, image_height);
    for (int y = str_elem_height / 2; y < image_height - str_elem_height / 2; ++y)
    {
        for (int x = str_elem_width / 2; x < image_width - str_elem_width / 2; ++x)
        {
            eroded_image.at(x, y) = erode(x, y);
        }
    }
    return eroded_image;
}

BinImg dilated(const BinImg &binimg, const StrElem &strelem)
{
    const int str_elem_height = static_cast<int>(strelem.size());
    const int str_elem_width = static_cast<int>(strelem.at(0).size());
    assert(str_elem_height % 2 == 1);
    assert(str_elem_width % 2 == 1);

    const auto dilate = [&](int x, int y) {
        for (int dy = -str_elem_height / 2; dy < str_elem_height / 2; dy++)
        {
            for (int dx = -str_elem_width / 2; dx < str_elem_width / 2; dx++)
            {
                const int ix = x + dx;
                const int iy = y + dy;
                const int sx = str_elem_width / 2 + dx;
                const int sy = str_elem_height / 2 + dy;
                if (binimg.at(ix, iy) && strelem.at(sy).at(sx))
                {
                    return true;
                }
            }
        }
        return false;
    };

    const int image_height = static_cast<int>(binimg.height());
    const int image_width = static_cast<int>(binimg.width());
    BinImg dilated_image(image_width, image_height);
    for (int y = str_elem_height / 2; y < image_height - str_elem_height / 2; ++y)
    {
        for (int x = str_elem_width / 2; x < image_width - str_elem_width / 2; ++x)
        {
            dilated_image.at(x, y) = dilate(x, y);
        }
    }
    return dilated_image;
}

BinImg closed(const BinImg &binimg, const StrElem &strelem)
{
    return eroded(dilated(binimg, strelem), strelem);
}

BinImg opened(const BinImg &binimg, const StrElem &strelem)
{
    return dilated(eroded(binimg, strelem), strelem);
}
