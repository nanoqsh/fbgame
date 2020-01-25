#pragma once

#include <glm/vec2.hpp>
#include <functional>
#include <string>
#include "actor.h"
#include "texture.h"
#include "rect.h"

namespace engine {
    struct window;

    enum class button_state {
        NORMAL = 0,
        HOVER = 1,
        ACTIVE = 2
    };

    enum class pos_mode {
        LEFT_BOTTOM = 0,
        CENTER = 1
    };

    struct texture_set {
        const texture &normal;
        const texture &hover;
        const texture &active;
    };

    struct button : public actor {
        using on_click = std::function<void(button &, window &)>;

        button(
                glm::vec2 pos,
                glm::vec2 size,
                std::string &&text,
                texture_set textures,
                pos_mode mode = pos_mode::CENTER
        );

        ~button() override;

        std::unique_ptr<actor> clone() override;

        void draw(const render &r) override;

        void set_state(button_state state);

        button_state get_state() const;

        void set_text_offset(glm::vec2 offset, button_state state);

        rect get_bounds() const;

        void set_on_click(on_click &&click);

        void click(window &w);

        void set_text(std::string &&text);

        const std::string &get_text() const;

    private:
        button_state state = button_state::NORMAL;
        pos_mode mode;

        glm::vec2 size;
        std::string text;
        texture_set textures;

        glm::vec2 text_offsets[3]{};

        on_click on_click_fn;
    };
}
