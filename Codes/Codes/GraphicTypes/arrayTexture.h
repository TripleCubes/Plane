#ifndef ARRAYTEXTURE_H
#define ARRAYTEXTURE_H

#include <Codes/GraphicTypes/graphicTypeData.h>
#include <string>
#include <memory>

class GraphicTypeData_ArrayTexture;

class ArrayTexture {
public:
    ArrayTexture(const ArrayTexture&) = delete;
    ArrayTexture &operator = (const ArrayTexture&) = delete;

    ArrayTexture();
    void init(const std::string &path, int layerWidth, int layerHeight);
    ~ArrayTexture();

    unsigned int getTextureId() const;
    int getLayerWidth() const;
    int getLayerHeight() const;
    int getLayerCount() const;

private:
    std::shared_ptr<GraphicTypeData_ArrayTexture> dataPtr;
};

class GraphicTypeData_ArrayTexture: public GraphicTypeData {
public:
    void init(const std::string &path, int layerWidth, int layerHeight);
    void release() override;

    unsigned int getTextureId() const;
    int getLayerWidth() const;
    int getLayerHeight() const;
    int getLayerCount() const;

private:
    int layerWidth = 0;
    int layerHeight = 0;
    int layerCount = 0;
    
    int imageFileWidth = 0;
    int imageFileHeight = 0;
    int numberOfColorChannels = 0;

    unsigned int textureId;
};

#endif
