#include <cassert>
#include <memory>

template <typename T> class Image
{
  public:
    Image(size_t width, size_t height) : m_width(width), m_height(height)
    {
        m_pixels = std::make_unique<T[]>(width * height);
    }
    Image(size_t width, size_t height, std::unique_ptr<T[]> &&pixels)
        : m_width(width), m_height(height), m_pixels(std::move(pixels))
    {
    }
    const T &at(size_t x, size_t y) const
    {
        return m_pixels[y * m_width + x];
    }

    T &at(size_t x, size_t y)
    {
        return m_pixels[y * m_width + x];
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
    size_t m_width;
    size_t m_height;
    std::unique_ptr<T[]> m_pixels;
};

template <typename T, typename UnaryFunction> auto transform(const Image<T> &input_image, UnaryFunction unary_function)
{
    using output_type = decltype(*UnaryFunction(T{}));
    Image<output_type> output_image(input_image.width(), input_image.height());
    for (size_t y = 0; y < input_image.height(); ++y)
    {
        for (size_t x = 0; y < input_image.width(); ++x)
        {
            output_image.at(x, y) = unary_function(input_image.at(x, y));
        }
    }
    return output_image;
}
