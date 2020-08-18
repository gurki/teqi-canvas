#include "teqi/canvas/window.h"
#include "teqi/canvas/utility.h"

namespace tq {


////////////////////////////////////////////////////////////////////////////////
Window::Window(
    const uint32_t width,
    const uint32_t height,
    std::string_view title,
    const uint8_t samples ) :
    width_( width ),
    height_( height )
{
    if ( ! glfwInit() ) {
        fmt::print( fg_error, "failed to initialize GLFW \n" );
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
        fmt::print( fg_error, "failed to create GLFW Window \n" );
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent( handle_ );
    glfwSetWindowUserPointer( handle_, this );

    glfwSetFramebufferSizeCallback( handle_, resizeCallback );
    glfwSetCursorPosCallback( handle_, mouseCallback );
    glfwSetScrollCallback( handle_, scrollCallback );

    glewExperimental = GL_TRUE;

    if ( GLEW_OK != glewInit() ) {
        fmt::print( fg_error, "failed to initialize GLEW \n" );
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
void Window::clear( const glm::vec3& color ) const {
    glClearColor( color.x, color.y, color.z, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


////////////////////////////////////////////////////////////////////////////////
void Window::checkProperties() const
{
    int width, height;
    glfwGetFramebufferSize( handle_, &width, &height);
    fmt::print( fg_subtle, "framebuffer size: ({}, {}) \n", width, height );

    float xscale, yscale;
    glfwGetWindowContentScale( handle_, &xscale, &yscale);
    fmt::print( fg_subtle, "window content scale: ({}, {}) \n", xscale, yscale );

    const GLubyte* vendor = glGetString( GL_VENDOR );
    fmt::print( fg_subtle, "vendor: {} \n", vendor );

    const GLubyte* renderer = glGetString( GL_RENDERER );
    fmt::print( fg_subtle, "renderer: {} \n", renderer );

    const GLubyte* version = glGetString( GL_VERSION );
    fmt::print( fg_subtle, "opengl version: {} \n", version );

    const GLubyte* glsl = glGetString( GL_SHADING_LANGUAGE_VERSION );
    fmt::print( fg_subtle, "glsl version: {} \n", glsl );
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