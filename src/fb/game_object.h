#pragma once

#include <glm/vec2.hpp>

#include "../engine/texture.h"
#include "../engine/actor.h"
#include "../engine/rect.h"

namespace fb {
    struct game_object : public engine::actor {
        game_object(
                glm::vec2 pos,
                glm::vec2 size,
                glm::vec2 collider_size,
                const engine::texture &sprite
        );

        ~game_object() override = default;

        void draw(const engine::render &r) override;

        void update(double delta_time) override;

        std::unique_ptr<engine::actor> clone() override;

        rect get_collider() const;

        const glm::vec2 &get_velocity() const;

        void set_velocity(const glm::vec2 &v);

        void add_velocity(const glm::vec2 &v);

        float get_weight() const;

        void set_weight(float w);

    private:
        glm::vec2 size;
        glm::vec2 collider_size;
        const engine::texture &sprite;

        glm::vec2 velocity;
        float weight = 0;
    };
}
