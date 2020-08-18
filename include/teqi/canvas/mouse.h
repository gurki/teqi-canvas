#pragma once

#include <glm/vec2.hpp>
#include <gl/glew.h>
#include <glfw/glfw3.h>

namespace tq {

class Window;


class Mouse
{
    public:

        enum class Button {
            Left = GLFW_MOUSE_BUTTON_LEFT,
            Middle = GLFW_MOUSE_BUTTON_MIDDLE,
            Right = GLFW_MOUSE_BUTTON_RIGHT,
        };

        Mouse( tq::Window* );

        void lock() const;
        void unlock() const;

        glm::vec2 cursorPosition() const; //  top-left origin
        glm::vec2 relativeCursorPosition() const; //  scaled to [0, 1], relative to current window dimensions
        bool pressed( const Button ) const;
        bool released( const Button ) const;

    private:

        tq::Window* window_ = nullptr;
};


}   //  ::tq