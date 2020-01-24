#pragma once

#include <glm/vec2.hpp>
#include "../texture.h"
#include "../../game_config.h"

namespace engine {
    struct render;

    namespace ui {
        struct font {
            font();

            font(font &) = delete;

            font &operator=(font) = delete;

            void print(const engine::render &r, glm::vec2 pos, const char *text) const;

        private:
            texture font_texture;

            float char_width = 0.0f;
            float char_height = 0.0f;

            font_config fc{};
        };
    }
}
