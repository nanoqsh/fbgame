#include <iostream>

#include "engine/render.h"
#include "game_config.h"

using namespace engine;

int main() {
    render r;

    game_config config;
    std::cout << config.get_n() << std::endl;
    std::cout << config.get_key() << std::endl;

    return 0;
}
