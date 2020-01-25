#pragma once

#include <glm/vec2.hpp>
#include "texture.h"
#include "../game_config.h"

namespace engine {
    struct render;

    struct font {
        font();

        font(font &) = delete;

        font &operator=(font) = delete;

        void print(const engine::render &r, glm::vec2 pos, const char *text) const;

        glm::vec2 get_text_size(size_t len) const;

    private:
        texture font_texture;

        float char_s = 0.0f;
        float char_t = 0.0f;
        float unit_x = 0.0f;
        float unit_y = 0.0f;

        font_config fc{};
    };
}
