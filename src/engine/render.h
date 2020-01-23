#pragma once

#include <glm/vec4.hpp>
#include <memory>
#include "window.h"
#include "shader.h"

namespace engine {
    struct render {
        using shared_ptr = std::unique_ptr<shader>;

        explicit render(const window &win);

        render(render &) = delete;

        render &operator=(render) = delete;

        void check_errors() const;

        void clear_color(glm::vec4 color) const;

    private:
        shared_ptr shader_handler;
    };
}
