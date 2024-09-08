#pragma once
#include <filesystem>
#include <string_view>

#include "binimg.hpp"
#include "color.hpp"

namespace fs = std::filesystem;

bool load_ppm(std::string_view path, std::vector<rgb> &out_pixels, size_t &width, size_t &height, size_t &maxval);
void save_as_ppm(const BinImg binary_image, const fs::path &filepath);
