#version 330 core

layout (location = 2) in vec2 pos;

void main() {
    gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);
}
