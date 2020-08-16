# teqi-canvas 🖼️
A minimal 3D-graphics starting point

## About
Uses `OpenGL`/`GLEW`/`GLFW` to quickly create a render **window**, load **shaders** and allow basic **mouse** and **keyboard** queries.


```cpp
#include <teqi/canvas.h>


int main( int argc, char* argv[] )
{
    tq::Window window( 1280, 720, "teqi-canvas" );
    tq::Keys keys( &window );

    while ( ! window.aboutToClose() )
    {
        if ( keys.pressed( GLFW_KEY_ESCAPE ) ) {
            window.close();
        }

        glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        window.finishFrame();
    }

    return EXIT_SUCCESS;
}
```