#ifndef COLOR_H
#define COLOR_H

struct Color {
    float r = 0;
    float g = 0;
    float b = 0;
    float a = 1;
    Color(float r, float g, float b, float a);
    Color();
    Color operator + (Color color) const;
    Color operator - (Color color) const;
};

#endif
