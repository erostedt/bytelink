#pragma once
#include <cstdint>
#include <vector>

struct rgb
{
    uint8_t r, g, b;
};

std::vector<uint8_t> rgb2gray(const std::vector<rgb> &pixels);
std::vector<bool> threshold(const std::vector<uint8_t> &grayscale, uint8_t thresh);
