#include <teqi/canvas.h>


int main( int argc, char* argv[] )
{
    tq::Window window( 1280, 720, "teqi-canvas" );
    tq::Keys keys( &window );
    tq::Mouse mouse( &window );

    tq::ShaderProgram shader( TQ_CANVAS_ROOT "res/shader/", { "flat.vs", "flat.fs" } );
    const GLuint vao = tq::createQuad();

    while ( ! window.aboutToClose() )
    {
        if ( keys.pressed( GLFW_KEY_ESCAPE ) ) {
            window.close();
        }

        glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        const glm::vec2 relMousePos = mouse.cursorPosition() / window.size();
        shader.setVec2( "relMousePos", relMousePos );
        shader.use();

        glBindVertexArray( vao );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
        glBindVertexArray( 0 );

        window.finishFrame();
    }

    return EXIT_SUCCESS;
}