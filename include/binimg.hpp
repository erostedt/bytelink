#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>

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
    void save_as_ppm(std::string_view filepath)
    {
        std::ofstream file(filepath.data());
        if (!file.is_open())
        {
            std::cout << "ERROR: could not open file" << filepath;
            std::exit(1);
        }

        file << "P6\n" << m_width << ' ' << m_height << "\n255\n";

        for (bool on : m_data)
        {
            uint8_t lum = (on) ? 255 : 0;
            file << lum << lum << lum;
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
