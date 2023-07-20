#ifndef TEXTURE_H
#define TEXTURE_H

#include <Codes/GraphicTypes/graphicTypeData.h>
#include <memory>
#include <string>

class GraphicTypeData_Texture;

class Texture {
public:
    Texture(const Texture&) = delete;
    Texture &operator = (const Texture&) = delete;

    Texture();
    void init(const std::string &path);
    ~Texture();

    unsigned int getTextureId() const;
    int getTextureWidth() const;
    int getTextureHeight() const;

private:
    std::shared_ptr<GraphicTypeData_Texture> dataPtr;
};

class GraphicTypeData_Texture: public GraphicTypeData {
public:    
    void init(const std::string &path);
    void release() override;

    unsigned int getTextureId() const;
    int getTextureWidth() const;
    int getTextureHeight() const;

private:
    int textureWidth = 0; 
    int textureHeight = 0;
    int numberOfColorChannels = 0;

    unsigned int textureId;
};

#endif
