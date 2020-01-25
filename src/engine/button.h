#pragma once

#include <glm/vec2.hpp>
#include <functional>
#include <string>
#include "actor.h"
#include "texture.h"
#include "rect.h"

namespace engine {
    enum class button_state {
        NORMAL = 0,
        HOVER = 1,
        ACTIVE = 2
    };

    struct button : public actor {
        using on_press = std::function<void()>;

        button(
                glm::vec2 pos,
                glm::vec2 size,
                std::string text,
                const texture &normal,
                const texture &hover,
                const texture &active
        );

        ~button() override;

        std::unique_ptr<actor> clone() override;

        void draw(const render &r) override;

        void set_state(button_state state);

        void set_text_offset(glm::vec2 offset, button_state state);

        rect get_bounds() const;

        void set_on_press(on_press&& press);

    private:
        button_state state = button_state::NORMAL;
        glm::vec2 size;
        std::string text;
        const texture &normal;
        const texture &hover;
        const texture &active;

        glm::vec2 text_offsets[3]{};

        on_press on_press_fn;
    };
}
