#include "game.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "engine/window.h"
#include "engine/render.h"
#include "engine/button.h"
#include "score.h"
#include "fb/game_object.h"

using namespace engine;
using namespace fb;

game::game() :
        score(score::load()),
        config(game_config::get()) {}

void game::run() {
    texture back(config.get_back());

    button_textures textures = config.get_button_textures();
    texture normal(textures.normal);
    texture hover(textures.hover);
    texture active(textures.active);

    texture_set button_textures_set{
            normal,
            hover,
            active
    };

    std::unique_ptr<button> start_button;
    std::unique_ptr<button> quit_button;

    texture bird_texture(config.get_bird());
    game_object bird(
            glm::vec2(300.0f, 256.0f),
            glm::vec2(36.0f, 36.0f),
            glm::vec2(36.0f, 36.0f),
            bird_texture
    );

    bird.set_weight(8.0f);

    int factor = 2;
    window w(300 * factor, 256 * factor, "Window");

    w.set_on_start([&](window &w) {
        start_button = std::make_unique<button>(
                glm::vec2(300.0f, 256.0f),
                glm::vec2(128.0f, 32.0f),
                "START",
                button_textures_set
        );
        start_button->set_text_offset(glm::vec2(0.0f, -2.0f), button_state::ACTIVE);

        start_button->set_on_click([this](button &self, window &) {
            self.set_text("run!@#");

            size_t new_score = 27;
            this->score = new_score;
            score::save(new_score);
        });

        quit_button = std::make_unique<button>(
                glm::vec2(300.0f, 216.0f),
                glm::vec2(128.0f, 32.0f),
                "QUIT",
                button_textures_set
        );
        quit_button->set_text_offset(glm::vec2(0.0f, -2.0f), button_state::ACTIVE);

        quit_button->set_on_click([this](button &, window &w) {
            w.set_should_close();
        });

        start_button->set_enable(false);
        quit_button->set_enable(false);

        w.add_actor(*start_button);
        w.add_actor(*quit_button);

        w.add_actor(bird);
    });

    w.set_on_keypress([&](window &w, const input &in) {
        if (in.key == GLFW_KEY_SPACE) {
            bird.add_velocity(glm::vec2(0.0f, 300.0f));
        }

        if (in.key == GLFW_KEY_ESCAPE) {
            w.set_should_close();
        }
    });

    w.run([&](window &, const render &r, double delta_time) {
        r.clear_color(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        r.reset_color();
        r.draw_back(back);

        std::stringstream ss;
        ss << "HIGH SCORE: " << score;
        r.set_color(glm::vec4(0.0f, 0.0f, 0.0f, 0.5f));
        r.print(glm::vec2(18.0f, 472.0f), ss.str().c_str());
        r.reset_color();
        r.print(glm::vec2(18.0f, 474.0f), ss.str().c_str());
    });
}
