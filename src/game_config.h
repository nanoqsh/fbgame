#pragma once

#include <string>

struct game_config {
    game_config(game_config &) = delete;

    game_config &operator=(game_config) = delete;

    const std::string &get_key() const;

    const std::string &get_vertex_shader() const;

    const std::string &get_fragment_shader() const;

    static const game_config &get();

private:
    game_config();

    std::string key;

    std::string vertex_shader;
    std::string fragment_shader;
};
