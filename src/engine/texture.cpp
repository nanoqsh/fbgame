#include "texture.h"
#include "files.h"
#include "render.h"

#include <stdexcept>
#include <soil/SOIL.h>

using namespace engine;

texture::texture(const char *file) {
    files::check_existence(file);

    uint8_t *image = SOIL_load_image(file, &width, &height, nullptr, SOIL_LOAD_RGBA);

    if (!image) {
        std::string message("image loading error: ");
        message.append(SOIL_last_result());

        throw std::runtime_error(message);
    }

    glGenTextures(1, &texture_handler);
    glBindTexture(GL_TEXTURE_2D, texture_handler);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    render::check_errors();
}

texture::~texture() {
    glDeleteTextures(1, &texture_handler);
}

void texture::bind(GLint unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, texture_handler);
}

std::pair<int, int> texture::get_size() const {
    return std::pair<int, int>(width, height);
}
