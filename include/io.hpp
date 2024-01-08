#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
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
    if (!fs::exists(ppm_path) || ppm_path.extension().string() != ".ppm")
        return false;

    std::ifstream file(ppm_path);
    if (!file.is_open())
        return false;

    std::string format;
    file >> format;
    file >> width;
    file >> height;
    file >> maxval;
    size_t channels{3};
    uint8_t r, g, b;
    for (size_t i{0}; i < width * height * channels; i += channels)
    {
        file >> r;
        file >> g;
        file >> b;
        out_pixels.push_back({r, g, b});
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
