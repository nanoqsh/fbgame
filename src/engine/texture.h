#pragma once

#include <GL/glew.h>
#include <utility>

namespace engine {
    struct texture {
        explicit texture(const char *file);

        ~texture();

        texture(texture &) = delete;

        texture &operator=(texture) = delete;

        void bind(GLint unit = 0) const;

        std::pair<int, int> get_size() const;

    private:
        GLuint texture_handler = 0;
        int width = 0;
        int height = 0;
    };
}
