#!/usr/bin/env python3
import imageio as iio
import os
import sys


def convert_sprite(imagefile, sprite_name):
    img = iio.imread(imagefile)

    data = ""
    for line in img:
        for pixel in line:
            data += f"{pixel[0]}, {pixel[1]}, {pixel[2]}, "

    dimx, dimy = img.shape[0], img.shape[1]

    final_sprite = (
        "// Autogenerated by convert_sprite.py\n\n"
        f"#ifndef SUMO_{sprite_name.upper()}_HPP\n"
        f"#define SUMO_{sprite_name.upper()}_HPP\n\n"
        "#include <array>\n\n"
        "#include \"engine/sprite.hpp\"\n\n"
        "namespace Sumo::Sprites{\n"
        "// clang-format off\n"
        f"    constexpr std::array<uint8_t, {img.size}> {sprite_name}_data = {{ {data[:-2]} }};\n"
        "// clang-format on\n"
        "\n"
        f"    constexpr Sprite {sprite_name}{{ {dimx}U, {dimy}U, {sprite_name}_data }};"
        "}\n"
        "#endif\n"
    )

    return final_sprite


def main():
    files_to_process = sys.argv[1:]

    for file_ in files_to_process:
        sprite_name = os.path.splitext(os.path.basename(file_))[0]

        output_header = f"../../src/game/assets/sprites/{sprite_name}.hpp"
        print(f"Converting {file_} to {output_header}")

        generated_code = convert_sprite(file_, sprite_name)

        with open(output_header, "w") as output_file:
            output_file.write(generated_code)


if __name__ == "__main__":
    main()
