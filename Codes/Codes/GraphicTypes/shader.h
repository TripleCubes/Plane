#ifndef SHADER_H
#define SHADER_H

#include <Codes/GraphicTypes/graphicTypeData.h>
#include <memory>
#include <string>
#include <glm/glm.hpp>

class Texture;
class Vec3;
class Vec2;
class Color;

class GraphicTypeData_Shader;

class Shader {
public:
    Shader(const Shader&) = delete;
    Shader &operator = (const Shader&) = delete;

    Shader();
    void init(const std::string &shaderPath);
    ~Shader();

    unsigned int getShaderId() const;
    void useProgram() const;
    void setUniform(const std::string &uniformName, const glm::mat4 &mat) const;
    void setUniform(const std::string &uniformName, Vec3 vec) const;
    void setUniform(const std::string &uniformName, Vec2 vec) const;
    void setUniform(const std::string &uniformName, Color color) const;
    void setUniform(const std::string &uniformName, int num) const;
    void setUniform(const std::string &uniformName, bool b) const;
    void setTextureUniform(const std::string &uniformName, const Texture &texture, int textureUniformIndex, bool arrayTexture) const;
    void setTextureUniform(const std::string &uniformName, unsigned int textureId, int textureUniformIndex, bool arrayTexture) const;

private:
    std::shared_ptr<GraphicTypeData_Shader> dataPtr;
};

class GraphicTypeData_Shader: public GraphicTypeData {
public:
    void init(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
    void release() override;

    unsigned int getShaderId() const;

private:
    unsigned int shaderId;
};

#endif
