#pragma once

#include <GL/glew.h>
#include <utility>
#include <string>

namespace engine {
    struct texture {
        explicit texture(std::string file);

        ~texture();

        texture(texture &) = delete;

        texture &operator=(texture) = delete;

        void bind(GLint unit = 0) const;

        std::pair<int, int> get_size() const;

    private:
        void init() const;

        std::string file;
        mutable bool initialized = false;

        mutable GLuint texture_handler = 0;
        mutable int width = 0;
        mutable int height = 0;
    };
}
