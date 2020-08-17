#include "teqi/canvas/shader.h"
#include "teqi/canvas/utility.h"

#include <fstream>
#include <sstream>

namespace tq {


////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] std::string readFile( std::string_view path )
{
    fmt::print( "reading file '{}' ... \n", path );

    std::ifstream file { path.data() };

    if ( ! file.is_open() ) {
        fmt::print( fg_error, "failed to open file '{}' \n", path );
        std::fflush( stdout );
        return {};
    }

    std::stringstream ss;
    ss << file.rdbuf();

    return ss.str();
}


////////////////////////////////////////////////////////////////////////////////
bool checkCompileError( const uint32_t shaderId )
{
    int success;
    glGetShaderiv( shaderId, GL_COMPILE_STATUS, &success );

    if ( success ) {
        return true;
    }

    const int maxLogSize = 512;
    char infoLog[ maxLogSize ];

    glGetShaderInfoLog( shaderId, maxLogSize, nullptr, infoLog );

    const auto msg = fmt::format(
        fg_error, "shader compilation error for shader {}: {}",
        shaderId, infoLog
    );

    fmt::print( "{}", msg );
    throw std::runtime_error { msg };

    return false;
}


////////////////////////////////////////////////////////////////////////////////
Shader::Shader( const std::string& file, const Shader::Type type ) :
    type_{ type }
{
    if ( type == Type::Invalid ) {
        type_ = Shader::typeFromFileExtension( file );
    }

    id_ = glCreateShader( GLenum( type_ ) );

    const std::string source = readFile( file );

    const char* sourceStr = source.c_str();

    glShaderSource( id_, 1, &sourceStr, nullptr );
    glCompileShader( id_ );

    if ( ! checkCompileError( id_ ) ) {
        return;
    }

    fmt::print( fg_success, "compiled {} shader \n", to_string( type_ ) );
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


////////////////////////////////////////////////////////////////////////////////
Shader::Type Shader::typeFromFileExtension( const std::string& name )
{
    const std::string ext = name.substr( name.size() - 2 );

    if ( ext == "vs" ) return Type::Vertex;
    if ( ext == "fs" ) return Type::Fragment;
    if ( ext == "tc" ) return Type::TessControl;
    if ( ext == "te" ) return Type::TessEval;
    if ( ext == "gs" ) return Type::Geometry;
    if ( ext == "cs" ) return Type::Compute;

    return Type::Invalid;
}


////////////////////////////////////////////////////////////////////////////////
const std::string& to_string( const Shader::Type type )
{
    static const std::unordered_map<Shader::Type, std::string> names = {
        { Shader::Type::Vertex, "Vertex" },
        { Shader::Type::Fragment, "Fragment" },
        { Shader::Type::TessControl, "Tesselation Control" },
        { Shader::Type::TessEval, "Tesselation Evaluation" },
        { Shader::Type::Geometry, "Geometry" },
        { Shader::Type::Compute, "Compute" },
        { Shader::Type::Invalid, "Invalid" }
    };

    return names.at( type );
}


}   //  ::tq