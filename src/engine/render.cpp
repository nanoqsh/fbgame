#include "render.h"
#include "../game_config.h"

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const char* vs = game_config::get().get_vertex_shader().c_str();
    const char* fs = game_config::get().get_fragment_shader().c_str();

    shader_handler = std::make_unique<shader>(vs, fs);

    rect_render_handler = std::make_unique<rect_render>(2);

    check_errors();
}

void render::clear_color(glm::vec4 color) const {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void render::check_errors() const {
    GLenum err;

    while ((err = glGetError()) != GL_NO_ERROR) {
        const char *err_message;

        switch (err) {
            case GL_INVALID_ENUM:
                err_message = "invalid enum";
                break;
            case GL_INVALID_VALUE:
                err_message = "invalid value";
                break;
            case GL_INVALID_OPERATION:
                err_message = "invalid operation";
                break;
            case GL_STACK_OVERFLOW:
                err_message = "stack overflow";
                break;
            case GL_STACK_UNDERFLOW:
                err_message = "stack underflow";
                break;
            case GL_OUT_OF_MEMORY:
                err_message = "out of memory";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                err_message = "invalid framebuffer operation";
                break;
            default:
                err_message = "undefined error";
                break;
        }

        throw std::runtime_error(err_message);
    }
}

void render::draw_rect(rect r, glm::vec4 color) const {
    shader_handler->use();
    shader_handler->set_uniform(shader_handler->get_index("rect_color"), color);
    rect_render_handler->draw(r);

    check_errors();
}
