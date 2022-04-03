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

    final_sprite = (
        f"#include <array>\n"
        "\n"
        "namespace Sumo::Sprites{\n"
        f"    std::array<uint8_t, {img.size}> {sprite_name} = {{ {data} }};\n"
        "}\n"
    )

    return final_sprite

def main():
    files_to_process = sys.argv[1:]

    for file_ in files_to_process:
        sprite_name = os.path.splitext(os.path.basename(file_))[0]

        output_header = f"../../src/assets/sprites/{sprite_name}.h"
        print(f"Converting {file_} to {output_header}")

        generated_code = convert_sprite(file_, sprite_name)
        
        with open(output_header, "w") as output_file:
            output_file.write(generated_code)

if __name__ == "__main__":
    main()
