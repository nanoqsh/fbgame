#include "label.h"

#include <utility>

#include "render.h"

using namespace engine;

label::label(glm::vec2 pos, std::string text, bool visible) :
        text(std::move(text)) {
    this->pos = pos;
    this->visible = visible;
}

void label::draw(const render &r) {
    glm::vec2 text_half_size = r.get_font().get_text_size(text.size()) * 0.5f;

    r.set_color(glm::vec4(0.0f, 0.0f, 0.0f, 0.5f));
    r.print(pos - text_half_size - glm::vec2(0.0f, 2.0f), text.c_str());
    r.reset_color();
    r.print(pos - text_half_size, text.c_str());
}

void label::update(float) {}

std::unique_ptr<actor> label::clone() {
    return std::make_unique<label>(*this);
}

const std::string &label::get_text() const {
    return text;
}

void label::set_text(const std::string &t) {
    text = t;
}
