#pragma once

#include <vector>
#include <GL/glew.h>

template <class T>
struct vbo {
    explicit vbo(std::vector<T> vertices) {
        glGenBuffers(1, &vbo_handler);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_handler);

        glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, sizeof(T), GL_FLOAT, GL_FALSE, sizeof(T), (GLvoid*)0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

private:
    GLuint vbo_handler = 0;
};
