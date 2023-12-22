#include <Codes/UI/button.h>

#include <Codes/UI/ui.h>
#include <Codes/Input/input.h>
#include <Codes/Types/vec2.h>

#include <Codes/Debug/print.h>

Button::Button(const std::string &buttonTitle, float x, float y, float w, float h, 
                Color buttonColor, Color textColor):
buttonTitle(buttonTitle), x(x), y(y), w(w), h(h), 
buttonColor(buttonColor), textColor(textColor) {}

void Button::update() {
    Vec2 mousePos = Input::getMousePos();
    
    hovered = false;
    if (mousePos.x >= x && mousePos.x <= x + w && mousePos.y >= y + scrolledY && mousePos.y <= y + scrolledY + h) {
        hovered = true;
    }

    status_justPressed = false;
    if (hovered && Input::justPressed(MouseButton::LEFT)) {
        status_justPressed = true;
        status_pressed = true;
    }

    if (!Input::pressed(MouseButton::LEFT)) {
        status_pressed = false;
    }
}

void Button::draw() const {
    if (!justPressed() && pressed()) {
        UI::drawRectWH(x, y + scrolledY, w, h, Color(1, 1, 1, 1));
    } else if (hovered) {
        UI::drawRectWH(x, y + scrolledY, w, h, buttonColor + Color(0.1, 0.1, 0.1, 1));
    } else {
        UI::drawRectWH(x, y + scrolledY, w, h, buttonColor);
    }
    UI::drawTextBox(x + 10, y + scrolledY + 5, buttonTitle, textColor, false);
}

void Button::setScrolledY(float scrolledY) {
    this->scrolledY = scrolledY;
}

void Button::setPos(float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2 Button::getPos() const {
    return Vec2(x, y);
}

void Button::setSize(float w, float h) {
    this->w = w;
    this->h = h;
}

Vec2 Button::getSize() const {
    return Vec2(w, h);
}

bool Button::pressed() const {
    return status_pressed;
}

bool Button::justPressed() const {
    return status_justPressed;
}

void Button::stickToMousePressX() {
    if (justPressed()) {
        Vec2 mousePos = Input::getMousePos();
        mousePressOffsetX = mousePos.x - x;

        return;
    }

    if (pressed()) {
        Vec2 mousePos = Input::getMousePos();
        x = mousePos.x - mousePressOffsetX;

        return;
    }
}

void Button::stickToMousePressY() {
    if (justPressed()) {
        Vec2 mousePos = Input::getMousePos();
        mousePressOffsetY = mousePos.y - y;

        return;
    }

    if (pressed()) {
        Vec2 mousePos = Input::getMousePos();
        y = mousePos.y - mousePressOffsetY;

        return;
    }
}

void Button::stickToMousePress() {
    stickToMousePressX();
    stickToMousePressY();
}

void Button::capPosX(float minCap, float maxCap) {
    if (x < minCap) {
        x = minCap;
    } else if (x + w > maxCap) {
        x = maxCap - w;
    }
}

void Button::capPosY(float minCap, float maxCap) {
    if (y < minCap) {
        y = minCap;
    } else if (y + h > maxCap) {
        y = maxCap - h;
    }
}
