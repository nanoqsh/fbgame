#include <iostream>

#include "game.h"
#include "game_config.h"

int main() {
    try {
        game fb;
        fb.run();
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    game_config config;
    std::cout << config.get_n() << std::endl;
    std::cout << config.get_key() << std::endl;

    return 0;
}
