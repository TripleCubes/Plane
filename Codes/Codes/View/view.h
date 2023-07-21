#ifndef VIEW_H
#define VIEW_H

#include <Codes/GraphicTypes/framebuffer.h>
#include <Codes/GraphicTypes/shader.h>
#include <Codes/GraphicTypes/mesh.h>
#include <glm/glm.hpp>

class View {
public:
    static void init();
    static void update();
    static void draw();

private:
    static const int GBUFFER_POS;
    static const int GBUFFER_NORMAL;
    static const int GBUFFER_COLOR;

    static glm::mat4 projectionMat;
    static glm::mat4 viewMat;

    static Framebuffer framebuffer_gBuffer;
    static Shader shader_gBuffer_colorPallete;

    static Framebuffer framebuffer_view;
    static Shader shader_view;

    static Shader shader_boxFrame;
    static Mesh mesh_boxFrame;

    static void drawChunks();
    static void drawBlockSelection();
};

#endif
