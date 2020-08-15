#include "teqi/canvas/mouse.h"
#include "teqi/canvas/window.h"

#include <glfw/glfw3.h>
#include <cassert>

namespace tq {


////////////////////////////////////////////////////////////////////////////////
Mouse::Mouse( Window* window ) :
    window_( window )
{
    assert( window );
}


////////////////////////////////////////////////////////////////////////////////
void Mouse::lock() const {
    glfwSetInputMode( window_->handle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED );
}


////////////////////////////////////////////////////////////////////////////////
void Mouse::unlock() const {
    glfwSetInputMode( window_->handle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL );
}


////////////////////////////////////////////////////////////////////////////////
glm::vec2 Mouse::cursorPosition() const {
    glm::vec<2, double> pos;
    glfwGetCursorPos( window_->handle(), &pos.x, &pos.y );
    return pos;
}


////////////////////////////////////////////////////////////////////////////////
bool Mouse::pressed( const uint32_t button ) const {
    return glfwGetMouseButton( window_->handle(), button ) == GLFW_PRESS;
}


////////////////////////////////////////////////////////////////////////////////
bool Mouse::released( const uint32_t button ) const {
    return glfwGetMouseButton( window_->handle(), button ) == GLFW_RELEASE;
}


}   //  ::tq