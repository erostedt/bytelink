
#include "binimg.hpp"
#include "core.hpp"
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
        std::cout << "  ./connected_components ppm-file" << std::endl;
        return EXIT_FAILURE;
    }

    std::string_view ppm_path{argv[1]};
    std::vector<rgb> rgb_pixels{};
    size_t width, height, maxval;
    if (!load_ppm(ppm_path, rgb_pixels, width, height, maxval))
    {
        std::cout << "Invalid ppm-file." << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<uint8_t> grayscale = rgb2gray(rgb_pixels);
    std::vector<bool> binary = threshold(grayscale, 10);
    BinImg binimg(width, height, binary);
    std::vector<std::vector<bool>> kernel = make_grid(7, 7);
    BinImg ei = eroded(binimg, kernel);
    BinImg di = dilated(binimg, kernel);
    BinImg ci = closed(binimg, kernel);
    BinImg oi = opened(binimg, kernel);
    binimg.save_as_ppm("pre_morph.ppm");
    ei.save_as_ppm("eroded.ppm");
    di.save_as_ppm("dilated.ppm");
    ci.save_as_ppm("closed.ppm");
    oi.save_as_ppm("opened.ppm");
}
