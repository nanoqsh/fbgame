#pragma once

#include <random>

struct random {
    explicit random(float distance_range) :
            gen(rd()),
            dis(distance_range * -0.5, distance_range * 0.5) {}

    float get_value() {
        return dis(gen);
    }

private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
};
