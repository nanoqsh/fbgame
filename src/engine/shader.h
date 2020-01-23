#pragma once

#include <GL/glew.h>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace engine {
    struct shader {
        shader(const char *vs_file, const char *fs_file);

        ~shader();

        shader(shader &) = delete;

        shader &operator=(shader) = delete;

        void use() const;

        GLint get_index(const char *name) const;

        void set_uniform(GLint index, glm::vec4 value) const;

        void set_uniform(GLint index, glm::vec3 value) const;

        void set_uniform(GLint index, glm::vec2 value) const;

        void set_uniform(GLint index, float value) const;

    private:
        GLuint program_handler = 0;
    };
}
