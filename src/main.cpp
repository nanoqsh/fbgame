#include <iostream>

#include "game.h"

int main() {
    try {
        game g;
        g.run();
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
