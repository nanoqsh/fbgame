#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <functional>

struct input {
    int key;
    int scancode;
    int mode;
};

namespace engine {
    struct window {
        using window_ptr = std::unique_ptr<GLFWwindow, void (*)(GLFWwindow *)>;
        using loop_callback = std::function<void()>;
        using keypress_callback = std::function<void(window &, const input &)>;

        window(int width, int height, const char *title);

        window(window &) = delete;

        window &operator=(window) = delete;

        void run(const loop_callback &loop_fn, const keypress_callback &keypress_fn);

        void set_should_close();

    private:
        window_ptr window_handler;
        const keypress_callback *key_callback_function;
    };
}
