#include "tube.h"

#include "../engine/render.h"

using namespace fb;

tube::tube(
        glm::vec2 pos,
        glm::vec2 size,
        glm::vec2 collider_size,
        float distance,
        const engine::texture &sprite,
        const game_state& state
) :
        size(size),
        collider_size(collider_size),
        distance(distance),
        sprite(sprite),
        state(state) {
    this->pos = pos;
}

void tube::draw(const engine::render &r) {
    float half_distance = distance * 0.5f;
    glm::vec2 half_size = size * 0.5f;

    glm::vec2 pos_bot = glm::vec2(pos.x, pos.y - half_distance - half_size.y);
    glm::vec2 pos_top = glm::vec2(pos.x, pos.y + half_distance + half_size.y);

    engine::rect flip_t = engine::rect(0.0f, 1.0f, 1.0f, 0.0f);

    r.reset_color();
    r.draw(engine::rect(pos_bot - half_size, pos_bot + half_size), sprite);
    r.draw(engine::rect(pos_top - half_size, pos_top + half_size), sprite, flip_t);

    if (game_config::get().get_show_colliders()) {
        auto[bot, top] = get_colliders();

        r.set_color(glm::vec4(1.0f, 0.4f, 0.6f, 0.6f));
        r.draw(bot);
        r.draw(top);
    }
}

void tube::update(float delta_time) {
    if (state != game_state::RUN) {
        return;
    }

    move(velocity * delta_time);
}

std::unique_ptr<engine::actor> tube::clone() {
    return std::make_unique<tube>(*this);
}

std::pair<engine::rect, engine::rect> tube::get_colliders() const {
    float half_distance = distance * 0.5f;
    glm::vec2 half_collider_size = collider_size * 0.5f;

    glm::vec2 pos_bot = glm::vec2(pos.x, pos.y - half_distance - half_collider_size.y);
    glm::vec2 pos_top = glm::vec2(pos.x, pos.y + half_distance + half_collider_size.y);

    return std::pair<engine::rect, engine::rect>(
            engine::rect(pos_bot - half_collider_size, pos_bot + half_collider_size),
            engine::rect(pos_top - half_collider_size, pos_top + half_collider_size)
    );
}

bool tube::is_touch(const engine::rect &r) const {
    auto[bot, top] = get_colliders();
    return bot.intersect_rect(r) || top.intersect_rect(r);
}

const glm::vec2 &tube::get_velocity() const {
    return velocity;
}

void tube::set_velocity(const glm::vec2 &v) {
    velocity = v;
}

void tube::add_velocity(const glm::vec2 &v) {
    velocity += v;
}

bool tube::get_overcome() const {
    return overcome;
}

void tube::set_overcome(bool o) {
    overcome = o;
}
