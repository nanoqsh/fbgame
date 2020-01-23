#pragma once

#include <vector>
#include <GL/glew.h>

namespace engine {
    struct rect_render {
        explicit rect_render();

        ~rect_render();

    private:
        GLuint vbo_handler = 0;
        GLuint vao_handler = 0;
    };
}
