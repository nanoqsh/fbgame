#pragma once

struct game {
    game();

    game(const game &) = delete;

    game &operator=(game) = delete;

    void run();
};
