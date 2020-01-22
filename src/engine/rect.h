#pragma once

#include <glm/vec2.hpp>

struct rect {
    glm::vec2 left_lower;
    glm::vec2 right_upper;

    rect(glm::vec2 left_lower, glm::vec2 right_upper);

    bool intersect_point(glm::vec2 point) const;
};
