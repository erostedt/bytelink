#include <algorithm>
#include <vector>

#include "color.hpp"
#include "image.hpp"

uint8_t rgb2gray(RGB24 rgb)
{
    uint32_t red = static_cast<uint32_t>(rgb.r);
    uint32_t green = static_cast<uint32_t>(rgb.g);
    uint32_t blue = static_cast<uint32_t>(rgb.b);
    return (299u * red + 587u * green + 114u * blue) / 1000u;
}

/*
std::vector<uint8_t> rgb2gray(const std::vector<RGB24> &pixels)
{
    std::vector<uint8_t> grayscale;
    for (const RGB24 &pixel : pixels)
    {
        grayscale.push_back((299u * static_cast<uint32_t>(pixel.r) + 587u * static_cast<uint32_t>(pixel.g) +
                             114u * static_cast<uint32_t>(pixel.b)) /
                            1000u);
    }
    return grayscale;
}
*/

std::vector<bool> threshold(const std::vector<uint8_t> &grayscale, uint8_t thresh)
{
    std::vector<bool> bin{};
    for (uint8_t lum : grayscale)
    {
        bin.push_back(lum > thresh);
    }
    return bin;
}
