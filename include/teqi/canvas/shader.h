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

    Shader( std::string_view file, const Type );
    ~Shader();

    Shader( const Shader& ) = delete;
    Shader& operator =( const Shader& ) = delete;
    Shader( Shader&& ) noexcept;
    Shader& operator =( Shader&& other ) noexcept;

    [[nodiscard]] uint32_t id() const { return id_; }
    [[nodiscard]] bool valid() const { return id_ != 0; }

    private:

        Type type_ { Type::Invalid };
        uint32_t id_ { 0 };
};


}   //  ::tq