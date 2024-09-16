#pragma once
#include <cstdint>
#include <image.hpp>
#include <vector>

std::vector<uint8_t> rgb2gray(const std::vector<RGB24> &pixels);
std::vector<bool> threshold(const std::vector<uint8_t> &grayscale, uint8_t thresh);
