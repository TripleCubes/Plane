#ifdef DEBUG

#include <Codes/Debug/debug3d.h>

std::vector<Debug3D::Point> Debug3D::pointList; 

void Debug3D::update() {
    pointList.clear();
}

void Debug3D::drawPoint(Vec3 pos, Color color, float size) {
    Point point;
    point.pos = pos;
    point.color = color;
    point.size = size;
    pointList.push_back(point);
}

#endif
