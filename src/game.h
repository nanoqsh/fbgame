#pragma once

#include "game_config.h"
#include "engine/texture.h"
#include "engine/button.h"

enum class game_state {
    MENU = 0,
    RUN = 1,
    GAME_OVER = 2
};

struct game {
    game();

    game(const game &) = delete;

    game &operator=(game) = delete;

    void run();

private:
    size_t score;
    size_t current_score = 0;
    const game_config &config;
    game_state state = game_state::RUN;

    button_textures textures;
    engine::texture normal;
    engine::texture hover;
    engine::texture active;
    engine::texture back_texture;
    engine::texture bird_texture;
    engine::texture tube_texture;

    std::unique_ptr<engine::button> start_button;
    std::unique_ptr<engine::button> quit_button;

    const size_t TUBES_NUMBER = 8;
};
