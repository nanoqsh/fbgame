#pragma once

#include "game_config.h"

struct game {
    game();

    game(const game &) = delete;

    game &operator=(game) = delete;

    void run();

private:
    size_t score;
    const game_config &config;
};
