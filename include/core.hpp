#pragma once
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

struct rgb
{
    uint8_t r, g, b;
};

static inline bool load_ppm(std::string_view path, std::vector<rgb> &out_pixels, size_t &width, size_t &height,
                            size_t &maxval)
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

static inline std::vector<uint8_t> rgb2gray(const std::vector<rgb> &pixels)
{
    std::vector<uint8_t> grayscale{};
    for (const rgb &pixel : pixels)
    {
        grayscale.push_back((299u * static_cast<uint32_t>(pixel.r) + 587u * static_cast<uint32_t>(pixel.g) +
                             114u * static_cast<uint32_t>(pixel.b)) /
                            1000u);
    }
    return grayscale;
}

static inline std::vector<bool> threshold(const std::vector<uint8_t> &grayscale, uint8_t thresh)
{
    std::vector<bool> bin{};
    for (uint8_t lum : grayscale)
    {
        bin.push_back(lum > thresh);
    }
    return bin;
}
