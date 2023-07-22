#include <Codes/UI/scrollBar.h>

#include <Codes/UI/ui.h>
#include <Codes/Types/vec2.h>

#include <Codes/Debug/print.h>

ScrollBar::ScrollBar(float x, float y, float h, Color color): x(x), y(y), h(h), color(color),
button("", x, y, SCROLLBAR_WIDTH, 50, color, Color(0, 0, 0, 1)) {}

float ScrollBar::getScrollValue() const {
    return -scrollValuePercentage * (pageHeight - visibleHeight);
}

void ScrollBar::setPageHeight(float visibleHeight, float pageHeight) {
    this->visibleHeight = visibleHeight;
    this->pageHeight = pageHeight;
    if (pageHeight < visibleHeight) {
        return;
    }

    float r = visibleHeight / pageHeight;
    button.setSize(SCROLLBAR_WIDTH, h * r);
}

void ScrollBar::update() {
    if (pageHeight < visibleHeight) {
        return;
    }

    button.update();
    button.stickToMousePressY(y, y + h);

    scrollValuePercentage = (button.getPos().y - y) / (h - button.getSize().y);
}

void ScrollBar::draw() const {
    if (pageHeight < visibleHeight) {
        return;
    }

    UI::drawRectWH(x, y, SCROLLBAR_WIDTH, h, color - Color(0.1, 0.1, 0.1, 0));
    button.draw();
}
