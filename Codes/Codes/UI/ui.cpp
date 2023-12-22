#include <Codes/UI/ui.h>

#include <Codes/GraphicTypes/mesh.h>
#include <Codes/GraphicTypes/shader.h>
#include <Codes/GraphicTypes/texture.h>
#include <Codes/Types/vec2.h>
#include <Codes/Types/color.h>
#include <Codes/Settings/settings.h>
#include <Codes/UI/Menu/menu.h>
#include <Codes/UI/Menu/menuManager.h>
#include <Codes/Input/input.h>
#include <Codes/Graphics/text.h>
#include <glad/glad.h>

#ifdef DEBUG
#include <Codes/View/view.h>
#include <Codes/View/camera.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#endif

#include <Codes/UI/debugUI.h>

#include <Codes/Debug/debugUI.h>

#include <Codes/Debug/print.h>

extern int currentWindowWidth;
extern int currentWindowHeight;

namespace GlobalGraphics {
    extern Mesh mesh_UILine;
    extern Shader shader_UILine;
}

Mesh UI::mesh_rect;
Shader UI::shader_rect;

Texture UI::texture_crosshair;

std::shared_ptr<Menu> UI::rootMenu = std::make_shared<Menu>("Root");

void UI::init() {
    mesh_rect.init();
    std::vector<float> rectVerticies = {
        0, 1,
        1, 1,
        0, 0,
        
        1, 1,
        1, 0,
        0, 0,
    };
    mesh_rect.set(MeshType::MESH2D, rectVerticies);

    shader_rect.init("Shaders/UI/rect");
    shader_rect.useProgram();
    shader_rect.setUniform("windowSize", Vec2((float)currentWindowWidth, (float)currentWindowHeight));

    texture_crosshair.init("Textures/UI/crosshair.png");

    GlobalGraphics::shader_UILine.useProgram();
    GlobalGraphics::shader_UILine.setUniform("windowSize", Vec2((float)currentWindowWidth, (float)currentWindowHeight));

    initMenus();
}

void UI::initMenus() {
    rootMenu->addSelfSharedPtr(rootMenu);

    rootMenu->addSubMenu("Pause");

    rootMenu->getSubMenu("Pause")->addSubMenu("Settings");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub1");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub2");
    
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub1");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub2");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub1");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub2");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub1");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub2");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub1");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub2");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub1");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub2");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub1");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub2");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub1");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub2");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub1");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub2");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub1");
    rootMenu->getSubMenu("Pause")->getSubMenu("Settings")->addSubMenu("SubSub2");

    rootMenu->getSubMenu("Pause")->addSubMenu("Settings 2");
    rootMenu->getSubMenu("Pause")->addSubMenu("Settings 3");
}

void UI::update() {
    MenuManager::update();

    if (Input::justPressed("ESC")) {
        if (MenuManager::isAllMenusClosed()) {
            rootMenu->getSubMenu("Pause")->open();
        } else {
            MenuManager::goBackOneMenu();
        }
    }
}

void UI::draw() {
    if (Settings::isFreeCam()) {
        drawTexture(currentWindowWidth/2, currentWindowHeight/2,
                    texture_crosshair.getTextureWidth(), texture_crosshair.getTextureHeight(), 
                    texture_crosshair, true);
    }

    MenuManager::draw();

    // TO DO: Replace with actual optimized debug ui code
    drawDebugUI();

    #ifdef DEBUG
    drawDebugUIStrs();
    drawDebugUI3dStrs();
    drawDebugUILines();
    #endif
}

void UI::drawRectPos(float x1, float y1, float x2, float y2, Color color) {
    if (x1 > x2) {
        float x3 = x1;
        x1 = x2;
        x2 = x3;
    }
    if (y1 > y2) {
        float y3 = y1;
        y1 = y2;
        y2 = y3;
    }

    float y3 = y1;
    y1 = currentWindowHeight - y2;
    y2 = currentWindowHeight - y3;

    shader_rect.useProgram();
    shader_rect.setUniform("rectPos", Vec2(x1, y1));
    shader_rect.setUniform("rectSize", Vec2(x2 - x1, y2 - y1));
    shader_rect.setUniform("drawMode", DRAWMODE_RECT);
    shader_rect.setUniform("drawColor", color);

    mesh_rect.draw();
}

void UI::drawRectWH(float x, float y, float w, float h, Color color) {
    drawRectPos(x, y, x + w, y + h, color);
}

void UI::drawTexture(float x, float y, float w, float h, const Texture &texture, bool centered) {
    drawTexture(x, y, w, h, texture.getTextureId(), texture.getTextureWidth(), texture.getTextureHeight(), centered);
}

