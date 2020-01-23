#include <glm/vec2.hpp>
#include "rect_render.h"

engine::rect_render::rect_render(GLuint index) {
    glGenVertexArrays(1, &vao_handler);
    glGenBuffers(1, &vbo_handler);

    glBindVertexArray(vao_handler);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_handler);

    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

engine::rect_render::~rect_render() {
    glDeleteVertexArrays(1, &vao_handler);
    glDeleteBuffers(1, &vbo_handler);
}

void engine::rect_render::draw(rect r) const {
    glm::vec2 points[4] =
            {
                    {r.left_bottom.x, r.right_top.y},
                    {r.left_bottom.x, r.left_bottom.y},
                    {r.right_top.x, r.left_bottom.y},
                    {r.right_top.x, r.right_top.y}
            };

    glBindVertexArray(vao_handler);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_handler);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindVertexArray(0);
}
