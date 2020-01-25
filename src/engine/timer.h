#pragma once

#include <GLFW/glfw3.h>

namespace engine {
    struct timer {
        timer() :
            last_time(glfwGetTime()),
            delta_time(0.0)
        {}

        void update() {
            double current_time = glfwGetTime();
            delta_time = current_time - last_time;
            last_time = current_time;
        }

        double get_delta_time() const {
            return delta_time;
        }

    private:
        double last_time;
        double delta_time;
    };
}
