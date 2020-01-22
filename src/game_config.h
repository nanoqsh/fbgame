#pragma once

#include <string>

struct game_config {
    game_config();

    int get_n() const;

    const std::string &get_key() const;

private:
    int n;
    std::string key;
};
