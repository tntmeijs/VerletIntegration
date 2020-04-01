#version 460 core
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 vertex_texture_coordinate;
layout (location = 3) in vec4 vertex_color;

out vec4 vertex_color_from_vs;

void main()
{
    vertex_color_from_vs = vertex_color;
    gl_Position = vec4(vertex_position, 1.0);
}
