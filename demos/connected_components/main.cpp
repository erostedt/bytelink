#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string_view>
#include <vector>

#define IMAGO_IMPLEMENTATION
#include "image.hpp"

#include "color.hpp"
#include "connected_components.hpp"


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Invalid usage." << std::endl;
        std::cout << "Intended usage:" << std::endl;
        std::cout << "  ./connected_components ppm-file" << std::endl;
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

    auto bins = std::make_unique<bool[]>(binary.size());
    std::copy(binary.begin(), binary.end(), bins.get());
    BinImg binimg(image.width(), image.height(), std::move(bins));

    ConnectedComponents cc = connected_components(binimg);
    for (size_t c{1}; c < cc.Components.size(); c++)
    {
        Point2f center = cc.Components.at(c).center();
        BoundingBox bb = cc.Components.at(c).bounding_box();
        size_t area = cc.Components.at(c).area();
        std::cout << "Component: " << c << std::endl;
        std::cout << "Center: " << center << std::endl;
        std::cout << "BoundingBox: " << bb << std::endl;
        std::cout << "Area: " << area << std::endl;
        std::cout << "-----------------" << std::endl;
    }
}
