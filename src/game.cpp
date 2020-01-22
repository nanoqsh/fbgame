#include "game.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/window.h"

using namespace engine;

game::game() = default;

void game::run() {
    window w(400, 400, "Window");
    w.run(
            []() {
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
            },
            [](window &w, const input &in) {
                if (in.key == GLFW_KEY_ESCAPE) {
                    w.set_should_close();
                }
            }
    );
}
