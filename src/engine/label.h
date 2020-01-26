#pragma once

#include <glm/vec2.hpp>
#include <string>

#include "actor.h"

namespace engine {
    struct label : public actor {
        label(glm::vec2 pos, std::string text, bool visible = true);

        ~label() override = default;

        void draw(const render &r) override;

        void update(float delta_time) override;

        std::unique_ptr<actor> clone() override;

        const std::string &get_text() const;

        void set_text(const std::string &t);

    private:
        std::string text;
    };
}
