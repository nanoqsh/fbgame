#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 st_map;

out vec2 st_map_fs;

void main() {
    st_map_fs = st_map;
    gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);
}
