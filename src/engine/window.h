#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <functional>
#include <utility>
#include <vector>
#include <functional>

#include "actor.h"
#include "button.h"

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
        using on_start = std::function<void(window &)>;
        using on_update = std::function<void(const render &, double delta_time)>;
        using on_keypress = std::function<void(window &, const input &)>;
        using on_mouse_move = std::function<void(window &, float x, float y)>;

        window(int width, int height, const char *title, bool vsync = true);

        window(window &) = delete;

        window &operator=(window) = delete;

        void set_on_start(on_start &&start);

        void set_on_keypress(on_keypress &&keypress);

        void set_on_mouse_move(on_mouse_move &&mouse_move);

        void run(on_update &&update);

        void set_should_close();

        std::pair<int, int> get_framebuffer_size() const;

        void add_button(button &b);

    private:
        void render_actors();

        window_ptr window_handler;
        render_ptr render_handler;

        on_start start_fn;
        on_keypress keypress_fn;
        on_mouse_move mouse_move_fn;

        std::vector<std::reference_wrapper<button>> buttons;
        std::vector<std::reference_wrapper<actor>> actors;
    };
}
