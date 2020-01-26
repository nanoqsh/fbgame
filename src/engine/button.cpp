#include "button.h"

#include <utility>

#include "render.h"

using namespace engine;

button::button(
        glm::vec2 pos,
        glm::vec2 size,
        std::string text,
        texture_set textures,
        pos_mode mode
) :
        size(size),
        text(std::move(text)),
        textures(textures),
        mode(mode) {
    this->pos = pos;
}

button::~button() = default;

std::unique_ptr<actor> button::clone() {
    return std::make_unique<button>(*this);
}

void button::draw(const render &r) {
    r.reset_color();

    rect bounds = get_bounds();

    switch (state) {
        case button_state::NORMAL:
            r.draw(bounds, textures.normal);
            break;
        case button_state::ACTIVE:
            r.draw(bounds, textures.active);
            break;
        case button_state::HOVER:
            r.draw(bounds, textures.hover);
            break;
    }

    glm::vec2 text_size = r.get_font().get_text_size(text.size());
    glm::vec2 text_pos(
            (size.x - text_size.x) * 0.5f,
            (size.y - text_size.y) * 0.5f
    );

    r.print(bounds.left_bottom + text_pos + text_offsets[(size_t) state], text.c_str());
}

void button::update(float) {}

void button::set_state(button_state s) {
    state = s;
}

button_state button::get_state() const {
    return state;
}

void button::set_text_offset(glm::vec2 offset, button_state s) {
    text_offsets[(size_t) s] = offset;
}

rect button::get_bounds() const {
    if (mode == pos_mode::LEFT_BOTTOM) {
        return rect(pos, pos + size);
    } else {
        glm::vec2 half_size = size * 0.5f;
        return rect(pos - half_size, pos + half_size);
    }
}

void button::set_on_click(const button::on_click &click) {
    on_click_fn = click;
}

void button::click(window &w) {
    if (on_click_fn) {
        on_click_fn(*this, w);
    }
}

void button::set_text(std::string &&t) {
    text = t;
}

const std::string &button::get_text() const {
    return text;
}
