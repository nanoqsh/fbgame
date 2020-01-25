#include "button.h"

#include <utility>

#include "render.h"

using namespace engine;

button::button(
        glm::vec2 pos,
        glm::vec2 size,
        std::string text,
        const texture &normal,
        const texture &hover,
        const texture &active
) :
        size(size),
        text(std::move(text)),
        normal(normal),
        hover(hover),
        active(active) {
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
            r.draw_rect(bounds, normal);
            break;
        case button_state::ACTIVE:
            r.draw_rect(bounds, active);
            break;
        case button_state::HOVER:
            r.draw_rect(bounds, hover);
            break;
    }

    glm::vec2 text_size = r.get_font().get_text_size(text.size());
    glm::vec2 text_pos(
            (size.x - text_size.x) * 0.5f,
            (size.y - text_size.y) * 0.5f
    );

    r.print(pos + text_pos + text_offsets[(size_t) state], text.c_str());
}

void button::set_state(button_state s) {
    state = s;
}

void button::set_text_offset(glm::vec2 offset, button_state s) {
    text_offsets[(size_t) s] = offset;
}

rect button::get_bounds() const {
    return rect(pos, pos + size);
}

void button::set_on_press(button::on_press &&press) {
    on_press_fn = press;
}
