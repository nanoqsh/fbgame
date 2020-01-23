#include "rect_render.h"

engine::rect_render::rect_render() {
    glGenVertexArrays(1, &vao_handler);
    glGenBuffers(1, &vbo_handler);

    glBindVertexArray(vao_handler);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_handler);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

engine::rect_render::~rect_render() {
    glDeleteVertexArrays(1, &vao_handler);
    glDeleteBuffers(1, &vbo_handler);
}
