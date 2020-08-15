#include "teqi/canvas/shaderbuilder.h"

namespace tq {


////////////////////////////////////////////////////////////////////////////////
ShaderBuilder& ShaderBuilder::load(
    std::string_view filename,
    const Shader::Type type )
{
    shaders_.emplace_back( filename, type );
    return *this;
}


}   //  ::tq