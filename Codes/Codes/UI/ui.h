#ifndef UI_H
#define UI_H

#include <string>
#include <memory>

class Color;
class Texture;
class Mesh;
class Shader;
class Menu;
struct TextCharacter;

class UI {
public:
    static void init();

    static void update();
    static void draw();

    static void drawRectPos(float x1, float y1, float x2, float y2, Color color);
    static void drawRectWH(float x, float y, float w, float h, Color color);
    static void drawTexture(float x, float y, float w, float h, const Texture &texture, bool centered = false);
    static void drawTexture(float x, float y, float w, float h, 
                            unsigned int textureId, int textureWidth, int textureHeight, 
                            bool centered = false);

    static void drawTextBox(float x, float y, const std::string &text, Color color);
    static void drawTextBox(float x, float y, const char *text, Color color);

private:
    static const int DRAWMODE_RECT = 0;
    static const int DRAWMODE_TEXTURE = 1;
    static const int DRAWMODE_TEXT = 2;

    static Mesh mesh_rect;
    static Shader shader_rect;

    static Texture texture_crosshair;

    static void drawTexture(bool isTextTexture, float x, float y, float w, float h, 
                            unsigned int textureId, int textureWidth, int textureHeight, 
                            Color textColor, bool centered);
    static TextCharacter drawTextChar(float x, float y, char characterCode, Color color);

    static std::shared_ptr<Menu> rootMenu;
    static void initMenus();

    #ifdef DEBUG
    static void drawDebugUIStrs();
    static void drawDebugUI3dStrs();
    static void drawDebugUILines();
    #endif
};

#endif
