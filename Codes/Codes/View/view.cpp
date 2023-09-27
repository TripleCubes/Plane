#include <Codes/View/view.h>

#include <Codes/Settings/settings.h>
#include <Codes/View/camera.h>
#include <Codes/Chunks/chunkLoader.h>
#include <Codes/Chunks/chunk.h>
#include <Codes/RayCast/blockRayCast.h>
#include <Codes/Types/color.h>
#include <Codes/Types/vec2.h>
#include <Codes/input.h>
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

glm::mat4 View::projectionMat(1.0f);
glm::mat4 View::viewMat(1.0f);

Framebuffer View::framebuffer_view_multisampled;
Framebuffer View::framebuffer_view;
Shader View::shader_view;

Shader View::shader_boxFrame;
Mesh View::mesh_boxFrame;

void View::init() {
    framebuffer_view_multisampled.init(0, 0, 1, true);
    framebuffer_view.init(0, 0, 1, false);
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
    if (Settings::isPerspectiveProjection()) {
        projectionMat = glm::perspective(glm::radians(70.0f), 
                                            (float)currentWindowWidth / (float)currentWindowHeight, 
                                            0.1f, 300.0f);
    } else {
        projectionMat = glm::ortho(-125.0f/2.0f, 125.0f/2.0f, -75.0f/2.0f, 75.0f/2.0f, -150.0f, 150.0f);
    }

    viewMat = glm::lookAt((Camera::getPos()).toGlmVec3(),
                                        (Camera::getPos() + Camera::getDir()).toGlmVec3(),
                                        glm::vec3(0.0f, 1.0f, 0.0f));

    if (Settings::isFreeCam()) {
        savedBlockRayCastResult = BlockRayCast::cast(Camera::getPos(), Camera::getDir(), 30);

        return;
    }

    Vec2 normalizedScreenCoord = Input::getMousePos().toNormalizedScreenCoord();
    glm::vec4 v4(normalizedScreenCoord.x, normalizedScreenCoord.y, -1.0f, 1.0f);
    v4 = glm::inverse(projectionMat) * v4;
    v4.z = Settings::isPerspectiveProjection() ? -1.0f : 0.0f;
    v4.w = 0.0f;
    v4 = glm::inverse(viewMat) * v4;

    if (Settings::isPerspectiveProjection()) {
        savedBlockRayCastResult = BlockRayCast::cast(Camera::getPos(), Vec3(v4.x, v4.y, v4.z), 30);
    } else {
        savedBlockRayCastResult = BlockRayCast::cast(Camera::getPos() + Vec3(v4.x, v4.y, v4.z), Camera::getDir(), 30);
    }
}

void View::draw() {
    shader_view.useProgram();
    shader_view.setUniform("projectionMat", projectionMat);
    shader_view.setUniform("viewMat", viewMat);

    shader_boxFrame.useProgram();
    shader_boxFrame.setUniform("projectionMat", projectionMat);
    shader_boxFrame.setUniform("viewMat", viewMat);

    framebuffer_view_multisampled.bind();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    drawChunks();
    drawBlockSelection();

    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer_view_multisampled.getFBO());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer_view.getFBO());
    glBlitFramebuffer(0, 0, currentWindowWidth, currentWindowHeight, 
                        0, 0, currentWindowWidth, currentWindowHeight,
                        GL_COLOR_BUFFER_BIT, GL_NEAREST);

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

    shader_view.useProgram();
    
    for (const auto &i: ChunkLoader::getChunkList()) {
        Vec3 pos = Vec3(i.first) * CHUNK_WIDTH;
        glm::mat4 modelMat = glm::mat4(1.0f);
        modelMat = glm::translate(modelMat, pos.toGlmVec3());
        shader_view.setUniform("modelMat", modelMat);
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
