#ifndef BUTTON_H
#define BUTTON_H

#include <Codes/Types/color.h>
#include <string>

class Vec2;

class Button {
public:
    Button(const std::string &buttonTitle, float x, float y, float w, float h, 
                Color buttonColor, Color textColor);

    void update();
    void draw() const;

    void setScrolledY(float scrolledY);
    void setPos(float x, float y);
    Vec2 getPos() const;
    void setSize(float w, float h);
    Vec2 getSize() const;

    bool pressed() const;
    bool justPressed() const;
    void stickToMousePressX();
    void stickToMousePressY();
    void stickToMousePress();
    void capPosX(float minCap, float maxCap);
    void capPosY(float minCap, float maxCap);

private:
    std::string buttonTitle;
    float scrolledY = 0;
    float x = 0;
    float y = 0;
    float w = 100;
    float h = 100;
    Color buttonColor;
    Color textColor;

    bool hovered = false;
    bool status_pressed = false;
    bool status_justPressed = false;

    float mousePressOffsetX = 0;
    float mousePressOffsetY = 0;
};

#endif
