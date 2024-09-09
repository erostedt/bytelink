#pragma once
#include <filesystem>

#include "binimg.hpp"
#include "color.hpp"
#include "image.hpp"

namespace fs = std::filesystem;

Image<rgb> load_image(const fs::path &path);
void save_as_ppm(const BinImg binary_image, const fs::path &filepath);
