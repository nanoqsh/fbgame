#pragma once

#include <glm/glm.hpp>

namespace engine {
    struct projection {
        projection(float width, float height);

        const glm::mat4 &get_mat() const;

    private:
        glm::mat4 mat;
    };
}
