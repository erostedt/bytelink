#pragma once
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

class BinImg
{
  public:
    BinImg(size_t width, size_t height, const std::vector<bool> &data) : m_width(width), m_height(height)
    {
        m_data = data;
    }
    BinImg(size_t width, size_t height) : m_width(width), m_height(height)
    {
        m_data.reserve(width * height);
        for (size_t i{0}; i < width * height; i++)
        {
            m_data.push_back(false);
        }
    }

    bool at(size_t row, size_t col) const
    {
        return m_data[row * m_width + col];
    }

    void set(size_t row, size_t col, bool on)
    {
        m_data[row * m_width + col] = on;
    }

    void save_as_ppm(const fs::path& filepath)
    {
        std::ofstream file(filepath);
        assert(file.is_open());

        file << "P3\n" << m_width << ' ' << m_height << "\n255\n";

        for (size_t y = 0; y < m_height; ++y)
        {
            for (size_t x = 0; x < m_width-1; ++x)
            {
                bool on = at(x, y);
                uint32_t lum = (on) ? 255 : 0;
                file << lum << ' ' << lum << ' ' << lum << ' ';
            }
            bool on = at(m_width-1, y);
            uint32_t lum = (on) ? 255 : 0;
            file << lum << ' ' << lum << ' ' << lum << '\n';
        }

    }
    size_t width() const
    {
        return m_width;
    }
    size_t height() const
    {
        return m_height;
    }

  private:
    size_t m_width{};
    size_t m_height{};
    std::vector<bool> m_data{};
};