void UI::drawTexture(float x, float y, float w, float h, 
                    unsigned int textureId, int textureWidth, int textureHeight, 
                    bool centered) {
    drawTexture(false, x, y, w, h, textureId, textureWidth, textureHeight, Color(0, 0, 0, 0), centered);
}

void UI::drawTexture(bool isTextTexture, float x, float y, float w, float h, 
                    unsigned int textureId, int textureWidth, int textureHeight, 
                    Color textColor, bool centered) {
    if (w < 0) {
        LINEINFORMATION();
        PRINTLN("w < 0");
        return;
    }
    if (h < 0) {
        LINEINFORMATION();
        PRINTLN("h < 0");
        return;
    }
    if (w == 0 && h == 0) {
        LINEINFORMATION();
        PRINTLN("w == 0 && h == 0");
        return;
    }
    
    if (h == 0) {
        h = (float)textureHeight / (float)textureWidth * w;
    } else if (w == 0) {
        w = (float)textureWidth / (float)textureHeight * h;
    }

    y = currentWindowHeight - y - h;

    if (centered) {
        x -= w/2;
        y += h/2;
    }

    shader_rect.useProgram();
    shader_rect.setUniform("rectPos", Vec2(x, y));
    shader_rect.setUniform("rectSize", Vec2(w, h));
    shader_rect.setUniform("drawMode", isTextTexture? DRAWMODE_TEXT : DRAWMODE_TEXTURE);
    if (isTextTexture) {
        shader_rect.setUniform("drawColor", textColor);
    }
    shader_rect.setTextureUniform("rectTexture", textureId, 0, false);

    mesh_rect.draw();
}

void UI::drawTextBox(float x, float y, const std::string &text, Color color, bool centered) {
    Vec2 textBoxSize;
    if (centered) {
        textBoxSize = Text::getTextBoxSize(text);
    }

    int cursorX = x - textBoxSize.x / 2;
    int cursorY = y;
    for (std::size_t i = 0; i < text.size(); i++)
    {
        TextCharacter drawnCharacter = drawTextChar(cursorX, cursorY, text[i], color);
        cursorX += drawnCharacter.advance;
    }
}

void UI::drawTextBox(float x, float y, const char *text, Color color, bool centered) {
    std::string string(text);
    drawTextBox(x, y, string, color, centered);
}

TextCharacter UI::drawTextChar(float x, float y, char characterCode, Color color) {
    TextCharacter character = Text::getCharacter(characterCode);
    if (characterCode != 32) {
        drawTexture(true, x + character.bearingX, y + FONT_HEIGHT - character.bearingY, character.w, character.h, 
        character.textureId, character.w, character.h, color, false);
    }

    return character;
}

#ifdef DEBUG
void UI::drawDebugUIStrs() {
    for (const auto &debugStr: DebugUI::getDebugStrList()) {
        drawTextBox(debugStr.pos.x, debugStr.pos.y, debugStr.str, debugStr.color, debugStr.centered);
    }
}

void UI::drawDebugUI3dStrs() {
    for (const auto &debugStr3d: DebugUI::getDebugStr3dList()) {
        Vec3 dirStr = debugStr3d.pos - Camera::getPos();
        if (dirStr.dot(Camera::getDir()) < 0) {
            continue;
        }

        glm::vec4 newPos = View::getProjectionMat() * View::getViewMat() * glm::vec4(debugStr3d.pos.x, 
                                                                                        debugStr3d.pos.y, 
                                                                                        debugStr3d.pos.z,
                                                                                        1.0f); 
        Vec2 newNewPos = Vec2(newPos.x, newPos.y);
        newNewPos = newNewPos / newPos.w;
        newNewPos = newNewPos + Vec2(1, 1);
        newNewPos = newNewPos / 2;
        newNewPos.y = 1 - newNewPos.y;
        drawTextBox(newNewPos.x * currentWindowWidth, newNewPos.y * currentWindowHeight, 
                    debugStr3d.str, debugStr3d.color, debugStr3d.centered);
    }
}

void UI::drawDebugUILines() {
    GlobalGraphics::shader_UILine.useProgram();

    for (const auto &line: DebugUI::getLineList()) {
        glLineWidth(line.size);
        float y1 = currentWindowHeight - line.pos1.y;
        float y2 = currentWindowHeight - line.pos2.y;
        GlobalGraphics::shader_UILine.setUniform("pos1", Vec2(line.pos1.x, y1));
        GlobalGraphics::shader_UILine.setUniform("pos2", Vec2(line.pos2.x, y2));
        GlobalGraphics::shader_UILine.setUniform("color", line.color);
        GlobalGraphics::mesh_UILine.draw();
    }

    glLineWidth(1);
}
#endif
