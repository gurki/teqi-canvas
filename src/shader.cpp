#include "teqi/canvas/shader.h"

#include <fmt/core.h>
#include <fstream>
#include <sstream>

namespace tq {


////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] std::string readFile( std::string_view path )
{
    fmt::print( "reading file '{}' ... \n", path );

    std::ifstream file { path.data() };

    if ( ! file.is_open() ) {
        fmt::print( stderr, "failed to open file '{}' \n", path );
        std::fflush( stdout );
    }

    std::stringstream ss;
    ss << file.rdbuf();

    return ss.str();
}


////////////////////////////////////////////////////////////////////////////////
void checkCompileError( const uint32_t shaderId )
{
    int success;
    glGetShaderiv( shaderId, GL_COMPILE_STATUS, &success );

    if ( success ) {
        return;
    }

    const int maxLogSize = 512;
    char infoLog[ maxLogSize ];

    glGetShaderInfoLog( shaderId, maxLogSize, nullptr, infoLog );

    const auto msg = fmt::format(
        "shader compilation error for shader {}: {}", shaderId, infoLog
    );

    fmt::print( "{}", msg );
    throw std::runtime_error { msg };
}


////////////////////////////////////////////////////////////////////////////////
Shader::Shader( std::string_view file, const Shader::Type type ) :
    type_ { type },
    id_ { glCreateShader( GLenum( type )) }
{
    const std::string source = readFile( file );
    const char* sourceStr = source.c_str();

    glShaderSource( id_, 1, &sourceStr, nullptr );
    glCompileShader( id_ );
    checkCompileError( id_ );
}


////////////////////////////////////////////////////////////////////////////////
Shader::~Shader() {
    glDeleteShader( id_ );
}


////////////////////////////////////////////////////////////////////////////////
Shader::Shader( Shader&& other ) noexcept :
    type_ { other.type_ },
    id_ { other.id_ }
{
    other.id_ = 0;
}


////////////////////////////////////////////////////////////////////////////////
Shader& Shader::operator =( Shader&& other ) noexcept {
    std::swap( id_, other.id_ );
    std::swap( type_, other.type_ );
    return *this;
}


}   //  ::tq