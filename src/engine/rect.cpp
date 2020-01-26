#include "rect.h"

using namespace engine;

rect::rect(glm::vec2 left_bottom, glm::vec2 right_top) :
        left_bottom(left_bottom),
        right_top(right_top) {
}

bool rect::intersect_point(float x, float y) const {
    return left_bottom.x <= x && right_top.x >= x &&
           left_bottom.y <= y && right_top.y >= y;
}

bool rect::intersect_point(glm::vec2 point) const {
    return intersect_point(point.x, point.y);
}

rect::rect(float left, float bottom, float right, float top) :
        rect(glm::vec2(left, bottom), glm::vec2(right, top)) {}

bool rect::intersect_rect(rect other) const {
    return left_bottom.x < other.right_top.x && right_top.x > other.left_bottom.x &&
           left_bottom.y < other.right_top.y && right_top.y > other.left_bottom.y;
}
