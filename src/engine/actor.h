#pragma once

#include <glm/vec2.hpp>
#include <memory>

namespace engine {
    struct render;

    struct actor {
        virtual ~actor() = default;

        virtual void draw(const render &r) = 0;

        virtual void update(float delta_time) = 0;

        virtual std::unique_ptr<actor> clone();

        const glm::vec2 &get_pos() const;

        void set_pos(const glm::vec2 &pos);

        void move(const glm::vec2 &offset);

        bool is_visible() const;

        void set_visible(bool visible);

        bool is_enable() const;

        void set_enable(bool enabled);

    protected:
        glm::vec2 pos;
        bool visible = true;
        bool enable = true;
    };
}
