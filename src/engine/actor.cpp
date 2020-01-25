#include "actor.h"
#include <stdexcept>

std::unique_ptr<engine::actor> engine::actor::clone() {
    throw std::runtime_error("clone method is not implemented!");
}

const glm::vec2 &engine::actor::get_pos() const {
    return pos;
}

void engine::actor::set_pos(const glm::vec2 &p) {
    pos = p;
}

void engine::actor::move(const glm::vec2 &offset) {
    pos += offset;
}

bool engine::actor::is_visible() const {
    return visible;
}

void engine::actor::set_visible(bool v) {
    visible = v;
}

bool engine::actor::is_enable() const {
    return enable;
}

void engine::actor::set_enable(bool e) {
    enable = e;
}
