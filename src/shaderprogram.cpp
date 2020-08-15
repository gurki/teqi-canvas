#include "teqi/canvas/shaderprogram.h"
#include <fmt/core.h>
#include <stdexcept>

namespace tq {


////////////////////////////////////////////////////////////////////////////////
void checkLinkError( const uint32_t programId )
{
    int success;
    glGetProgramiv( programId, GL_LINK_STATUS, &success );

    if ( success ) {
        return;
    }

    const int logSize = 1024;
    char infoLog[ logSize ];

    glGetProgramInfoLog( programId, logSize, nullptr, infoLog );

    throw std::runtime_error { fmt::format(
        "shader link error: {}", infoLog
    )};
}


////////////////////////////////////////////////////////////////////////////////
ShaderProgram::ShaderProgram( const std::vector<Shader>& shaders ) :
    id_ { glCreateProgram() }
{
    for ( const auto& shader : shaders ) {
        glAttachShader( id_, shader.id() );
    }

    glLinkProgram( id_ );
    checkLinkError( id_ );

    glUseProgram( id_ );

    uint32_t cameraBlockId = glGetUniformBlockIndex( id_, "Camera" );
    uint32_t lightsBlockId = glGetUniformBlockIndex( id_, "Lights" );

    if ( cameraBlockId != GL_INVALID_INDEX ) {
        glUniformBlockBinding( id_, cameraBlockId, 0 );
    }

    if ( lightsBlockId != GL_INVALID_INDEX ) {
        glUniformBlockBinding( id_, lightsBlockId, 1 );
    }
}


////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::use() const {
    glUseProgram( id_ );
}


////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setBool( const std::string& name, bool value ) const {
    glUniform1i(
        glGetUniformLocation( id_, name.c_str() ), static_cast<int>( value )
    );
}


////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setInt( const std::string& name, int value ) const {
    glUniform1i( glGetUniformLocation( id_, name.c_str() ), value );
}


////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setFloat( const std::string& name, float value ) const {
    glUniform1f( glGetUniformLocation( id_, name.c_str() ), value );
}


////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setVec2( const std::string& name, const glm::vec2& value ) const {
    glUniform2fv( glGetUniformLocation( id_, name.c_str() ), 1, &value[ 0 ] );
}


////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setVec2( const std::string& name, float x, float y ) const {
    glUniform2f( glGetUniformLocation( id_, name.c_str() ), x, y );
}


////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setVec3( const std::string& name, const glm::vec3& value ) const {
    glUniform3fv( glGetUniformLocation( id_, name.c_str()) , 1, &value[ 0 ] );
}


////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setVec3( const std::string& name, float x, float y, float z ) const {
    glUniform3f( glGetUniformLocation( id_, name.c_str() ), x, y, z );
}


////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setVec4( const std::string& name, const glm::vec4& value ) const {
    glUniform4fv( glGetUniformLocation( id_, name.c_str() ), 1, &value[ 0 ] );
}


////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setVec4( const std::string& name, float x, float y, float z, float w ) const {
    glUniform4f( glGetUniformLocation( id_, name.c_str() ), x, y, z, w );
}


////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setMat2( const std::string& name, const glm::mat2& mat ) const {
    glUniformMatrix2fv(
        glGetUniformLocation( id_, name.c_str() ), 1, GL_FALSE, &mat[ 0 ][ 0 ]
    );
}


////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setMat3( const std::string& name, const glm::mat3& mat ) const {
    glUniformMatrix3fv(
        glGetUniformLocation( id_, name.c_str() ), 1, GL_FALSE, &mat[ 0 ][ 0 ]
    );
}


////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setMat4( const std::string& name, const glm::mat4& mat ) const {
    glUniformMatrix4fv(
        glGetUniformLocation( id_, name.c_str() ), 1, GL_FALSE, &mat[ 0 ][ 0 ]
    );
}


}   //  ::tq