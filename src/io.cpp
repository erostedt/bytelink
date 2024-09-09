#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "binimg.hpp"
#include "color.hpp"
#include "image.hpp"

namespace fs = std::filesystem;

Image<rgb> load_image(const fs::path &path)
{
    int width, height, components;
    uint8_t *bytes = stbi_load(path.c_str(), &width, &height, &components, STBI_rgb);
    assert(bytes != NULL);
    size_t size = width * height;
    std::unique_ptr<rgb[]> pixels = std::make_unique<rgb[]>(size);
    memcpy(pixels.get(), bytes, size * sizeof(rgb));
    Image<rgb> image(width, height, std::move(pixels));
    free(bytes);
    return image;
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
