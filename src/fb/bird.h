#pragma once

#include <glm/vec2.hpp>

#include "../engine/texture.h"
#include "../engine/actor.h"
#include "../engine/rect.h"
#include "../game.h"

namespace fb {
    struct bird : public engine::actor {
        bird(
                glm::vec2 pos,
                glm::vec2 size,
                glm::vec2 collider_size,
                const engine::texture &sprite,
                const game_state& state
        );

        ~bird() override = default;

        void draw(const engine::render &r) override;

        void update(double delta_time) override;

        std::unique_ptr<engine::actor> clone() override;

        rect get_collider() const;

        const glm::vec2 &get_velocity() const;

        void set_velocity(const glm::vec2 &v);

        void add_velocity(const glm::vec2 &v);

        const glm::vec2 &get_gravity() const;

        void set_gravity(const glm::vec2 &g);

    private:
        glm::vec2 size;
        glm::vec2 collider_size;
        const engine::texture &sprite;
        const game_state& state;

        glm::vec2 velocity = glm::vec2(0.0f);
        glm::vec2 gravity = glm::vec2(0.0f);
    };
}
