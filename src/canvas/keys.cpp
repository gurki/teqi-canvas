#include "teqi/canvas/keys.h"
#include "teqi/canvas/window.h"

#include <glfw/glfw3.h>
#include <cassert>

namespace tq {


////////////////////////////////////////////////////////////////////////////////
Keys::Keys( Window* window ) :
    window_( window )
{
    assert( window );
}


////////////////////////////////////////////////////////////////////////////////
bool Keys::pressed( const uint32_t key ) const {
    return glfwGetKey( window_->handle(), key ) == GLFW_PRESS;
}


////////////////////////////////////////////////////////////////////////////////
bool Keys::released( const uint32_t key ) const {
    return glfwGetKey( window_->handle(), key ) == GLFW_RELEASE;
}


}   //  ::tq