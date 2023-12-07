#ifdef DEBUG

#include <Codes/Debug/debug3d.h>

std::vector<Debug3d::Point> Debug3d::pointList; 
std::vector<Debug3d::Surface> Debug3d::surfaceList; 
std::vector<Debug3d::BoxFrame> Debug3d::boxFrameList; 

void Debug3d::update() {
    pointList.clear();
    surfaceList.clear();
    boxFrameList.clear();
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

void Debug3d::drawBoxFrame(Vec3 pos, Color color, Vec3 size, Vec3 margin) {
    BoxFrame boxFrame;
    boxFrame.pos = pos;
    boxFrame.color = color;
    boxFrame.size = size;
    boxFrame.margin = margin;
    boxFrameList.push_back(boxFrame);
}

#endif
