#define IMAGO_IMPLEMENTATION
#include "image.hpp"

#include "color.hpp"
#include "morphology.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string_view>
#include <vector>

const RGB24 BLACK = {0, 0, 0};
const RGB24 WHITE = {255, 255, 255};

Image<RGB24> colorize(const BinImg& binimg)
{
    auto color = std::make_unique<RGB24[]>(binimg.size());
    auto data = binimg.data();
    for (size_t i = 0; i < binimg.size(); ++i)
    {
         color[i] = (data[i]) ? WHITE : BLACK;
    }
    return Image<RGB24>(binimg.width(), binimg.height(), std::move(color));
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Invalid usage." << std::endl;
        std::cout << "Intended usage:" << std::endl;
        std::cout << "  ./morphology ppm-file" << std::endl;
        return EXIT_FAILURE;
    }

    std::string_view ppm_path = argv[1];
    auto image = load_image(ppm_path);

    std::vector<RGB24> rgb_pixels;
    for (size_t y = 0; y < image.height(); ++y)
    {
        for (size_t x = 0; x < image.width(); ++x)
        {
            rgb_pixels.push_back(image.at(x, y));
        }
    }

    std::vector<uint8_t> grayscale = rgb2gray(rgb_pixels);
    std::vector<bool> binary = threshold(grayscale, 10);
    const auto kernel = make_grid(7, 7);

    auto bins = std::make_unique<bool[]>(binary.size());
    std::copy(binary.begin(), binary.end(), bins.get());
    BinImg binimg(image.width(), image.height(), std::move(bins));

    save_image(colorize(binimg), "pre_morph.png");
    save_image(colorize(eroded(binimg, kernel)), "eroded.png");
    save_image(colorize(dilated(binimg, kernel)), "dilated.png");
    save_image(colorize(closed(binimg, kernel)), "closed.png");
    save_image(colorize(opened(binimg, kernel)), "opened.png");
}
