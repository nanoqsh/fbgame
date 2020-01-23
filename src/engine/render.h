#pragma once

#include <glm/vec4.hpp>
#include <memory>
#include "window.h"
#include "shader.h"
#include "rect.h"
#include "rect_render.h"

namespace engine {
    struct render {
        using shared_ptr = std::unique_ptr<shader>;
        using rect_render_ptr = std::unique_ptr<rect_render>;

        explicit render(const window &win);

        render(render &) = delete;

        render &operator=(render) = delete;

        void check_errors() const;

        void clear_color(glm::vec4 color) const;

        void draw_rect(rect r) const;

    private:
        shared_ptr shader_handler;
        rect_render_ptr rect_render_handler;
    };
}
