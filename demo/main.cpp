#include <teqi/canvas.h>


int main( int argc, char* argv[] )
{
    tq::Window window( 1280, 720, "teqi-canvas" );
    tq::Keys keys( &window );
    tq::Mouse mouse( &window );

    tq::ShaderProgram shader( TQ_CANVAS_ROOT "res/shader/", { "flat.vs", "flat.fs" } );
    shader.use();

    while ( ! window.aboutToClose() )
    {
        if ( keys.pressed( GLFW_KEY_ESCAPE ) ) {
            window.close();
        }

        shader.setVec2( "relMousePos", mouse.relativeCursorPosition() );
        tq::drawQuad( { -1, -1 }, { 2, 2 } );

        window.finishFrame();
    }

    return EXIT_SUCCESS;
}