#include "game_object.h"

#include "../engine/render.h"

using namespace fb;

void game_object::draw(const engine::render &r) {
    r.reset_color();
    glm::vec2 half_size = size * 0.5f;
    r.draw(rect(pos - half_size, pos + half_size), sprite);

    if (game_config::get().get_show_colliders()) {
        r.set_color(glm::vec4(0.4f, 1.0f, 0.6f, 0.45f));
        r.draw(get_collider());
    }
}

std::unique_ptr<engine::actor> game_object::clone() {
    return std::make_unique<game_object>(*this);
}

game_object::game_object(
        glm::vec2 pos,
        glm::vec2 size,
        glm::vec2 collider_size,
        const engine::texture &sprite
) :
        size(size),
        collider_size(collider_size),
        sprite(sprite),
        velocity(0.0f) {
    this->pos = pos;
}

rect game_object::get_collider() const {
    glm::vec2 half_collider_size = collider_size * 0.5f;
    return rect(pos - half_collider_size, pos + half_collider_size);
}

void game_object::update(double delta_time) {
    velocity -= glm::vec2(0.0f, weight);
    move(velocity * (float) delta_time);
}

const glm::vec2 &game_object::get_velocity() const {
    return velocity;
}

void game_object::set_velocity(const glm::vec2 &v) {
    velocity = v;
}

void game_object::add_velocity(const glm::vec2 &v) {
    velocity += v;
}

float game_object::get_weight() const {
    return weight;
}

void game_object::set_weight(float w) {
    weight = w;
}
