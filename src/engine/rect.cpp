#include "rect.h"

rect::rect(glm::vec2 left_lower, glm::vec2 right_upper) :
        left_lower(left_lower),
        right_upper(right_upper) {
}

bool rect::intersect_point(glm::vec2 point) const {
    return
            left_lower.x >= point.x
            && right_upper.x <= point.x
            && left_lower.y >= point.y
            && right_upper.y <= point.y;
}
