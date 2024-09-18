#define IMAGO_IMPLEMENTATION
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string_view>

#include "connected_components.hpp"
#include "image.hpp"

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
    const auto image = load_image(ppm_path);
    const auto binimg = convert_image(image, [](const RGB24 rgb) { return rgb2gray(rgb) > 10; });

    ConnectedComponents cc = connected_components(binimg);
    for (size_t c = 1; c < cc.Components.size(); c++)
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
