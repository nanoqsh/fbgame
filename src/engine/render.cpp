#include "render.h"
#include "../game_config.h"

#include <GL/glew.h>
#include <stdexcept>
#include <iostream>

using namespace engine;

bool render::created_opengl = false;

render::render(const window &win) {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("failed to initialize GLEW");
    }

    auto[width, height] = win.get_framebuffer_size();
    glViewport(0, 0, width, height);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    created_opengl = true;

    const char *vs = game_config::get().get_vertex_shader().c_str();
    const char *fs = game_config::get().get_fragment_shader().c_str();

    shader_handler = std::make_unique<shader>(vs, fs);
    rect_render_handler = std::make_unique<rect_render>(0, 1);
    projection_handler = std::make_unique<projection>((float) width, (float) height);

    init_render();
    check_errors();
}

void render::clear_color(glm::vec4 color) const {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void render::check_errors() {
    if (!created_opengl) {
        throw std::runtime_error("openGL context not yet configured");
    }

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

    GLint mode = shader_handler->get_index("mode");
    shader_handler->set_uniform(mode, 0u);

    GLint rect_color = shader_handler->get_index("rect_color");
    shader_handler->set_uniform(rect_color, color);

    rect_render_handler->draw(r);

    check_errors();
}

void render::draw_rect(rect r, const texture &sprite) const {
    const GLint SPRITE_UNIT = 0;

    shader_handler->use();

    GLint mode = shader_handler->get_index("mode");
    shader_handler->set_uniform(mode, 1u);

    GLint sprite_index = shader_handler->get_index("img");
    shader_handler->set_uniform(sprite_index, SPRITE_UNIT);

    sprite.bind(SPRITE_UNIT);
    rect_render_handler->draw(r);

    check_errors();
}

void render::init_render() {
    shader_handler->use();

    GLint projection_index = shader_handler->get_index("projection");
    shader_handler->set_uniform(projection_index, projection_handler->get_mat());
}
