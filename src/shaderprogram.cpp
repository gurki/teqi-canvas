#include "teqi/canvas/shaderprogram.h"
#include <fmt/color.h>
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

    const auto msg = fmt::format(
        fmt::fg( fmt::color::dark_red ),
        "shader link error: {}",
        infoLog
    );

    fmt::print( "{}", msg );
    throw std::runtime_error( msg );
}


////////////////////////////////////////////////////////////////////////////////
ShaderProgram::ShaderProgram(
    const std::string& root,
    const std::vector<std::string>& names )
{
    std::vector<Shader> shaders;

    for ( const auto& name : names ) {
        shaders.emplace_back( root + name );
    }

    id_ = glCreateProgram();

    for ( const auto& shader : shaders ) {
        glAttachShader( id_, shader.id() );
    }

    glLinkProgram( id_ );
    checkLinkError( id_ );

    fmt::print(
        fmt::fg( fmt::color::light_green ),
        "linked shader program {} with {} shaders \n",
        id_, shaders.size()
    );
}


////////////////////////////////////////////////////////////////////////////////
ShaderProgram::~ShaderProgram() {
    glDeleteProgram( id_ );
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


////////////////////////////////////////////////////////////////////////////////
bool ShaderProgram::bindUniformBlock(
    const std::string& name,
    const uint32_t location ) const
{
    uint32_t blockId = glGetUniformBlockIndex( id_, name.c_str() );

    if ( blockId != GL_INVALID_INDEX ) {
        glUniformBlockBinding( id_, blockId, location );
        return true;
    }

    return false;
}


////////////////////////////////////////////////////////////////////////////////
ShaderProgram::ShaderProgram( ShaderProgram&& other ) noexcept :
    id_ ( other.id_ )
{
    other.id_ = 0;
}


////////////////////////////////////////////////////////////////////////////////
ShaderProgram& ShaderProgram::operator=( ShaderProgram&& other ) noexcept {
    std::swap( id_, other.id_ );
    return *this;
}


}   //  ::tq