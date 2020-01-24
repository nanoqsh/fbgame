#include <glm/vec4.hpp>
#include "rect_render.h"
#include "render.h"

engine::rect_render::rect_render(GLuint pos_index, GLuint st_map_index) {
    glGenVertexArrays(1, &vao_handler);
    glGenBuffers(1, &vbo_handler);

    glBindVertexArray(vao_handler);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_handler);

    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * 4, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(pos_index);
    glVertexAttribPointer(pos_index, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), nullptr);

    glEnableVertexAttribArray(st_map_index);
    auto *st_map_offset = (GLvoid *) (2 * sizeof(GLfloat));
    glVertexAttribPointer(st_map_index, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), st_map_offset);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    render::check_errors();
}

engine::rect_render::~rect_render() {
    glDeleteVertexArrays(1, &vao_handler);
    glDeleteBuffers(1, &vbo_handler);
}

void engine::rect_render::draw(rect r) const {
    glm::vec4 points[4] =
            {
                    // reflected by y (v)
                    {r.left_bottom.x, r.right_top.y,   0.0f, 0.0f},
                    {r.left_bottom.x, r.left_bottom.y, 0.0f, 1.0f},
                    {r.right_top.x,   r.left_bottom.y, 1.0f, 1.0f},
                    {r.right_top.x,   r.right_top.y,   1.0f, 0.0f}
            };

    glBindVertexArray(vao_handler);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_handler);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindVertexArray(0);

    render::check_errors();
}
