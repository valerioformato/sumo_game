#!/usr/bin/env python3
import imageio as iio
import os
import sys


def convert_sprite(filename, sprite_name):
    img = iio.imread(filename)

    print(f"shape: {img.shape}, size: {img.size}")
    dimx, dimy, colors = img.shape[0], img.shape[1], img.shape[2]

    data = ""
    for line in img:
        for pixel in line:
            if colors == 3:
                data += f"ColorI32 {{ {pixel[0]}, {pixel[1]}, {pixel[2]} }}, "
            elif colors == 4:
                data += f"ColorI32 {{ {pixel[0]}, {pixel[1]}, {pixel[2]}, {pixel[3]} }}, "

    final_sprite = (
        "// Autogenerated by convert_sprite.py\n\n"
        f"#ifndef SUMO_{sprite_name.upper()}_HPP\n"
        f"#define SUMO_{sprite_name.upper()}_HPP\n\n"
        "#include <array>\n\n"
        "#include \"engine/sprite.hpp\"\n\n"
        "namespace Sumo::Sprites{\n"
        "// clang-format off\n"
        f"    constexpr std::array<ColorI32, {dimx*dimy}> {sprite_name}_data = {{ {data[:-2]} }};\n"
        "// clang-format on\n"
        "\n"
        f"    constexpr StaticSprite {sprite_name}{{ {{ {dimx}U, {dimy}U }}, {sprite_name}_data }};"
        "}\n"
        "#endif\n"
    )

    return final_sprite


def convert_sprite_gif(filename, sprite_name):
    img = iio.get_reader(filename)

    frames = img.get_length()
    print(f"sprite has {frames} frames")

    data = ""
    for frame in img:
        print(f"shape: {frame.shape}, size: {frame.size}")
        dimx, dimy, colors = frame.shape[0], frame.shape[1], frame.shape[2]
        for line in frame:
            for pixel in line:
                if colors == 3:
                    data += f"ColorI32 {{ {pixel[0]}, {pixel[1]}, {pixel[2]} }}, "
                elif colors == 4:
                    data += f"ColorI32 {{ {pixel[0]}, {pixel[1]}, {pixel[2]}, {pixel[3]} }}, "

    final_sprite = (
        "// Autogenerated by convert_sprite.py\n\n"
        f"#ifndef SUMO_{sprite_name.upper()}_HPP\n"
        f"#define SUMO_{sprite_name.upper()}_HPP\n\n"
        "#include <array>\n\n"
        "#include \"engine/sprite.hpp\"\n\n"
        "namespace Sumo::Sprites{\n"
        "// clang-format off\n"
        f"    constexpr std::array<ColorI32, {dimx*dimy*frames}> {sprite_name}_data = {{ {data[:-2]} }};\n"
        "// clang-format on\n"
        "\n"
        f"    constexpr AnimatedSprite {sprite_name}{{ {{ {dimx}U, {dimy}U }}, {frames}U, {sprite_name}_data }};"
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

        generated_code = None
        if os.path.splitext(file_)[1] == ".gif":
            generated_code = convert_sprite_gif(file_, sprite_name)
        else:
            generated_code = convert_sprite(file_, sprite_name)

        with open(output_header, "w") as output_file:
            output_file.write(generated_code)


if __name__ == "__main__":
    main()
