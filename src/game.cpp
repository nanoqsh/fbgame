#include "game.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <random>
#include <vector>

#include "engine/window.h"
#include "engine/render.h"
#include "score.h"
#include "fb/bird.h"
#include "fb/tube.h"

using namespace engine;
using namespace fb;

game::game() :
        score(score::load()),
        config(game_config::get()),
        textures(config.get_button_textures()),
        normal(textures.normal),
        hover(textures.hover),
        active(textures.active),
        back_texture(config.get_back()),
        bird_texture(config.get_bird()),
        tube_texture(config.get_tube())
        {}

void game::run() {
    float screen_width = 700.0f;
    float screen_height = 512.0f;
    float screen_half_width = screen_width * 0.5f;
    float screen_half_height = screen_height * 0.5f;

    float tube_step = 200.0f;
    float tube_height = 320.0f;
    float tube_width = 52.0f;
    float tube_distance = 160.0f;
    float tube_bounds = tube_step * TUBES_NUMBER;
    float tube_left_bound = tube_bounds * -0.5f + screen_half_width;
    float tube_right_bound = tube_bounds * 0.5f + screen_half_width;

    float lower_bound = 20.0f;
    float upper_bound = screen_height - 20.0f;

    float bird_speed = 100.0f;

    float distance_half_range = 60.0f;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-distance_half_range, distance_half_range);

    texture_set button_textures_set{
            normal,
            hover,
            active
    };

    bird bird_object(
            glm::vec2(screen_half_width, 256.0f),
            glm::vec2(36.0f, 36.0f),
            glm::vec2(32.0f, 28.0f),
            bird_texture,
            state
    );
    bird_object.set_gravity(glm::vec2(0.0f, -10.0f));

    std::vector<tube> tubes;
    for (size_t i = 0; i < TUBES_NUMBER; ++i) {
        tube t(
                glm::vec2(screen_half_width + tube_step + tube_step * i, screen_half_height + dis(gen)),
                glm::vec2(tube_width, tube_height),
                glm::vec2(tube_width, tube_height),
                tube_distance,
                tube_texture,
                state
        );
        t.set_velocity(glm::vec2(-bird_speed, 0.0f));

        tubes.push_back(t);
    }

    auto init_game = [&]() {
        bird_object.set_pos(glm::vec2(screen_half_width, 256.0f));
        bird_object.set_velocity(glm::vec2(0.0f));

        size_t i = 0;
        for (tube &t: tubes) {
            t.set_pos(glm::vec2(screen_half_width + tube_step + tube_step * i, screen_half_height + dis(gen)));
            t.set_overcome(false);
            ++i;
        }

        this->current_score = 0;

        state = game_state::RUN;
    };

    init_game();

    window w((int) screen_width, (int) screen_height, "Window");

    w.set_on_start([&](window &w) {
        start_button = std::make_unique<button>(
                glm::vec2(screen_half_width, screen_half_height),
                glm::vec2(128.0f, 32.0f),
                "START",
                button_textures_set
        );
        start_button->set_text_offset(glm::vec2(0.0f, -2.0f), button_state::ACTIVE);

        start_button->set_on_click([this](button &self, window &) {
            self.set_text("run!@#");
        });

        quit_button = std::make_unique<button>(
                glm::vec2(screen_half_width, screen_half_height - 40.0f),
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

        for (tube &t: tubes) {
            w.add_actor(t);
        }

        w.add_actor(bird_object);
    });

    w.set_on_keypress([&](window &w, const input &in) {
        if (in.key == GLFW_KEY_SPACE) {
            bird_object.add_velocity(glm::vec2(0.0f, 9.5f));

            if (state == game_state::GAME_OVER) {
                init_game();
            }
        } else if (in.key == GLFW_KEY_ESCAPE) {
            w.set_should_close();
        }
    });

    w.run([&](window &, const render &r, double delta_time) {

        if (state == game_state::RUN) {
            for (tube &t: tubes) {
                glm::vec2 old_pos = t.get_pos();

                if (old_pos.x < screen_half_width && !t.get_overcome()) {
                    t.set_overcome(true);
                    this->current_score++;
                }

                if (old_pos.x < tube_left_bound) {
                    float dif = old_pos.x - tube_left_bound;
                    t.set_pos(glm::vec2(tube_right_bound + dif, screen_half_height + dis(gen)));
                    t.set_overcome(false);
                }

                if (t.is_touch(bird_object.get_collider())) {
                    state = game_state::GAME_OVER;
                    break;
                }
            }
        }

        float y_pos = bird_object.get_pos().y;
        if (y_pos < lower_bound || y_pos > upper_bound) {
            state = game_state::GAME_OVER;
        }

        r.clear_color(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        r.reset_color();
        r.draw_back(back_texture);

        std::stringstream ss;
        ss << "SCORE: " << current_score;

        if (state == game_state::RUN) {
            r.set_color(glm::vec4(0.0f, 0.0f, 0.0f, 0.5f));
            r.print(glm::vec2(18.0f, screen_height - 32.0f), ss.str().c_str());
            r.reset_color();
            r.print(glm::vec2(18.0f, screen_height - 30.0f), ss.str().c_str());
        } else if (state == game_state::GAME_OVER) {
            r.set_color(glm::vec4(0.0f, 0.0f, 0.0f, 0.5f));
            r.draw(rect(0.0f, 0.0f, screen_width, screen_height));

            r.set_color(glm::vec4(0.0f, 0.0f, 0.0f, 0.5f));
            r.print(glm::vec2(20.0f, screen_half_height - 2.0f), ss.str().c_str());
            r.reset_color();
            r.print(glm::vec2(20.0f, screen_half_height), ss.str().c_str());
        }
    });
}
