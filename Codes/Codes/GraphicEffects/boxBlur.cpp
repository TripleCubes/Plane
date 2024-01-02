#include <Codes/GraphicEffects/boxBlur.h>

#include <Codes/GraphicTypes/mesh.h>
#include <Codes/Types/vec2.h>
#include <glad/glad.h>

namespace GlobalGraphics {
    extern Mesh mesh_windowRect;
}
extern int currentWindowWidth;
extern int currentWindowHeight;

BoxBlur::BoxBlur() {
    framebuffer_horizontalBlurred.init(currentWindowWidth, currentWindowHeight, 1, false);
    framebuffer_verticalBlurred.init(currentWindowWidth, currentWindowHeight, 1, false);
    shader_blur.init("Shaders/GraphicEffects/boxBlur");
    shader_blur.useProgram();
    shader_blur.setUniform("windowSize", Vec2(currentWindowWidth, currentWindowHeight));
}

void BoxBlur::createBlurredTexture(unsigned int in_textureId, int numPasses, int blurSizePx) {
    createBlurredTexture(in_textureId, blurSizePx);

    for (int i = 0; i < numPasses - 1; i++) {
        createBlurredTexture(framebuffer_verticalBlurred.getTextureId(), blurSizePx);
    }
}

void BoxBlur::createBlurredTexture(unsigned int in_textureId, int blurSizePx) {
    shader_blur.useProgram();
    shader_blur.setUniform("blurSizePx", blurSizePx);
    shader_blur.setUniform("horizontalBlur", true);
    shader_blur.setTextureUniform("in_texture", in_textureId, 0, false);
    framebuffer_horizontalBlurred.bind();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    GlobalGraphics::mesh_windowRect.draw();

    shader_blur.setUniform("horizontalBlur", false);
    shader_blur.setTextureUniform("in_texture", framebuffer_horizontalBlurred.getTextureId(), 0, false);
    framebuffer_verticalBlurred.bind();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    GlobalGraphics::mesh_windowRect.draw();
}
