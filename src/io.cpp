#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "binimg.hpp"
#include "color.hpp"

namespace fs = std::filesystem;

bool load_ppm(std::string_view path, std::vector<rgb> &out_pixels, size_t &width, size_t &height, size_t &maxval)
{
    fs::path ppm_path(path);
    assert(fs::exists(ppm_path) || ppm_path.extension().string() == ".ppm");

    std::ifstream file(ppm_path);
    assert(file.is_open());

    std::string format;
    file >> format;
    assert(format == "P3");

    file >> width;
    file >> height;
    file >> maxval;

    const size_t channels = 3;
    uint32_t r, g, b;
    for (size_t i = 0; i < height * width * channels; i += channels)
    {
        file >> r;
        file >> g;
        file >> b;
        out_pixels.push_back({static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b)});
    }
    return true;
}

void save_as_ppm(const BinImg binary_image, const fs::path &filepath)
{
    std::ofstream file(filepath);
    assert(file.is_open());

    file << "P3\n" << binary_image.width() << ' ' << binary_image.height() << "\n255\n";

    for (size_t y = 0; y < binary_image.height(); ++y)
    {
        for (size_t x = 0; x < binary_image.width() - 1; ++x)
        {
            bool on = binary_image.at(x, y);
            uint32_t lum = (on) ? 255 : 0;
            file << lum << ' ' << lum << ' ' << lum << ' ';
        }
        bool on = binary_image.at(binary_image.width() - 1, y);
        uint32_t lum = (on) ? 255 : 0;
        file << lum << ' ' << lum << ' ' << lum << '\n';
    }
}
