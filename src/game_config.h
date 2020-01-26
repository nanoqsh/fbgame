#pragma once

#include <string>

struct font_config {
    int width;
    int height;
    float size;
    float indent;
};

struct button_textures {
    std::string normal;
    std::string hover;
    std::string active;
};

struct game_config {
    static const game_config &get();

    game_config(game_config &) = delete;

    game_config &operator=(game_config) = delete;

    const std::string &get_vertex_shader() const;

    const std::string &get_fragment_shader() const;

    const std::string &get_font() const;

    const font_config &get_font_config() const;

    const button_textures &get_button_textures() const;

    const std::string &get_bird() const;

    const std::string &get_back() const;

    const std::string &get_tube() const;

    bool get_show_colliders() const;

private:
    game_config();

    std::string vertex_shader;
    std::string fragment_shader;
    std::string font;

    font_config font_data{};
    button_textures buttons{};

    std::string bird;
    std::string back;
    std::string tube;

    bool show_colliders = false;
};
