#include "projection.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace engine;

projection::projection(float width, float height) :
        mat(glm::ortho(0.0f, width, 0.0f, height, 0.0f, 1.0f)) {}

const glm::mat4 &projection::get_mat() const {
    return mat;
}
