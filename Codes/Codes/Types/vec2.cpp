#include <Codes/Types/vec2.h>

#include <Codes/Globals/pi.h>
#include <cmath>

#include <Codes/Debug/print.h>

extern int currentWindowWidth;
extern int currentWindowHeight;

Vec2::Vec2(float x, float y): x(x), y(y) {}
Vec2::Vec2() {}

float Vec2::dot(Vec2 vec1, Vec2 vec2) {
    return vec1.x*vec2.x + vec1.y*vec2.y;
}

float Vec2::angleRad(Vec2 vec1, Vec2 vec2) {
    float dot = Vec2::dot(vec1, vec2);
    float det = vec1.x*vec2.y - vec1.y*vec2.x;
    return std::atan2(det, dot);
}

float Vec2::angleDeg(Vec2 vec1, Vec2 vec2) {
    return radToDeg(angleRad(vec1, vec2));
}

bool Vec2::operator == (Vec2 vec) const {
    return x==vec.x && y==vec.y;
}

Vec2 Vec2::operator + (Vec2 vec) const {
    return Vec2(x+vec.x, y+vec.y);
}

Vec2 Vec2::operator - (Vec2 vec) const {
    return Vec2(x-vec.x, y-vec.y);
}

Vec2 Vec2::operator * (float num) const {
    return Vec2(x*num, y*num);
}

Vec2 Vec2::operator / (float num) const {
    return Vec2(x/num, y/num);
}

float Vec2::length() const {
    return sqrt(x*x + y*y);
}

float Vec2::lengthSqr() const {
    return x*x + y*y;
}

Vec2 Vec2::normalize() const {
    if (*this == Vec2(0, 0)) {
        LINEINFORMATION();
        PRINTLN("Cant normalize Vec2(0, 0)"); 
        return Vec2(0, 0);
    }

    return *this / this->length();
}

float Vec2::getYFromX(Vec2 vec, float x) const {
    Vec2 differentsVec = vec - Vec2(this->x, this->y);
    if (differentsVec.x == 0)
    {
        LINEINFORMATION();
        PRINTLN("differentsVec.x == 0");
        return this->y;
    }
    if (differentsVec.y == 0)
    {
        return this->y;
    }
    if (x == this->x)
    {
        return this->y;
    }
    if (x == vec.x)
    {
        return vec.y;
    }
    
    float m = (this->y - vec.y)/(this->x - vec.x);
    float a = this->y - m*this->x;
    return m*x + a;
}

Vec2 Vec2::toNormalizedScreenCoord() const {
    return Vec2((x / (float)currentWindowWidth) * 2 - 1,
                - ((y / (float)currentWindowHeight) * 2 - 1));
}

Vec2 Vec2::rotateRad(float rad) {
    return Vec2(x*std::cos(rad) - y*std::sin(rad),
                x*std::sin(rad) + y*std::cos(rad));
}

Vec2 Vec2::rotateDeg(float deg) {
    return rotateRad(degToRad(deg));
}
