#define IMAGO_IMPLEMENTATION
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string_view>

#include "imago.hpp"
#include "morphology.hpp"

const RGBA32 BLACK = {0, 0, 0, 255};
const RGBA32 WHITE = {255, 255, 255, 255};

Image<RGBA32> colorize(const BinImg &binimg)
{
    return convert_image(binimg, [](const bool on) { return on ? WHITE : BLACK; });
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Invalid usage." << std::endl;
        std::cout << "Intended usage:" << std::endl;
        std::cout << "  ./morphology image_file" << std::endl;
        return EXIT_FAILURE;
    }

    std::string_view ppm_path = argv[1];
    const auto image = load_image(ppm_path);

    const auto kernel = make_grid(7, 7);
    const auto binimg = convert_image(image, [](const RGBA32 rgba) { return rgba_to_gray(rgba) > 10; });

    save_image(colorize(binimg), "pre_morph.png");
    save_image(colorize(eroded(binimg, kernel)), "eroded.png");
    save_image(colorize(dilated(binimg, kernel)), "dilated.png");
    save_image(colorize(closed(binimg, kernel)), "closed.png");
    save_image(colorize(opened(binimg, kernel)), "opened.png");
}
