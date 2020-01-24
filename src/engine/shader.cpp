#include "shader.h"
#include "files.h"
#include "render.h"

#include <string>
#include <stdexcept>

using namespace engine;

static void check_shader_error(GLuint shader_handler) {
    GLint success;
    GLchar info_log[512];
    glGetShaderiv(shader_handler, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader_handler, 512, nullptr, info_log);
        std::string info("shader compilation failed\n");
        info.append(info_log);

        throw std::runtime_error(info);
    }
}

static void check_program_error(GLuint program_handler) {
    GLint success;
    GLchar info_log[512];
    glGetProgramiv(program_handler, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(program_handler, 512, nullptr, info_log);
        std::string info("shader program building failed\n");
        info.append(info_log);

        throw std::runtime_error(info);
    }
}

static GLuint create_shader(const char *file, GLenum shader_type) {
    GLuint shader_handler = glCreateShader(shader_type);
    std::string code = files::read_file(file);
    const char *code_ptr = code.c_str();

    glShaderSource(shader_handler, 1, &code_ptr, nullptr);
    glCompileShader(shader_handler);

    check_shader_error(shader_handler);

    return shader_handler;
}

shader::shader(const char *vs_file, const char *fs_file) {
    GLuint vertex_shader = create_shader(vs_file, GL_VERTEX_SHADER);
    GLuint fragment_shader = create_shader(fs_file, GL_FRAGMENT_SHADER);

    program_handler = glCreateProgram();

    glAttachShader(program_handler, vertex_shader);
    glAttachShader(program_handler, fragment_shader);
    glLinkProgram(program_handler);

    check_program_error(program_handler);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    render::check_errors();
}

shader::~shader() {
    glDeleteProgram(program_handler);
}

void shader::use() const {
    glUseProgram(program_handler);
}

GLint shader::get_index(const char *name) const {
    GLint index = glGetUniformLocation(program_handler, name);

    if (index == -1) {
        std::string message("uniform '");
        message.append(name);
        message.append("' not found in program ");
        message.append(std::to_string(program_handler));

        throw std::runtime_error(message);
    }

    return index;
}

void shader::set_uniform(GLint index, glm::vec4 value) const {
    use();
    glUniform4f(index, value.x, value.y, value.z, value.w);
}

void shader::set_uniform(GLint index, glm::vec3 value) const {
    use();
    glUniform3f(index, value.x, value.y, value.z);
}

void shader::set_uniform(GLint index, glm::vec2 value) const {
    use();
    glUniform2f(index, value.x, value.y);
}

void shader::set_uniform(GLint index, GLfloat value) const {
    use();
    glUniform1f(index, value);
}

void shader::set_uniform(GLint index, GLuint value) const {
    use();
    glUniform1ui(index, value);
}

void shader::set_uniform(GLint index, GLint value) const {
    use();
    glUniform1i(index, value);
}
