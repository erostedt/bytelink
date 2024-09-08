#include <vector>

#include "binimg.hpp"

BinImg::BinImg(size_t width, size_t height, const std::vector<bool> &data) : m_width(width), m_height(height)
{
    m_data = data;
}

BinImg::BinImg(size_t width, size_t height) : m_width(width), m_height(height)
{
    m_data.reserve(width * height);
    for (size_t i{0}; i < width * height; i++)
    {
        m_data.push_back(false);
    }
}

bool BinImg::at(size_t x, size_t y) const
{
    return m_data.at(y * m_width + x);
}

void BinImg::set(size_t x, size_t y, bool on)
{
    m_data[y * m_width + x] = on;
}

size_t BinImg::width() const
{
    return m_width;
}
size_t BinImg::height() const
{
    return m_height;
}
