#pragma once

#include <gl/glew.h>
#include <glfw/glfw3.h>

#include <string_view>
#include <functional>

namespace tq {


class Window
{
    public:

        Window(
            const GLint width,
            const GLint height,
            std::string_view title = "window",
            const uint8_t samples = 8
        );

        ~Window();

        Window( const Window& ) = delete;
        Window& operator=( const Window& ) = delete;
        Window( Window&& ) = delete;
        Window& operator=( Window&& ) = delete;

        void close() const;
        void finishFrame() const;
        void setTitle( const std::string& title ) const;

        GLFWwindow* handle() const { return handle_; }
        [[nodiscard]] uint32_t width() const { return width_; }
        [[nodiscard]] uint32_t height() const { return height_; }
        [[nodiscard]] bool aboutToClose() const;

        using mouse_callback_t = std::function<void( const double, const double )>;
        using scroll_callback_t = std::function<void( const double, const double )>;
        using resize_callback_t = std::function<void( const int, const int )>;

        void onMouseMove( const mouse_callback_t& );
        void onScroll( const scroll_callback_t& );
        void onResize( const resize_callback_t& );
        void checkProperties() const;

    private:

        static void resizeCallback( GLFWwindow*, int width, int height );
        static void mouseCallback( GLFWwindow*, double posX, double posY );
        static void scrollCallback( GLFWwindow*, double offsetX, double offsetY );

        uint32_t width_ {};
        uint32_t height_ {};
        GLFWwindow* handle_ { nullptr };
        mouse_callback_t mouseCallback_ {};
        scroll_callback_t scrollCallback_ {};
        resize_callback_t resizeCallback_ {};
};


}   //  ::tq