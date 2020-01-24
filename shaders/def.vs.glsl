#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 st_map;

uniform mat4 projection;

out vec2 st_map_fs;

void main() {
    st_map_fs = st_map;
    gl_Position = projection * vec4(pos.x, pos.y, 0.0f, 1.0f);
}
