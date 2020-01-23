#pragma once

#include <glm/vec2.hpp>

struct rect {
    glm::vec2 left_bottom;
    glm::vec2 right_top;

    rect(glm::vec2 left_bottom, glm::vec2 right_top);

    rect(float left, float bottom, float right, float top);

    bool intersect_point(glm::vec2 point) const;
};
