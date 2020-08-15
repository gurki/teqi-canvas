#include "teqi/canvas/window.h"
#include <fmt/core.h>

namespace tq {


////////////////////////////////////////////////////////////////////////////////
Window::Window( 
    const GLint width,
    const GLint height, 
    std::string_view title,
    const uint8_t samples ) :
    width_( width ),
    height_( height )
{
    if ( ! glfwInit() ) {
        fmt::print( "failed to initialize GLFW \n" );
        return;
    }    

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_SAMPLES, samples );

    handle_ = glfwCreateWindow( width, height, title.data(), nullptr, nullptr );

    int screenWidth, screenHeight;
    glfwGetFramebufferSize( handle_, &screenWidth, &screenHeight );

    if ( ! handle_ ) {
        fmt::print( "failed to create GLFW Window \n" );
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent( handle_ );
    glfwSetWindowUserPointer( handle_, this );

    glfwSetFramebufferSizeCallback( handle_, resizeCallback );
    glfwSetCursorPosCallback( handle_, mouseCallback );
    glfwSetScrollCallback( handle_, scrollCallback );
    
    // glfwSetInputMode( handle_, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    glfwSetInputMode( handle_, GLFW_STICKY_KEYS, GL_TRUE );
    glewExperimental = GL_TRUE;

    if ( GLEW_OK != glewInit() ) {
        fmt::print( "failed to initialize GLEW \n" );
        return;
    }

    glViewport( 0, 0, screenWidth, screenHeight );
    glfwSwapInterval( 0 );

    checkProperties();
}


////////////////////////////////////////////////////////////////////////////////
Window::~Window() {
    glfwDestroyWindow( handle_ );
    glfwTerminate();
}


////////////////////////////////////////////////////////////////////////////////
void Window::close() const {
    glfwSetWindowShouldClose( handle_, true );
}


////////////////////////////////////////////////////////////////////////////////
bool Window::aboutToClose() const {
    return glfwWindowShouldClose( handle_ );
}


////////////////////////////////////////////////////////////////////////////////
void Window::finishFrame() const {
    glfwSwapBuffers( handle_ );
    glfwPollEvents();
}


////////////////////////////////////////////////////////////////////////////////
void Window::setTitle( const std::string& title ) const {
    glfwSetWindowTitle( handle_, title.c_str() );
}


////////////////////////////////////////////////////////////////////////////////
void Window::checkProperties() const 
{
    int width, height;
    glfwGetFramebufferSize( handle_, &width, &height);
    fmt::print( "framebuffer size width: {}, height: {} \n", width, height );

    float xscale, yscale;
    glfwGetWindowContentScale( handle_, &xscale, &yscale);
    fmt::print( "window content scale x: {}, y: {} \n", xscale, yscale );
}


////////////////////////////////////////////////////////////////////////////////
void Window::onMouseMove( const mouse_callback_t& callback ) {
    mouseCallback_ = callback;
}


////////////////////////////////////////////////////////////////////////////////
void Window::onScroll( const scroll_callback_t& callback ) {
    scrollCallback_ = callback;
}


////////////////////////////////////////////////////////////////////////////////
void Window::onResize( const resize_callback_t& callback ) {
    resizeCallback_ = callback;
}


////////////////////////////////////////////////////////////////////////////////
void Window::resizeCallback( GLFWwindow* handle, int width, int height ) 
{
    glViewport( 0, 0, width, height );

    auto* window = reinterpret_cast<Window*>( glfwGetWindowUserPointer( handle ) );

    if ( window->resizeCallback_ ) {
        window->resizeCallback_( width, height );
    }
}


////////////////////////////////////////////////////////////////////////////////
void Window::mouseCallback( GLFWwindow* handle, double posX, double posY ) 
{
    auto* window = reinterpret_cast<Window*>( glfwGetWindowUserPointer( handle ) );
    
    if ( window->mouseCallback_ ) {
        window->mouseCallback_( posX, posY );
    }
}


////////////////////////////////////////////////////////////////////////////////
void Window::scrollCallback( GLFWwindow* handle, double offsetX, double offsetY ) 
{
    auto* window = reinterpret_cast<Window*>( glfwGetWindowUserPointer( handle ) );

    if ( window->scrollCallback_ ) {
        window->scrollCallback_( offsetX, offsetY );
    }
}


}   //  ::tq