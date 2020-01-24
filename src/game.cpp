#include "game.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <memory>
#include <cmath>

#include "engine/window.h"
#include "engine/render.h"
#include "engine/rect.h"

using namespace engine;

void game::run() {
    double time = 0.0;
    std::unique_ptr<texture> sky;

    window w(600, 600, "Window");
    w.run(
            [&sky]() {
                sky = std::make_unique<texture>("./data/1.png");
            },
            [&time, &sky](const render &r, double delta_time) {
                r.clear_color(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

                time += delta_time;

                auto alpha = std::sin((float) time) * 0.5f + 0.5f;
                auto rect_color = glm::vec4(0.5f, alpha, 0.9f, 1.0f);

                r.draw_rect(rect(-0.4f, -0.4f, 0.6f, 0.6f), rect_color);
                r.draw_rect(rect(-0.6f, -0.6f, 0.0f, 0.0f), *sky);
            },
            [](window &w, const input &in) {
                if (in.key == GLFW_KEY_ESCAPE) {
                    w.set_should_close();
                }
            }
    );
}
