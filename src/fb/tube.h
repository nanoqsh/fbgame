#pragma once

#include <glm/vec2.hpp>

#include "../engine/texture.h"
#include "../engine/actor.h"
#include "../engine/rect.h"
#include "../game.h"

namespace fb {
    struct tube : public engine::actor {
        tube(
                glm::vec2 pos,
                glm::vec2 size,
                glm::vec2 collider_size,
                float distance,
                const engine::texture &sprite,
                const game_state& state
        );

        ~tube() override = default;

        void draw(const engine::render &r) override;

        void update(float delta_time) override;

        std::unique_ptr<actor> clone() override;

        std::pair<engine::rect, engine::rect> get_colliders() const;

        bool is_touch(const engine::rect &r) const;

        const glm::vec2 &get_velocity() const;

        void set_velocity(const glm::vec2 &v);

        void add_velocity(const glm::vec2 &v);

        bool get_overcome() const;

        void set_overcome(bool o);

    private:
        glm::vec2 size;
        glm::vec2 collider_size;
        float distance;
        const engine::texture &sprite;
        const game_state& state;

        glm::vec2 velocity = glm::vec2(0.0f);

        bool overcome = false;
    };
}
