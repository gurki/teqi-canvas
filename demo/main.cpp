#include <teqi/canvas.h>


int main( int argc, char* argv[] )
{
    tq::Window window( 1280, 720, "teqi-canvas" );
    tq::Keys keys( &window );
    tq::Mouse mouse( &window );

    tq::Texture texture( TQ_CANVAS_ROOT "res/textures/leaf.jpg" );
    tq::ShaderProgram shader( TQ_CANVAS_ROOT "res/shaders/", { "flat.vs", "flat.fs" } );

    texture.use();
    shader.use();

    while ( ! window.aboutToClose() )
    {
        if ( keys.pressed( GLFW_KEY_ESCAPE ) ) {
            window.close();
        }

        shader.setVec2( "mouseRel", mouse.relativeCursorPosition() );
        shader.setBool( "mouseDown", mouse.pressed( tq::Mouse::Button::Left ) );
        tq::drawUnitQuad();

        window.finishFrame();
    }

    return EXIT_SUCCESS;
}