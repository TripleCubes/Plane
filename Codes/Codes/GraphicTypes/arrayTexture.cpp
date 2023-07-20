#include <Codes/GraphicTypes/arrayTexture.h>

#include <glad/glad.h>
#include <stb_image.h>
#include <Codes/GraphicTypes/graphicTypesManager.h>

#include <Codes/Debug/print.h>

ArrayTexture::ArrayTexture() {}

void ArrayTexture::init(const std::string &path, int layerWidth, int layerHeight) {
    dataPtr = std::make_shared<GraphicTypeData_ArrayTexture>();
    dataPtr->init(path, layerWidth, layerHeight);
    GraphicTypesManager::addGraphicTypeData(dataPtr);
}

ArrayTexture::~ArrayTexture() {
    dataPtr->release();
    GraphicTypesManager::removeGraphicTypeData(dataPtr);
}

unsigned int ArrayTexture::getTextureId() const {
    return dataPtr->getTextureId();
}

int ArrayTexture::getLayerWidth() const {
    return dataPtr->getLayerWidth();
}

int ArrayTexture::getLayerHeight() const {
    return dataPtr->getLayerHeight();
}

int ArrayTexture::getLayerCount() const {
    return dataPtr->getLayerCount();
}



void GraphicTypeData_ArrayTexture::init(const std::string &path, int layerWidth, int layerHeight) {
    if (initialized) {
        LINEINFORMATION();
        PRINTLN("Array texture already initialized");
        return;
    }

    unsigned char *textureData = stbi_load(path.c_str(), &imageFileWidth, &imageFileHeight, &numberOfColorChannels, 0);
    if (!textureData) {
        LINEINFORMATION();
        PRINT("Failed to load texture");
        PRINTLN(path);

        return;
    }

    int layerCountX = imageFileWidth / layerWidth;
    int layerCountY = imageFileHeight / layerHeight;
    this->layerCount = layerCountX * layerCountY;
    if (layerCount > 256) {
        LINEINFORMATION();
        PRINTLN("LayerCount > 256");
        return;
    }

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureId);

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, layerWidth, layerHeight, layerCount, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    for (int layerIndex = 0; layerIndex < layerCount; layerIndex++) {
        unsigned char layerData[8*8*4];
        int layerIndexX = layerIndex % layerCountX;
        int layerIndexY = layerIndex / layerCountX;
        int layerDataPixelIndex = 0;
        for (int textureY = layerIndexY*layerHeight; textureY < (layerIndexY+1)*layerHeight; textureY++) {
            for (int textureX = layerIndexX*layerWidth; textureX < (layerIndexX+1)*layerWidth; textureX++) {
                for (int textureRGBAIndex = 0; textureRGBAIndex < 4; textureRGBAIndex++) {
                    layerData[layerDataPixelIndex] = textureData[textureY*imageFileWidth*4 + textureX*4 + textureRGBAIndex];
                    layerDataPixelIndex++;
                }
            }
        }
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, layerIndex, layerWidth, layerHeight, 1, GL_RGBA, GL_UNSIGNED_BYTE, layerData);
    }

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    stbi_image_free(textureData);

    initialized = true;
}

void GraphicTypeData_ArrayTexture::release() {
    if (released) {
        return;
    }

    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Cant release not initialized array texture");
        return;
    }

    glDeleteTextures(1, &textureId);

    released = true;
}

unsigned int GraphicTypeData_ArrayTexture::getTextureId() const {
    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Array texture not initialized");
        return 0;
    }

    if (released) {
        LINEINFORMATION();
        PRINTLN("Array texture already released");
        return 0;
    }

    return textureId;
}

int GraphicTypeData_ArrayTexture::getLayerWidth() const {
    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Array texture not initialized");
        return 0;
    }

    if (released) {
        LINEINFORMATION();
        PRINTLN("Array texture already released");
        return 0;
    }

    return layerWidth;
}

int GraphicTypeData_ArrayTexture::getLayerHeight() const {
    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Array texture not initialized");
        return 0;
    }

    if (released) {
        LINEINFORMATION();
        PRINTLN("Array texture already released");
        return 0;
    }

    return layerHeight;
}

int GraphicTypeData_ArrayTexture::getLayerCount() const {
    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Array texture not initialized");
        return 0;
    }

    if (released) {
        LINEINFORMATION();
        PRINTLN("Array texture already released");
        return 0;
    }

    return layerCount;
}
