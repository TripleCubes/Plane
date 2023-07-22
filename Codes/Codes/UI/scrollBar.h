#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <Codes/Types/color.h>
#include <Codes/UI/button.h>

const float SCROLLBAR_WIDTH = 15;

class ScrollBar {
public:
    ScrollBar(float x, float y, float h, Color color);

    float getScrollValue() const;
    void setPageHeight(float visibleHeight, float pageHeight);

    void update();
    void draw() const;

private:
    float scrollValuePercentage = 0;
    float visibleHeight = 0;
    float pageHeight = 0;
    float x = 0;
    float y = 0;
    float h = 0;
    Color color;
    Button button;
};

#endif
