#pragma once

#include <gl/glew.h>

namespace tq {


////////////////////////////////////////////////////////////////////////////////
inline GLuint createStaticGeometry(
    const std::vector<glm::vec3>& vertices,
    const std::vector<uint32_t>& indices )
{
    const size_t vboSize = vertices.size() * sizeof( glm::vec3 );
    const size_t iboSize = indices.size() * sizeof( uint32_t );

    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    GLuint vbo;
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, vboSize, vertices.data(), GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( glm::vec3 ), ( void* )( 0 ) );
    glEnableVertexAttribArray( 0 );

    GLuint ibo;
    glGenBuffers( 1, &ibo );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, iboSize, indices.data(), GL_STATIC_DRAW );

    glBindVertexArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

    return vao;
}


////////////////////////////////////////////////////////////////////////////////
inline GLuint createQuad()
{
    static const std::vector<glm::vec3> vertices = {
        { 1, 1, 0 },
        { 1,-1, 0 },
        {-1,-1, 0 },
        {-1, 1, 0 }
    };

    static const std::vector<uint32_t> indices = {
        0, 1, 3,
        1, 2, 3
    };

    return createStaticGeometry( vertices, indices );
}


}   //  ::tq