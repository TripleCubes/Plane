#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <Codes/GraphicTypes/graphicTypeData.h>
#include <memory>
#include <vector>

class GraphicTypeData_Framebuffer;

class Framebuffer {
public:
    Framebuffer(const Framebuffer&) = delete;
    Framebuffer &operator = (const Framebuffer&) = delete;

    Framebuffer();
    void init(int width, int height, int numberOfTextures);
    ~Framebuffer();

    void bind() const;
    unsigned int getFBO() const;
    unsigned int getTextureId(int index = 0) const;

private:
    std::shared_ptr<GraphicTypeData_Framebuffer> dataPtr;
};

class GraphicTypeData_Framebuffer: public GraphicTypeData {
public:
    void init(int width, int height, int numberOfTextures);
    void release() override;

    void bind() const;
    unsigned int getFBO() const;
    unsigned int getTextureId(int index) const;

private:
    int framebufferWidth = 0;
    int framebufferHeight = 0;
    int numberOfTextures = 0;

    unsigned int FBO;
    std::vector<unsigned int> textureIdList;
    unsigned int RBO;
};

#endif
