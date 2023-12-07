#ifdef DEBUG

#include <Codes/Debug/debug3d.h>

std::vector<Debug3d::Point> Debug3d::pointList; 
std::vector<Debug3d::Surface> Debug3d::surfaceList; 

void Debug3d::update() {
    pointList.clear();
    surfaceList.clear();
}

void Debug3d::drawPoint(Vec3 pos, Color color, float size) {
    Point point;
    point.pos = pos;
    point.color = color;
    point.size = size;
    pointList.push_back(point);
}

void Debug3d::drawSurface(Vec3 pos, Color color, Vec2 size) {
    Surface surface;
    surface.pos = pos;
    surface.color = color;
    surface.size = size;
    surfaceList.push_back(surface);
}

#endif
