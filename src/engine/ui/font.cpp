#include "font.h"
#include "../render.h"
#include "../rect.h"

using namespace engine::ui;

font::font() :
        font_texture(game_config::get().get_font().c_str()) {
    fc = game_config::get().get_font_config();

    char_width = 1.0f / (float) fc.width;
    char_height = 1.0f / (float) fc.height;
}

void font::print(const engine::render &r, glm::vec2 pos, const char *text) const {
    int count = 0;
    for (const char *it = text; *it != '\0'; ++it) {
        int n = (int) *it;
        int x = n % fc.width;
        int y = n / fc.width;

        float x_step = (float) count * (fc.indent + fc.size);

        rect char_rect(
                pos.x + x_step,
                pos.y,
                pos.x + fc.size + x_step,
                pos.y + fc.size
        );

        float x_pos = (float) x * char_width;
        float y_pos = (float) y * char_height;

        rect st_map(
                x_pos,
                y_pos,
                x_pos + char_width,
                y_pos + char_height
        );

        r.draw_rect(char_rect, font_texture, st_map);

        ++count;
    }
}
