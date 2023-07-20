#include <Codes/GraphicTypes/shader.h>

#include <string>
#include <fstream>
#include <Codes/GraphicTypes/graphicTypesManager.h>
#include <glad/glad.h>

#include <Codes/Types/vec2.h>
#include <Codes/Types/vec3.h>
#include <Codes/Types/color.h>
#include <Codes/GraphicTypes/texture.h>
#include <glm/gtc/type_ptr.hpp>

#include <Codes/Debug/print.h>

Shader::Shader() {}

void Shader::init(const std::string &shaderPath) {
    dataPtr = std::make_shared<GraphicTypeData_Shader>();
    dataPtr->init(shaderPath + "_vertex.glsl", shaderPath + "_fragment.glsl");
    GraphicTypesManager::addGraphicTypeData(dataPtr);
}

Shader::~Shader() {
    dataPtr->release();
    GraphicTypesManager::removeGraphicTypeData(dataPtr);
}

unsigned int Shader::getShaderId() const {
    return dataPtr->getShaderId();
}

void Shader::useProgram() const {
    glUseProgram(dataPtr->getShaderId());
}

void Shader::setUniform(const std::string &uniformName, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(dataPtr->getShaderId(), uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setUniform(const std::string &uniformName, Vec3 vec) const {
    glUniform3f(glGetUniformLocation(dataPtr->getShaderId(), uniformName.c_str()), vec.x, vec.y, vec.z);
}

void Shader::setUniform(const std::string &uniformName, Vec2 vec) const {
    glUniform2f(glGetUniformLocation(dataPtr->getShaderId(), uniformName.c_str()), vec.x, vec.y);    
}

void Shader::setUniform(const std::string &uniformName, Color color) const {
    glUniform4f(glGetUniformLocation(dataPtr->getShaderId(), uniformName.c_str()), color.r, color.g, color.b, color.a);
}

void Shader::setUniform(const std::string &uniformName, int num) const {
    glUniform1i(glGetUniformLocation(dataPtr->getShaderId(), uniformName.c_str()), num);
}

void Shader::setUniform(const std::string &uniformName, bool b) const {
    glUniform1i(glGetUniformLocation(dataPtr->getShaderId(), uniformName.c_str()), b);
}

void Shader::setTextureUniform(const std::string &uniformName, const Texture &texture, int textureUniformIndex, bool arrayTexture) const {
    setTextureUniform(uniformName, texture.getTextureId(), textureUniformIndex, arrayTexture);
}

void Shader::setTextureUniform(const std::string &uniformName, unsigned int textureId, int textureUniformIndex, bool arrayTexture) const {
    glUniform1i(glGetUniformLocation(dataPtr->getShaderId(), uniformName.c_str()), textureUniformIndex);
    glActiveTexture(GL_TEXTURE0 + textureUniformIndex);
    glBindTexture(arrayTexture? GL_TEXTURE_2D_ARRAY : GL_TEXTURE_2D, textureId);
}



unsigned int compileShader(const std::string &path, bool isFragmentShader) {
    std::ifstream file(path);
    if (file.fail()) {
        LINEINFORMATION();
        PRINT(path);
        PRINTLN("not found");
        return -1;
    }
    std::string shaderCodeString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    const char *shaderCode = shaderCodeString.c_str();
    unsigned int shader;

    shader = glCreateShader(isFragmentShader ? GL_FRAGMENT_SHADER : GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        LINEINFORMATION();
        PRINTLN(path);
        PRINTLN(infoLog);
        return -1;
    }

    return shader;
}

void linkShaderProgram(unsigned int shaderProgram, const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    unsigned int vertexShader = compileShader(vertexShaderPath, false);
    unsigned int fragmentShader = compileShader(fragmentShaderPath, true);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        LINEINFORMATION();
        PRINTLN(vertexShaderPath);
        PRINTLN(fragmentShaderPath);
        PRINTLN(infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void GraphicTypeData_Shader::init(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    if (initialized) {
        LINEINFORMATION();
        PRINTLN("Shader already initialized");
        return;
    }

    shaderId = glCreateProgram();
    linkShaderProgram(shaderId, vertexShaderPath, fragmentShaderPath);

    initialized = true;
}

void GraphicTypeData_Shader::release() {
    if (released) {
        return;
    }

    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Cant release unitialized shader");
        return;
    }

    glDeleteProgram(shaderId);

    released = true;
}

unsigned int GraphicTypeData_Shader::getShaderId() const {
    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Shader not initialized");
        return 0;
    }

    if (released) {
        LINEINFORMATION();
        PRINTLN("Shader already released");
        return 0;
    }
    
    return shaderId;
}
