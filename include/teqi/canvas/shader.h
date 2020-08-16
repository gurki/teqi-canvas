#pragma once

#include <gl/glew.h>
#include <string_view>

namespace tq {


struct Shader
{
    enum class Type : GLenum
    {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        TessControl = GL_TESS_CONTROL_SHADER,
        TessEval = GL_TESS_EVALUATION_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        Compute = GL_COMPUTE_SHADER,
        Invalid
    };

    Shader( const std::string& file, const Type = Type::Invalid );
    ~Shader();

    [[nodiscard]] uint32_t id() const { return id_; }
    [[nodiscard]] bool valid() const { return id_ != 0; }

    Shader( const Shader& ) = delete;
    Shader& operator=( const Shader& ) = delete;

    Shader( Shader&& ) noexcept;
    Shader& operator=( Shader&& other ) noexcept;

    static Shader::Type typeFromFileExtension( const std::string& name );

    private:

        Type type_ { Type::Invalid };
        uint32_t id_ { 0 };
};


const std::string& to_string( const Shader::Type );


}   //  ::tq