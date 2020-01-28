#include "game.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

#include "engine/window.h"
#include "engine/render.h"
#include "engine/label.h"
#include "engine/rect_actor.h"
#include "fb/bird.h"
#include "fb/tube.h"
#include "score.h"

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
        tube_texture(config.get_tube()),
        rnd(config.get_distance_range()) {}

void game::run() {
    float screen_width = 700.0f;
    float screen_height = 512.0f;
    float screen_half_width = screen_width * 0.5f;
    float screen_half_height = screen_height * 0.5f;

    size_t tubes_number = 8;
    float tube_step = config.get_tube_step();
    float tube_height = 320.0f;
    float tube_width = 52.0f;
    float tube_distance = 160.0f;
    float tube_bounds = tube_step * tubes_number;
    float tube_left_bound = tube_bounds * -0.5f + screen_half_width;
    float tube_right_bound = tube_bounds * 0.5f + screen_half_width;

    float lower_bound = 10.0f;
    float upper_bound = screen_height - 10.0f;

    float bird_speed = config.get_bird_speed();
    float jump_power = config.get_jump_power();
    float gravity = config.get_gravity();

    float button_width = 128.0f;
    float button_height = 32.0f;

    float bird_sprite_width = 36.0f;
    float bird_sprite_height = 36.0f;
    float bird_collider_width = 32.0f;
    float bird_collider_height = 28.0f;

    std::stringstream ss;
    ss << "HIGH SCORE: " << score;
    label high_score_label(glm::vec2(screen_half_width, screen_height - 40.0f), ss.str());
    label about_label(glm::vec2(screen_half_width, 40.0f), config.get_about());

    label current_score_label(glm::vec2(100.0f, screen_height - 40.0f), "SCORE: 0", false);

    label score_label(glm::vec2(screen_half_width, screen_half_height + 40.0f), "");
    score_label.set_enable(false);

    label congratulate_label(glm::vec2(screen_half_width, screen_half_height), "");
    congratulate_label.set_enable(false);
    rect_actor dark(
            rect(0.0f, 0.0f, screen_width, screen_height),
            glm::vec4(0.05f, 0.05f, 0.1f, 0.5f)
    );

    auto set_score = [&]() {
        std::stringstream ss;
        ss << "SCORE: " << current_score;
        current_score_label.set_text(ss.str());
    };

    texture_set button_textures_set{
            normal,
            hover,
            active
    };

    bird bird_object(
            glm::vec2(screen_half_width, screen_half_height),
            glm::vec2(bird_sprite_width, bird_sprite_height),
            glm::vec2(bird_collider_width, bird_collider_height),
            bird_texture,
            state
    );
    bird_object.set_gravity(glm::vec2(0.0f, -gravity));
    bird_object.set_enable(false);

    std::vector<tube> tubes;
    for (size_t i = 0; i < tubes_number; ++i) {
        tube t(
                glm::vec2(0.0f, 0.0f),
                glm::vec2(tube_width, tube_height),
                glm::vec2(tube_width, tube_height),
                tube_distance,
                tube_texture,
                state
        );
        t.set_velocity(glm::vec2(-bird_speed, 0.0f));
        t.set_enable(false);

        tubes.push_back(t);
    }

    button start_button(
            glm::vec2(screen_half_width, screen_half_height),
            glm::vec2(button_width, button_height),
            "START",
            button_textures_set
    );
    start_button.set_text_offset(glm::vec2(0.0f, -2.0f), button_state::ACTIVE);
    start_button.set_enable(true);

    button quit_button(
            glm::vec2(screen_half_width, screen_half_height - 40.0f),
            glm::vec2(button_width, button_height),
            "QUIT",
            button_textures_set
    );
    quit_button.set_text_offset(glm::vec2(0.0f, -2.0f), button_state::ACTIVE);
    quit_button.set_on_click([this](button &, window &w) {
        w.set_should_close();
    });
    quit_button.set_enable(true);

    button restart_button(
            glm::vec2(screen_half_width, screen_half_height - 60.0f),
            glm::vec2(button_width, button_height),
            "RESTART",
            button_textures_set
    );
    restart_button.set_text_offset(glm::vec2(0.0f, -2.0f), button_state::ACTIVE);
    restart_button.set_enable(false);

    auto start_game = [&]() {
        state = game_state::RUN;

        bird_object.set_enable(true);
        bird_object.set_pos(glm::vec2(screen_half_width, screen_half_height));
        bird_object.set_velocity(glm::vec2(0.0f));

        size_t i = 0;
        for (tube &t: tubes) {
            t.set_pos(glm::vec2(
                    screen_half_width + tube_step + tube_step * i,
                    screen_half_height + rnd.get_value()
            ));

            t.set_overcome(false);
            t.set_enable(true);
            ++i;
        }

        current_score = 0;
        set_score();
        current_score_label.set_visible(true);

        dark.set_enable(false);
        restart_button.set_enable(false);
        score_label.set_enable(false);
        congratulate_label.set_enable(false);
        start_button.set_enable(false);
        quit_button.set_enable(false);
        high_score_label.set_enable(false);
        about_label.set_enable(false);
    };

    start_button.set_on_click([&start_game](button &, window &) {
        start_game();
    });
    restart_button.set_on_click([&start_game](button &, window &) {
        start_game();
    });

    auto game_over = [&]() {
        state = game_state::GAME_OVER;

        std::stringstream ss;

        if (current_score > score) {
            score::save(current_score);
            this->score = current_score;

            ss << "New record: " << this->score;
            score_label.set_text(ss.str());
            congratulate_label.set_text(config.get_congratulations());
        } else {
            ss << "Your score: " << current_score;
            score_label.set_text(ss.str());
            congratulate_label.set_text(config.get_game_over());
        }

        score_label.set_enable(true);
        congratulate_label.set_enable(true);
        dark.set_enable(true);
        restart_button.set_enable(true);
    };

    window w((int) screen_width, (int) screen_height, config.get_title().c_str());

    w.set_on_start([&](window &w) {
        for (tube &t: tubes) {
            w.add_actor(t);
        }

        w.add_actor(bird_object);
        w.add_actor(current_score_label);
        w.add_actor(dark);

        w.add_actor(score_label);
        w.add_actor(congratulate_label);
        w.add_actor(high_score_label);
        w.add_actor(about_label);

        w.add_actor(start_button);
        w.add_actor(quit_button);
        w.add_actor(restart_button);
    });

    w.set_on_mouse_click([&](window &, float x, float y) {
        if (state == game_state::RUN) {
            bird_object.add_velocity(glm::vec2(0.0f, jump_power));
        }
    });

    w.set_on_keypress([&](window &w, const input &in) {
        if (in.key == GLFW_KEY_SPACE) {
            bird_object.add_velocity(glm::vec2(0.0f, jump_power));
        } else if (in.key == GLFW_KEY_ESCAPE) {
            w.set_should_close();
        } else if (in.key == GLFW_KEY_ENTER && state == game_state::GAME_OVER) {
            start_game();
        }
    });

    w.set_on_prerender([&](window &, const render &r) {
        r.clear_color(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        r.reset_color();
        r.draw_back(back_texture);
    });

    w.run([&](window &, float delta_time) {
        if (state != game_state::RUN) {
            return;
        }

        for (tube &t: tubes) {
            glm::vec2 old_pos = t.get_pos();

            if (old_pos.x < screen_half_width && !t.get_overcome()) {
                t.set_overcome(true);
                this->current_score++;

                set_score();
            }

            if (old_pos.x < tube_left_bound) {
                float dif = old_pos.x - tube_left_bound;
                t.set_pos(glm::vec2(tube_right_bound + dif, screen_half_height + rnd.get_value()));
                t.set_overcome(false);
            }

            if (t.is_touch(bird_object.get_collider())) {
                game_over();
                return;
            }
        }

        float y_pos = bird_object.get_pos().y;
        if (y_pos < lower_bound || y_pos > upper_bound) {
            game_over();
        }
    });
}
