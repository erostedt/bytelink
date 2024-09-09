
#include "binimg.hpp"
#include "color.hpp"
#include "io.hpp"
#include "morphology.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string_view>
#include <vector>

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

    std::vector<rgb> rgb_pixels;
    for (size_t y = 0; y < image.height(); ++y)
    {
        for (size_t x = 0; x < image.width(); ++x)
        {
            rgb_pixels.push_back(image.at(x, y));
        }
    }

    std::vector<uint8_t> grayscale = rgb2gray(rgb_pixels);
    std::vector<bool> binary = threshold(grayscale, 10);
    BinImg binimg(image.width(), image.height(), binary);
    const auto kernel = make_grid(7, 7);

    save_as_ppm(binimg, "pre_morph.ppm");
    save_as_ppm(eroded(binimg, kernel), "eroded.ppm");
    save_as_ppm(dilated(binimg, kernel), "dilated.ppm");
    save_as_ppm(closed(binimg, kernel), "closed.ppm");
    save_as_ppm(opened(binimg, kernel), "opened.ppm");
}
