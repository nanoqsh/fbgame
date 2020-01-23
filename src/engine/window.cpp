#include "window.h"

#include <stdexcept>
#include "render.h"

using namespace engine;

static window::window_ptr init_window(int width, int height, const char *title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    return window::window_ptr(
            glfwCreateWindow(width, height, title, nullptr, nullptr),
            [](GLFWwindow *) {
                glfwTerminate();
            }
    );
}

window::window(int width, int height, const char *title, bool vsync) :
        window_handler(init_window(width, height, title)),
        render_handler(nullptr),
        key_callback_function(nullptr) {
    if (!window_handler) {
        throw std::runtime_error("failed to create GLFW window");
    }

    glfwMakeContextCurrent(window_handler.get());

    if (vsync) {
        glfwSwapInterval(1);
    }

    render_handler = std::make_unique<render>(*this);
}

void window::set_should_close() {
    glfwSetWindowShouldClose(window_handler.get(), GL_TRUE);
}

void window::run(const window::loop_callback &loop_fn, const window::keypress_callback &keypress_fn) {
    key_callback_function = &keypress_fn;

    glfwSetWindowUserPointer(window_handler.get(), this);

    glfwSetKeyCallback(
            window_handler.get(),
            [](GLFWwindow *window_ptr, int key, int scancode, int action, int mode) {
                auto *self = static_cast<window *>(glfwGetWindowUserPointer(window_ptr));

                if (action == GLFW_PRESS && self->key_callback_function) {
                    (*self->key_callback_function)(*self, input{key, scancode, mode});
                }
            }
    );

    double last_time = glfwGetTime();
    double delta_time = 0;

    while (!glfwWindowShouldClose(window_handler.get())) {
        glfwPollEvents();
        loop_fn(*render_handler.get(), delta_time);
        glfwSwapBuffers(window_handler.get());

        double current_time = glfwGetTime();
        delta_time = current_time - last_time;
        last_time = current_time;
    }

    glfwSetKeyCallback(window_handler.get(), nullptr);
    key_callback_function = nullptr;
}

std::pair<int, int> window::get_framebuffer_size() const {
    int width, height;
    glfwGetFramebufferSize(window_handler.get(), &width, &height);
    return std::pair<int, int>(width, height);
}
