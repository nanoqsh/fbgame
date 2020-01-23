#pragma once

struct game {
    game() = default;

    game(const game &) = delete;

    game &operator=(game) = delete;

    void run();
};
