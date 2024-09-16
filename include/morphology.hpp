#pragma once
#include <vector>

#include "image.hpp" 

using StrElem = std::vector<std::vector<bool>>;
StrElem make_grid(size_t width, size_t height);
BinImg eroded(const BinImg &binimg, const StrElem &strelem);
BinImg dilated(const BinImg &binimg, const StrElem &strelem);
BinImg closed(const BinImg &binimg, const StrElem &strelem);
BinImg opened(const BinImg &binimg, const StrElem &strelem);
