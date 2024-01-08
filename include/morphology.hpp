#pragma once

#include "binimg.hpp"
#include <cstddef>
#include <vector>
std::vector<std::vector<bool>> make_grid(size_t rows, size_t cols);
BinImg eroded(const BinImg &binimg, const std::vector<std::vector<bool>> &strelem);
BinImg dilated(const BinImg &binimg, const std::vector<std::vector<bool>> &strelem);
BinImg closed(const BinImg &binimg, const std::vector<std::vector<bool>> &strelem);
BinImg opened(const BinImg &binimg, const std::vector<std::vector<bool>> &strelem);
