#ifndef VEC2_H
#define VEC2_H

struct Vec2 {
    float x = 0;
    float y = 0;

    Vec2(float x, float y);
    Vec2();

    bool operator == (Vec2 vec) const;
    Vec2 operator + (Vec2 vec) const;
    Vec2 operator - (Vec2 vec) const;
    Vec2 operator * (float num) const;
    Vec2 operator / (float num) const;
    float length() const;
    float lengthSqr() const;
    Vec2 normalize() const;
    float getYFromX(Vec2 vec, float x) const;
};

#endif
