#pragma once
#include <cstdint>
#include <image.hpp>
#include <vector>

template <typename T, typename UnaryFunction> auto convert_image(const Image<T> &image, const UnaryFunction &function)
{
    using output_type = decltype(function(T{}));
    Image<output_type> output(image.width(), image.height());
    std::transform(image.cbegin(), image.cend(), output.begin(), function);
    return output;
}
uint8_t rgb2gray(RGB24 rgb);
// std::vector<uint8_t> rgb2gray(const std::vector<RGB24> &pixels);
std::vector<bool> threshold(const std::vector<uint8_t> &grayscale, uint8_t thresh);
