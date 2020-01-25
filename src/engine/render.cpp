#include "render.h"

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

    this->width = width;
    this->height = height;

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
    font_handler = std::make_unique<font>();

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

void render::reset_color() const {
    shader_handler->use();

    GLint rect_color = shader_handler->get_index("rect_color");
    shader_handler->set_uniform(rect_color, glm::vec4(1.0f));
}

void render::set_color(glm::vec4 color) const {
    shader_handler->use();

    GLint rect_color = shader_handler->get_index("rect_color");
    shader_handler->set_uniform(rect_color, color);
}

void render::draw(rect r) const {
    shader_handler->use();

    GLint mode = shader_handler->get_index("mode");
    shader_handler->set_uniform(mode, 0u);

    rect_render_handler->draw(r);

    check_errors();
}

void render::draw(rect r, const texture &tx, rect st_map) const {
    shader_handler->use();

    GLint mode = shader_handler->get_index("mode");
    shader_handler->set_uniform(mode, 1u);

    GLint sprite_index = shader_handler->get_index("img");
    shader_handler->set_uniform(sprite_index, SPRITE_UNIT);

    tx.bind(SPRITE_UNIT);
    rect_render_handler->draw(r, st_map);

    check_errors();
}

void render::draw(const texture &tx, float factor) const {
    auto[width, height] = tx.get_size();
    draw(rect(0.0, 0.0, width * factor, height * factor), tx);
}

void render::draw_back(const texture &tx) const {
    auto[width, height] = tx.get_size();

    if (width < height) {
        draw(get_bounds(), tx, rect(0.0f, 0.0f, (float) height / (float) width, 1.0f));
    } else {
        draw(get_bounds(), tx, rect(0.0f, 0.0f, 1.0f, (float) width / (float) height));
    }
}

void render::print(glm::vec2 pos, const char *text) const {
    shader_handler->use();

    font_handler->print(*this, pos, text);
}

const font &render::get_font() const {
    return *font_handler;
}

void render::init_render() {
    shader_handler->use();

    GLint projection_index = shader_handler->get_index("projection");
    shader_handler->set_uniform(projection_index, projection_handler->get_mat());

    reset_color();
}

std::pair<int, int> render::get_size() const {
    return std::make_pair(width, height);
}

rect render::get_bounds() const {
    return rect(0.0f, 0.0f, (float) width, (float) height);
}
