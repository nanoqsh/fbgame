#include "rect.h"

rect::rect(glm::vec2 left_bottom, glm::vec2 right_top) :
        left_bottom(left_bottom),
        right_top(right_top) {
}

bool rect::intersect_point(glm::vec2 point) const {
    return
            left_bottom.x >= point.x
            && right_top.x <= point.x
            && left_bottom.y >= point.y
            && right_top.y <= point.y;
}

rect::rect(float left, float bottom, float right, float top) :
        rect(glm::vec2(left, bottom), glm::vec2(right, top)) {}

bool rect::intersect_rect(rect other) const {
    return left_bottom.x < other.right_top.x && right_top.x > other.left_bottom.x &&
           left_bottom.y < other.right_top.y && right_top.y > other.left_bottom.y;
}
