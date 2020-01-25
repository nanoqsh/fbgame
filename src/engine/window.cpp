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
        render_handler(nullptr) {
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

void window::set_on_start(window::on_start &&start) {
    start_fn = start;
}

void window::set_on_keypress(window::on_keypress &&keypress) {
    keypress_fn = keypress;
}

void window::set_on_mouse_move(window::on_mouse_move &&mouse_move) {
    mouse_move_fn = mouse_move;
}

void window::set_on_mouse_click(window::on_mouse_click &&mouse_click) {
    mouse_click_fn = mouse_click;
}

void window::run(window::on_update &&update) {
    glfwSetWindowUserPointer(window_handler.get(), this);

    glfwSetCursorPosCallback(window_handler.get(), mouse_move_callback);
    glfwSetMouseButtonCallback(window_handler.get(), mouse_click_callback);
    glfwSetKeyCallback(window_handler.get(), key_callback);

    double last_time = glfwGetTime();
    double delta_time = 0;

    start_fn(*this);

    while (!glfwWindowShouldClose(window_handler.get())) {
        glfwPollEvents();
        update(*render_handler.get(), delta_time);
        render_actors();
        glfwSwapBuffers(window_handler.get());

        double current_time = glfwGetTime();
        delta_time = current_time - last_time;
        last_time = current_time;
    }

    glfwSetKeyCallback(window_handler.get(), nullptr);
    glfwSetCursorPosCallback(window_handler.get(), nullptr);
    glfwSetMouseButtonCallback(window_handler.get(), nullptr);
}

std::pair<int, int> window::get_framebuffer_size() const {
    int width, height;
    glfwGetFramebufferSize(window_handler.get(), &width, &height);
    return std::pair<int, int>(width, height);
}

void window::add_button(button &b) {
    buttons.emplace_back(b);
    actors.emplace_back(b);
}

void window::render_actors() {
    for (actor &a: actors) {
        if (a.is_enable() && a.is_visible()) {
            a.draw(*render_handler);
        }
    }
}

void window::mouse_move_callback(GLFWwindow *window_ptr, double x_pos, double y_pos) {
    auto *self = static_cast<window *>(glfwGetWindowUserPointer(window_ptr));

    auto[_, height] = self->get_framebuffer_size();
    (void) _;

    auto user_x = (float) x_pos;
    auto user_y = (float) (height - 1) - (float) y_pos;

    for (button &b: self->buttons) {
        if (b.is_enable() && b.get_bounds().intersect_point(user_x, user_y)) {
            b.set_state(button_state::HOVER);
        } else {
            b.set_state(button_state::NORMAL);
        }
    }

    if (self->mouse_move_fn) {
        self->mouse_move_fn(*self, user_x, user_y);
    }
}

void window::mouse_click_callback(GLFWwindow *window_ptr, int mouse_button, int action, int mods) {
    (void) mouse_button;
    (void) mods;

    auto *self = static_cast<window *>(glfwGetWindowUserPointer(window_ptr));

    double x_pos, y_pos;
    glfwGetCursorPos(window_ptr, &x_pos, &y_pos);

    auto[_, height] = self->get_framebuffer_size();
    (void) _;

    auto user_x = (float) x_pos;
    auto user_y = (float) (height - 1) - (float) y_pos;

    for (button &b: self->buttons) {
        if (b.is_enable() && b.get_bounds().intersect_point(user_x, user_y)) {
            if (action == GLFW_RELEASE) {
                b.set_state(button_state::HOVER);
                b.click();
            } else if (action == GLFW_PRESS) {
                b.set_state(button_state::ACTIVE);
            }
        }
    }

    if (action == GLFW_RELEASE) {
        if (self->mouse_click_fn) {
            self->mouse_click_fn(*self, user_x, user_y);
        }
    }
}

void window::key_callback(GLFWwindow *window_ptr, int key, int scancode, int action, int mode) {
    auto *self = static_cast<window *>(glfwGetWindowUserPointer(window_ptr));

    if (action == GLFW_PRESS && self->keypress_fn) {
        self->keypress_fn(*self, input{key, scancode, mode});
    }
}
