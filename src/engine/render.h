#pragma once

#include <glm/vec4.hpp>
#include "window.h"

namespace engine {
    struct render {
        explicit render(const window &win);

        render(render &) = delete;

        render &operator=(render) = delete;

        void clear_color(glm::vec4 color) const;
    };
}
