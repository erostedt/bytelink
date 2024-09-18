#define IMAGO_IMPLEMENTATION
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string_view>

#include "image.hpp"
#include "morphology.hpp"

const RGB24 BLACK = {0, 0, 0};
const RGB24 WHITE = {255, 255, 255};

Image<RGB24> colorize(const BinImg &binimg)
{
    return convert_image(binimg, [](const bool on) { return on ? WHITE : BLACK; });
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
    const auto image = load_image(ppm_path);

    const auto kernel = make_grid(7, 7);
    const auto binimg = convert_image(image, [](const RGB24 rgb) { return rgb2gray(rgb) > 10; });

    save_image(colorize(binimg), "pre_morph.png");
    save_image(colorize(eroded(binimg, kernel)), "eroded.png");
    save_image(colorize(dilated(binimg, kernel)), "dilated.png");
    save_image(colorize(closed(binimg, kernel)), "closed.png");
    save_image(colorize(opened(binimg, kernel)), "opened.png");
}
