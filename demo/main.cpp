#include <teqi/canvas.h>


int main( int argc, char* argv[] )
{
    tq::Window window( 1280, 720, "teqi-canvas" );
    tq::Keys keys( &window );
    tq::Mouse mouse( &window );

    while ( ! window.aboutToClose() )
    {
        if ( keys.pressed( GLFW_KEY_ESCAPE ) ) {
            window.close();
        }

        glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        window.finishFrame();
    }
}