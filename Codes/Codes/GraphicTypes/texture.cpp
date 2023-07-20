#include <Codes/GraphicTypes/texture.h>

#include <glad/glad.h>
#include <stb_image.h>
#include <Codes/GraphicTypes/graphicTypesManager.h>

#include <Codes/Debug/print.h>

Texture::Texture() {}

void Texture::init(const std::string &path) {
    dataPtr = std::make_shared<GraphicTypeData_Texture>();
    dataPtr->init(path);
    GraphicTypesManager::addGraphicTypeData(dataPtr);
}

Texture::~Texture() {
    dataPtr->release();
    GraphicTypesManager::removeGraphicTypeData(dataPtr);
}

unsigned int Texture::getTextureId() const {
    return dataPtr->getTextureId();
}

int Texture::getTextureWidth() const {
    return dataPtr->getTextureWidth();
}

int Texture::getTextureHeight() const {
    return dataPtr->getTextureHeight();
}



void GraphicTypeData_Texture::init(const std::string &path) {
    if (initialized) {
        LINEINFORMATION();
        PRINTLN("Texture already initialized");
        return;
    }

    unsigned char *textureData = stbi_load(path.c_str(), &textureWidth, &textureHeight, &numberOfColorChannels, 0);
    if (!textureData) {
        LINEINFORMATION();
        PRINT("Failed to load texture");
        PRINTLN(path);

        return;
    }

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(textureData);

    initialized = true;
}

void GraphicTypeData_Texture::release() {
    if (released) {
        return;
    }

    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Cant release unitialized texture");
        return;
    }

    glDeleteTextures(1, &textureId);

    released = true;
}

unsigned int GraphicTypeData_Texture::getTextureId() const {
    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Texture not initialized");
        return 0;
    }

    if (released) {
        LINEINFORMATION();
        PRINTLN("Texture already released");
        return 0;
    }

    return textureId;
}

int GraphicTypeData_Texture::getTextureWidth() const {
    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Texture not initialized");
        return 0;
    }

    if (released) {
        LINEINFORMATION();
        PRINTLN("Texture already released");
        return 0;
    }

    return textureWidth;
}

int GraphicTypeData_Texture::getTextureHeight() const {
    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Texture not initialized");
        return 0;
    }

    if (released) {
        LINEINFORMATION();
        PRINTLN("Texture already released");
        return 0;
    }

    return textureHeight;
}
