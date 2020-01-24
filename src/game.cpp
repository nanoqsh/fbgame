#include "game.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <cmath>

#include "engine/window.h"
#include "engine/render.h"
#include "engine/rect.h"

using namespace engine;

void game::run() {
    double time = 0.0;
    std::unique_ptr<texture> sky;

    window w(300, 300, "Window");

    w.set_on_start([&sky]() {
        sky = std::make_unique<texture>("./data/1.png");
    });

    w.set_on_keypress([](window &w, const input &in) {
        if (in.key == GLFW_KEY_ESCAPE) {
            w.set_should_close();
        }
    });

    w.run([&time, &sky](const render &r, double delta_time) {
        r.clear_color(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        time += delta_time;

        auto alpha = std::sin((float) time) * 0.5f + 0.5f;
        auto rect_color = glm::vec4(0.5f, alpha, 0.9f, 1.0f);

        auto r1 = rect(50.0f, 50.0f, 250.0f, 250.0f);
        r.draw_rect(r1, rect_color);

        for (int i = 0; i < 12; ++i) {
            float step = 26.f;
            auto r2 = rect(-10.0f + float(i) * step, 40.0f, 10.0f + float(i) * step, 60.0f);

            if (r1.intersect_rect(r2)) {
                r.draw_rect(r2, *sky);
            }
        }
    });
}
