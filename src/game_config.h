#pragma once

#include <string>

struct font_config {
    int width;
    int height;
    float size;
    float indent;
};

struct game_config {
    static const game_config &get();

    game_config(game_config &) = delete;

    game_config &operator=(game_config) = delete;

    const std::string &get_vertex_shader() const;

    const std::string &get_fragment_shader() const;

    const std::string &get_font() const;

    const font_config &get_font_config() const;

private:
    game_config();

    std::string vertex_shader;
    std::string fragment_shader;
    std::string font;
    font_config font_data{};
};
