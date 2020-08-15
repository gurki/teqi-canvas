#pragma once

#include "teqi/canvas/shader.h"

#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace tq {


struct ShaderProgram {

    ShaderProgram() = default;
    explicit ShaderProgram( const std::vector<Shader>& shaders );

    void use() const;

    void setBool( const std::string& name, bool value ) const;
    void setInt( const std::string& name, int value ) const;
    void setFloat( const std::string& name, float value ) const;
    void setVec2( const std::string& name, const glm::vec2& value ) const;
    void setVec2( const std::string& name, float x, float y ) const;
    void setVec3( const std::string& name, const glm::vec3& value ) const;
    void setVec3( const std::string& name, float x, float y, float z ) const;
    void setVec4( const std::string& name, const glm::vec4& value ) const;
    void setVec4( const std::string& name, float x, float y, float z, float w ) const;
    void setMat2( const std::string& name, const glm::mat2& mat ) const;
    void setMat3( const std::string& name, const glm::mat3& mat ) const;
    void setMat4( const std::string& name, const glm::mat4& mat ) const;

    [[nodiscard]] uint32_t id() const { return id_; }
    [[nodiscard]] bool valid() const { return id_ > 0; }

    private:

        uint32_t id_ { 0 };
};


}   //  ::tq