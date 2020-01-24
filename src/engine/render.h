#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <memory>
#include "window.h"
#include "shader.h"
#include "rect.h"
#include "rect_render.h"
#include "texture.h"
#include "projection.h"
#include "ui/font.h"

namespace engine {
    struct render {
        using shared_ptr = std::unique_ptr<shader>;
        using rect_render_ptr = std::unique_ptr<rect_render>;
        using projection_ptr = std::unique_ptr<projection>;
        using font_ptr = std::unique_ptr<ui::font>;

        explicit render(const window &win);

        render(render &) = delete;

        render &operator=(render) = delete;

        static void check_errors();

        void clear_color(glm::vec4 color) const;

        void set_color(glm::vec4 color) const;

        void reset_color() const;

        void draw_rect(rect r) const;

        void draw_rect(rect r, const texture &sprite, rect st_map = rect(0.0f, 0.0f, 1.0f, 1.0f)) const;

        void print(glm::vec2 pos, const char *text) const;

    private:
        void init_render();

        shared_ptr shader_handler;
        rect_render_ptr rect_render_handler;
        projection_ptr projection_handler;
        font_ptr font_handler;

        static bool created_opengl;
    };
}
