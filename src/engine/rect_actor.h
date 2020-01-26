#pragma once

#include <glm/vec4.hpp>

#include "actor.h"
#include "rect.h"

namespace engine {
    struct rect_actor : public engine::actor {
        rect_actor(rect rct, glm::vec4 color, bool visible = true);

        ~rect_actor() override = default;

        void draw(const render &r) override;

        void update(float delta_time) override;

        std::unique_ptr<actor> clone() override;

    private:
        rect rct;
        glm::vec4 color;
    };
}
