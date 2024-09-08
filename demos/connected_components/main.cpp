#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string_view>
#include <vector>

#include "color.hpp"
#include "connected_components.hpp"
#include "io.hpp"

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
    std::vector<rgb> rgb_pixels;
    size_t width, height, maxval;
    if (!load_ppm(ppm_path, rgb_pixels, width, height, maxval))
    {
        std::cout << "Invalid ppm-file." << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<uint8_t> grayscale = rgb2gray(rgb_pixels);
    std::vector<bool> binary = threshold(grayscale, 10);
    BinImg binimg(width, height, binary);

    ConnectedComponents cc = connected_components(binimg);
    // std::cout << "CC Map: " << std::endl;
    // std::cout << cc.Map << std::endl;
    // std::cout << "-----------------" << std::endl;
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
