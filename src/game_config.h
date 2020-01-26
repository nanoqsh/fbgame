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

    const std::string &get_title() const;

    const std::string &get_game_over() const;

    const std::string &get_congratulations() const;

    const std::string &get_about() const;

    float get_tube_step() const;

    float get_bird_speed() const;

    float get_jump_power() const;

    float get_gravity() const;

    float get_distance_range() const;

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

    std::string title;
    std::string game_over;
    std::string congratulations;
    std::string about;

    float tube_step = 0.0f;
    float bird_speed = 0.0f;
    float jump_power = 0.0f;
    float gravity = 0.0f;
    float distance_range = 0.0f;
};
