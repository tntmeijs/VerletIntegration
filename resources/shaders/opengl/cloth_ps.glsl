#version 460 core

in vec4 vertex_color_from_vs;

out vec4 PixelColor;

void main()
{
    PixelColor = vertex_color_from_vs;
}
