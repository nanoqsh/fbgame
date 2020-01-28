#include "bird.h"

#include "../engine/render.h"

using namespace fb;

bird::bird(
        glm::vec2 pos,
        glm::vec2 size,
        glm::vec2 collider_size,
        const engine::texture &sprite,
        const game_state &state
) :
        size(size),
        collider_size(collider_size),
        sprite(sprite),
        state(state) {
    this->pos = pos;
}

void bird::draw(const engine::render &r) {
    r.reset_color();
    glm::vec2 half_size = size * 0.5f;
    r.draw(engine::rect(pos - half_size, pos + half_size), sprite);

    if (game_config::get().get_show_colliders()) {
        r.set_color(glm::vec4(0.4f, 1.0f, 0.6f, 0.6f));
        r.draw(get_collider());
    }
}

std::unique_ptr<engine::actor> bird::clone() {
    return std::make_unique<bird>(*this);
}

engine::rect bird::get_collider() const {
    glm::vec2 half_collider_size = collider_size * 0.5f;
    return engine::rect(pos - half_collider_size, pos + half_collider_size);
}

void bird::update(float delta_time) {
    if (state != game_state::RUN) {
        return;
    }

    velocity += gravity * delta_time;
    move(velocity);
}

const glm::vec2 &bird::get_velocity() const {
    return velocity;
}

void bird::set_velocity(const glm::vec2 &v) {
    velocity = v;
}

void bird::add_velocity(const glm::vec2 &v) {
    velocity += v;
}

const glm::vec2 &bird::get_gravity() const {
    return gravity;
}

void bird::set_gravity(const glm::vec2 &g) {
    gravity = g;
}
