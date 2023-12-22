#ifndef VIEW_H
#define VIEW_H

#include <Codes/GraphicTypes/framebuffer.h>
#include <Codes/GraphicTypes/shader.h>
#include <Codes/GraphicTypes/mesh.h>
#include <Codes/GraphicTypes/texture.h>
#include <glm/glm.hpp>

class View {
public:
    static void init();
    static void update();
    static void draw();

    static const glm::mat4 &getViewMat() { return viewMat; };
    static const glm::mat4 &getProjectionMat() { return projectionMat; }; 

private:
    static const int GBUFFER_POS;
    static const int GBUFFER_NORMAL;
    static const int GBUFFER_COLOR;

    static glm::mat4 projectionMat;
    static glm::mat4 viewMat;

    static Framebuffer framebuffer_view_multisampled;
    static Framebuffer framebuffer_view;
    static Shader shader_view;

    static Texture texture_colorPallete;

    static Shader shader_gameSelection;

    static void drawChunks();
    static void drawBlockSelection();
    static void drawGameSelection();
    static void drawEntities();

    #ifdef DEBUG
    static void drawDebug3dPoints();
    static void drawDebug3dLines();
    static void drawDebug3dSurfaces();
    static void drawDebug3dBoxFrames();
    static void drawDebug3dText();
    #endif
};

#endif
