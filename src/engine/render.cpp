#include "render.h"

#include <GL/glew.h>
#include <stdexcept>

using namespace engine;

render::render(const window &win) {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("failed to initialize GLEW");
    }

    auto[width, height] = win.get_framebuffer_size();
    glViewport(0, 0, width, height);
}

void render::clear_color(glm::vec4 color) const {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}
