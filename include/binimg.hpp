#pragma once
#include <vector>

class BinImg
{
  public:
    BinImg(size_t width, size_t height, const std::vector<bool> &data);
    BinImg(size_t width, size_t height);
    bool at(size_t x, size_t y) const;
    void set(size_t x, size_t y, bool on);
    size_t width() const;
    size_t height() const;

  private:
    size_t m_width{};
    size_t m_height{};
    std::vector<bool> m_data{};
};
