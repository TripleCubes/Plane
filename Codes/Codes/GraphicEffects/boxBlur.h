#ifndef BOXBLUR_H
#define BOXBLUR_H

#include <Codes/GraphicTypes/framebuffer.h>
#include <Codes/GraphicTypes/shader.h>

class BoxBlur {
public:
    void init();
    unsigned int getBlurredTextureId() const { return framebuffer_verticalBlurred.getTextureId(); };
    void createBlurredTexture(unsigned int in_textureId, int numPasses, int blurSizePx);

private:
    Framebuffer framebuffer_horizontalBlurred;
    Framebuffer framebuffer_verticalBlurred;
    Shader shader_blur;

    void createBlurredTexture(unsigned int in_textureId, int blurSizePx);
};

#endif
