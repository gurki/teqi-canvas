#pragma once

#include <gl/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <fmt/color.h>

namespace tq {


////////////////////////////////////////////////////////////////////////////////
inline GLuint createGeometryBuffer(
    const std::vector<glm::vec3>& vertices,
    const std::vector<glm::vec2>& coords,
    const std::vector<uint32_t>& indices,
    GLuint& vao,
    GLuint& vbo,
    GLuint& ibo,
    const GLuint usageHint = GL_STATIC_DRAW )
{
    const size_t vertSize = vertices.size() * sizeof( glm::vec3 );
    const size_t coordSize = coords.size() * sizeof( glm::vec2 );
    const size_t vboSize = vertSize + coordSize;
    const size_t iboSize = indices.size() * sizeof( uint32_t );

    //  vertex array

    if ( ! vao ) glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    //  vertex buffer

    if ( ! vbo ) glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, vboSize, NULL, usageHint );

    glBufferSubData( GL_ARRAY_BUFFER, 0, vertSize, vertices.data() );
    glBufferSubData( GL_ARRAY_BUFFER, vertSize, coordSize, coords.data() );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( glm::vec3 ), ( void* )( 0 ) );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, sizeof( glm::vec2 ), ( void* )( vertSize ) );

    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );

    //  index buffer

    if ( ! ibo ) glGenBuffers( 1, &ibo );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, iboSize, indices.data(), usageHint );

    glBindVertexArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

    return vao;
}


////////////////////////////////////////////////////////////////////////////////
inline void drawQuad(
    const glm::vec2& pos,
    const glm::vec2& size,
    const float depth = 0.f )
{
    static GLuint vao = 0, vbo = 0, ibo = 0;

    static const std::vector<uint32_t> indices = {
        0, 1, 3,
        1, 2, 3
    };

    static const std::vector<glm::vec2> coords = {
        { 0, 0 },
        { 1, 0 },
        { 1, 1 },
        { 0, 1 }
    };

    const std::vector<glm::vec3> vertices = {
        { pos.x, pos.y, depth },
        { pos.x + size.x, pos.y, depth },
        { pos.x + size.x, pos.y + size.y, depth },
        { pos.x, pos.y + size.y, depth }
    };

    createGeometryBuffer( vertices, coords, indices, vao, vbo, ibo );

    glBindVertexArray( vao );
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
    glBindVertexArray( 0 );
}


////////////////////////////////////////////////////////////////////////////////
inline void drawUnitQuad()
{
    static GLuint vao = 0, vbo = 0, ibo = 0;

    static const std::vector<uint32_t> indices = {
        0, 1, 3,
        1, 2, 3
    };

    static const std::vector<glm::vec2> coords = {
        { 0, 0 },
        { 1, 0 },
        { 1, 1 },
        { 0, 1 }
    };

    static const std::vector<glm::vec3> vertices = {
        {-1,-1, 0 },
        { 1,-1, 0 },
        { 1, 1, 0 },
        {-1, 1, 0 }
    };

    if ( ! vao ) {
        createGeometryBuffer( vertices, coords, indices, vao, vbo, ibo );
    }

    glBindVertexArray( vao );
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
    glBindVertexArray( 0 );
}


static const fmt::text_style fg_subtle = fmt::fg( fmt::color::dark_gray );
static const fmt::text_style fg_info = fmt::fg( fmt::color::light_sky_blue );
static const fmt::text_style fg_success = fmt::fg( fmt::color::light_green );
static const fmt::text_style fg_warning = fmt::fg( fmt::color::light_yellow );
static const fmt::text_style fg_error = fmt::fg( fmt::color::indian_red );


}   //  ::tq