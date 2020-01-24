#version 330 core

uniform uint mode;
uniform vec4 rect_color;
uniform sampler2D img;

in vec2 st_map_fs;

out vec4 color;

void main() {
	if (mode == 0u) {
		color = rect_color;
	} else {
		color = rect_color * texture2D(img, st_map_fs);
	}
}
