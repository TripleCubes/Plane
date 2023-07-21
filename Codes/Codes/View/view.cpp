#include <Codes/View/view.h>

#include <Codes/Settings/settings.h>
#include <Codes/View/camera.h>
#include <Codes/Chunks/chunkLoader.h>
#include <Codes/Chunks/chunk.h>
#include <Codes/RayCast/blockRayCast.h>
#include <Codes/Types/color.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <vector>

#include <Codes/Debug/print.h>

extern int currentWindowWidth;
extern int currentWindowHeight;
extern const int CHUNK_WIDTH;
namespace GlobalGraphics {
    extern Mesh mesh_windowRect;
    extern Shader shader_windowRect;
}
extern BlockRayCastResult savedBlockRayCastResult;

const int View::GBUFFER_POS = 0;
const int View::GBUFFER_NORMAL = 1;
const int View::GBUFFER_COLOR = 2;

Framebuffer View::framebuffer_gBuffer;
Shader View::shader_gBuffer_colorPallete;

Framebuffer View::framebuffer_view;
Shader View::shader_view;

Shader View::shader_boxFrame;
Mesh View::mesh_boxFrame;

void View::init() {
    framebuffer_gBuffer.init(0, 0, 3);
    shader_gBuffer_colorPallete.init("Shaders/View/gBuffer_colorPallete");

    framebuffer_view.init(0, 0, 1);
    shader_view.init("Shaders/View/view");

    shader_boxFrame.init("Shaders/View/boxFrame");
    mesh_boxFrame.init();
    std::vector<float> verticies_boxFrame = {
        0, 1, 0, // A 0
        1, 1, 0, // B 1
        1, 1, 1, // C 2
        0, 1, 1, // D 3
        0, 0, 0, // E 4
        1, 0, 0, // F 5
        1, 0, 1, // G 6
        0, 0, 1, // H 7
    };
    std::vector<unsigned int> indicies_boxFrame = {
        0, 1,
        1, 2,
        2, 3,
        3, 0,
        0, 4,
        1, 5,
        2, 6,
        3, 7,
        4, 5,
        5, 6,
        6, 7,
        7, 4
    };
    mesh_boxFrame.set(MeshType::MESH3D_FRAME, verticies_boxFrame, indicies_boxFrame);
}

void View::update() {
    savedBlockRayCastResult = BlockRayCast::cast(Camera::getPos(), Camera::getDir(), 10);
}

void View::draw() {
    glm::mat4 projectionMat = glm::mat4(1.0f);
    if (Settings::isPerspectiveProjection()) {
        projectionMat = glm::perspective(glm::radians(70.0f), 
                                            (float)currentWindowWidth / (float)currentWindowHeight, 
                                            0.1f, 300.0f);
    } else {
        projectionMat = glm::ortho(-125.0f, 125.0f, -75.0f, 75.0f, -150.0f, 150.0f);
    }

    glm::mat4 viewMat = glm::lookAt((Camera::getPos()).toGlmVec3(),
                                        (Camera::getPos() + Camera::getDir()).toGlmVec3(),
                                        glm::vec3(0.0f, 1.0f, 0.0f));

    shader_gBuffer_colorPallete.useProgram();
    shader_gBuffer_colorPallete.setUniform("projectionMat", projectionMat);
    shader_gBuffer_colorPallete.setUniform("viewMat", viewMat);

    shader_boxFrame.useProgram();
    shader_boxFrame.setUniform("projectionMat", projectionMat);
    shader_boxFrame.setUniform("viewMat", viewMat);

    framebuffer_gBuffer.bind();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    drawChunks();

    framebuffer_view.bind();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    shader_view.useProgram();
    shader_view.setTextureUniform("gBuffer_pos", framebuffer_gBuffer.getTextureId(GBUFFER_POS), 0);
    shader_view.setTextureUniform("gBuffer_normal", framebuffer_gBuffer.getTextureId(GBUFFER_NORMAL), 1);
    shader_view.setTextureUniform("gBuffer_color", framebuffer_gBuffer.getTextureId(GBUFFER_COLOR), 2);
    GlobalGraphics::mesh_windowRect.draw();

    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer_gBuffer.getFBO());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer_view.getFBO());
    glBlitFramebuffer(0, 0, currentWindowWidth, currentWindowHeight, 
                        0, 0, currentWindowWidth, currentWindowHeight,
                        GL_DEPTH_BUFFER_BIT, GL_NEAREST);

    framebuffer_view.bind();
    glEnable(GL_DEPTH_TEST);
    drawBlockSelection();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    GlobalGraphics::shader_windowRect.useProgram();
    GlobalGraphics::shader_windowRect.setTextureUniform("windowRectTexture", framebuffer_view.getTextureId(GBUFFER_POS), 0);
    GlobalGraphics::mesh_windowRect.draw();
}

void View::drawChunks() {
    if (Settings::isWireframeMode())
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    shader_gBuffer_colorPallete.useProgram();
    
    for (const auto &i: ChunkLoader::getChunkList()) {
        Vec3 pos = Vec3(i.first) * CHUNK_WIDTH;
        glm::mat4 modelMat = glm::mat4(1.0f);
        modelMat = glm::translate(modelMat, pos.toGlmVec3());
        shader_gBuffer_colorPallete.setUniform("modelMat", modelMat);
        i.second->draw();
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void View::drawBlockSelection() {
    if (!savedBlockRayCastResult.found) {
        return;
    }
    
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, Vec3(savedBlockRayCastResult.selectedPos).toGlmVec3());
    shader_boxFrame.useProgram();
    shader_boxFrame.setUniform("modelMat", modelMat);
    shader_boxFrame.setUniform("boxSize", Vec3(1, 1, 1));
    shader_boxFrame.setUniform("boxMargin", Vec3(0, 0, 0));
    if (Settings::isWireframeMode()) {
        shader_boxFrame.setUniform("frameColor", Color(1, 1, 1, 1));
    } else {
        shader_boxFrame.setUniform("frameColor", Color(0, 0, 0, 1));
    }

    mesh_boxFrame.draw();
}
