#include "rect_actor.h"

#include "render.h"

using namespace engine;

rect_actor::rect_actor(rect rct, glm::vec4 color, bool visible) :
        rct(rct),
        color(color) {
    this->visible = visible;
}

void rect_actor::draw(const render &r) {
    r.set_color(color);
    r.draw(rct);
}

void rect_actor::update(float) {}

std::unique_ptr<actor> rect_actor::clone() {
    return std::make_unique<rect_actor>(*this);
}
