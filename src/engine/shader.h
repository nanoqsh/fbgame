#pragma once

#include <GL/glew.h>

namespace engine {
    struct shader {
        shader(const char *vs_file, const char *fs_file);

        ~shader();

        shader(shader &) = delete;

        shader &operator=(shader) = delete;

        void use() const;

    private:
        GLuint program_handler = 0;
    };
}
