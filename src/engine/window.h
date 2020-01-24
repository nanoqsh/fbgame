#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <functional>
#include <utility>

struct input {
    int key;
    int scancode;
    int mode;
};

namespace engine {
    struct render;

    struct window {
        using window_ptr = std::unique_ptr<GLFWwindow, void (*)(GLFWwindow *)>;
        using render_ptr = std::unique_ptr<render>;
        using on_start = std::function<void()>;
        using on_update = std::function<void(const render &, double delta_time)>;
        using on_keypress = std::function<void(window &, const input &)>;

        window(int width, int height, const char *title, bool vsync = true);

        window(window &) = delete;

        window &operator=(window) = delete;

        void run(
                const on_start &start,
                const on_update &update,
                const on_keypress &keypress
        );

        void set_should_close();

        std::pair<int, int> get_framebuffer_size() const;

    private:
        window_ptr window_handler;
        render_ptr render_handler;
        const on_keypress *keypress_fn;
    };
}
