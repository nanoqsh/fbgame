#pragma once

struct game {
    game() = delete;

    game(const game &) = delete;

    game &operator=(game) = delete;

    static void run();
};
