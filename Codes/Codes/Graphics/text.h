#ifndef TEXT_H
#define TEXT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <vector>
#include <string>

const int FONT_HEIGHT = 24;

class Vec2;

struct TextCharacter
{
    unsigned int textureId;
    float w = 0;
    float h = 0;
    float bearingX = 0;
    float bearingY = 0;
    float advance = 0;
    float lineHeight = 0;
};

class Text {
public:
    static void init();
    static TextCharacter getCharacter(char characterCode);
    static Vec2 getTextBoxSize(const std::string &text);

private:
    static FT_Library library;
    static FT_Face face;

    static std::vector<TextCharacter> characters;
    static int firstCharacterCode;
};

#endif
