#pragma once 

#include "teqi/canvas/shaderprogram.h"

namespace tq {


class ShaderBuilder 
{
    public:

        ShaderBuilder() = default;

        ShaderBuilder& load( 
            std::string_view filename, 
            const Shader::Type
        );

        [[nodiscard]] ShaderProgram build() const {
            return ShaderProgram { shaders_ };
        }

    private:

        std::vector<Shader> shaders_ {};
};


}   //  ::tq