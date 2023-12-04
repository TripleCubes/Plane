#include <Codes/View/view.h>

#include <Codes/Settings/settings.h>
#include <Codes/View/camera.h>
#include <Codes/Chunks/chunkLoader.h>
#include <Codes/Chunks/chunk.h>
#include <Codes/RayCast/blockRayCast.h>
#include <Codes/Game/GameSelection/gameSelection.h>
#include <Codes/Entities/entityList.h>
#include <Codes/Entities/entity.h>

#include <Codes/Types/color.h>
#include <Codes/Types/vec2.h>
#include <Codes/Types/vec3.h>
#include <Codes/Input/input.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <vector>

#include <Codes/Debug/debug3d.h>

#include <Codes/Debug/print.h>

extern int currentWindowWidth;
extern int currentWindowHeight;
extern const int CHUNK_WIDTH;
namespace GlobalGraphics {
    extern Mesh mesh_windowRect;
    extern Shader shader_windowRect;

    extern Mesh mesh_3dBox;
    extern Shader shader_3dBox;

    extern Mesh mesh_point;
    extern Shader shader_point;

    extern Mesh mesh_boxFrame;
    extern Shader shader_boxFrame;
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

Texture View::texture_colorPallete;

Shader View::shader_gameSelection;

void View::init() {
    framebuffer_view_multisampled.init(0, 0, 1, true);
    framebuffer_view.init(0, 0, 1, false);
    shader_view.init("Shaders/View/view");

    texture_colorPallete.init("Textures/colorPallete.png");

    shader_gameSelection.init("Shaders/View/gameSelection");
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

    // TO DO: Move to another file
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
    shader_view.setTextureUniform("colorPalleteTexture", texture_colorPallete, 0, false);
    shader_view.setUniform("colorPalleteTextureWH", Vec2((float)texture_colorPallete.getTextureWidth(), 
                                                            (float)texture_colorPallete.getTextureHeight()));

    GlobalGraphics::shader_boxFrame.useProgram();
    GlobalGraphics::shader_boxFrame.setUniform("projectionMat", projectionMat);
    GlobalGraphics::shader_boxFrame.setUniform("viewMat", viewMat);

    shader_gameSelection.useProgram();
    shader_gameSelection.setUniform("projectionMat", projectionMat);
    shader_gameSelection.setUniform("viewMat", viewMat);

    GlobalGraphics::shader_3dBox.useProgram();
    GlobalGraphics::shader_3dBox.setUniform("projectionMat", projectionMat);
    GlobalGraphics::shader_3dBox.setUniform("viewMat", viewMat);

    GlobalGraphics::shader_point.useProgram();
    GlobalGraphics::shader_point.setUniform("projectionMat", projectionMat);
    GlobalGraphics::shader_point.setUniform("viewMat", viewMat);

    framebuffer_view_multisampled.bind();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    drawChunks();
    drawBlockSelection();
    drawGameSelection();
    drawEntities();
    #ifdef DEBUG
    drawDebug3D();
    #endif

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
    GlobalGraphics::shader_windowRect.setTextureUniform("windowRectTexture", framebuffer_view.getTextureId(GBUFFER_POS), 0, false);
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
    GlobalGraphics::shader_boxFrame.useProgram();
    GlobalGraphics::shader_boxFrame.setUniform("modelMat", modelMat);
    GlobalGraphics::shader_boxFrame.setUniform("boxSize", Vec3(1, 1, 1));
    GlobalGraphics::shader_boxFrame.setUniform("boxMargin", Vec3(0, 0, 0));
    if (Settings::isWireframeMode()) {
        GlobalGraphics::shader_boxFrame.setUniform("frameColor", Color(1, 1, 1, 1));
    } else {
        GlobalGraphics::shader_boxFrame.setUniform("frameColor", Color(0, 0, 0, 1));
    }

    GlobalGraphics::mesh_boxFrame.draw();
}

void View::drawGameSelection() {
    if (Settings::isWireframeMode())
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    shader_gameSelection.useProgram();

    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, Vec3(0, 0.01, 0).toGlmVec3());
    shader_view.setUniform("modelMat", modelMat);

    GameSelection::draw();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void View::drawEntities() {
    GlobalGraphics::shader_3dBox.useProgram();

    for (const auto &entity: EntityList::getList()) {
        GlobalGraphics::shader_3dBox.setUniform("scale", entity->getSize());
        GlobalGraphics::shader_3dBox.setUniform("offset", entity->getOffset());
        GlobalGraphics::shader_3dBox.setUniform("color", Color(1, 1, 1, 1));

        glm::mat4 modelMat = glm::mat4(1.0f);
        modelMat = glm::translate(modelMat, entity->getPos().toGlmVec3());
        GlobalGraphics::shader_3dBox.setUniform("modelMat", modelMat);

        GlobalGraphics::mesh_3dBox.draw();
    }
}

#ifdef DEBUG
void View::drawDebug3D() {
    GlobalGraphics::shader_point.useProgram();

    for (const Debug3D::Point &point: Debug3D::getPointList()) {
        glPointSize(point.size);
        glm::mat4 modelMat = glm::mat4(1.0f);
        modelMat = glm::translate(modelMat, point.pos.toGlmVec3());
        GlobalGraphics::shader_point.setUniform("modelMat", modelMat);
        GlobalGraphics::shader_point.setUniform("pointColor", point.color);
        GlobalGraphics::mesh_point.draw();
    }

    glPointSize(1);
}
#endif
