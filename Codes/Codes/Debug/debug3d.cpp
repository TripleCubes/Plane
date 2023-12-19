#ifdef DEBUG

#include <Codes/Debug/debug3d.h>

#include <Codes/Time/time.h>

#include <Codes/Debug/print.h>

std::vector<Debug3d::Point> Debug3d::pointList; 
std::vector<Debug3d::Line> Debug3d::lineList; 
std::vector<Debug3d::Surface> Debug3d::surfaceList; 
std::vector<Debug3d::BoxFrame> Debug3d::boxFrameList; 
std::vector<Debug3d::FadeBorderedSurface> Debug3d::fadeBorderedSurfaceList;
std::vector<Debug3d::Text> Debug3d::textList;

void Debug3d::update() {
    pointList.clear();
    lineList.clear();
    surfaceList.clear();
    boxFrameList.clear();
    textList.clear();
    
    for (FadeBorderedSurface &surface: fadeBorderedSurfaceList) {
        surface.time -= Time::getDeltaTime();
        float opacity = surface.time / surface.maxTime;

        Color surfaceColor = surface.surface.color;
        surfaceColor.a = opacity;
        addBorderedSurface(surface.surface.pos, surfaceColor, surface.surface.size);
    }

    for (std::size_t i = 0; i < fadeBorderedSurfaceList.size();) {
        if (fadeBorderedSurfaceList[i].time < 0) {
            fadeBorderedSurfaceList.erase(fadeBorderedSurfaceList.begin() + i);
        } else {
            i++;
        }
    }
}

void Debug3d::addPoint(Vec3 pos, Color color, float size) {
    Point point;
    point.pos = pos;
    point.color = color;
    point.size = size;
    pointList.push_back(point);
}

void Debug3d::addLine(Vec3 pos1, Vec3 pos2, Color color, float size) {
    Line line;
    line.pos1 = pos1;
    line.pos2 = pos2;
    line.color = color;
    line.size = size;
    lineList.push_back(line);
}

void Debug3d::addSurface(Vec3 pos, Color color, Vec2 size) {
    Surface surface;
    surface.pos = pos;
    surface.color = color;
    surface.size = size;
    surfaceList.push_back(surface);
}

void Debug3d::addBorderedSurface(Vec3 pos, Color color, Vec2 size) {
    pos.y += 1.001;
    
    float alpha = color.a;
    color.a = alpha*0.5;
    addSurface(pos, color, size);

    color.a = alpha;
    Vec3 pos_0 = Vec3(pos.x,            pos.y, pos.z            );
    Vec3 pos_1 = Vec3(pos.x + size.x,   pos.y, pos.z            );
    Vec3 pos_2 = Vec3(pos.x,            pos.y, pos.z + size.y   );
    Vec3 pos_3 = Vec3(pos.x + size.x,   pos.y, pos.z + size.y   );
    addLine(pos_0, pos_1, color, 2);
    addLine(pos_0, pos_2, color, 2);
    addLine(pos_3, pos_1, color, 2);
    addLine(pos_3, pos_2, color, 2);
}

void Debug3d::addFadeBorderedSurface(Vec3 pos, Color color, Vec2 size, float fadeTime) {
    FadeBorderedSurface surface;
    surface.surface.pos = pos;
    surface.surface.color = color;
    surface.surface.size = size;
    surface.time = fadeTime;
    surface.maxTime = fadeTime;
    fadeBorderedSurfaceList.push_back(surface);
}

void Debug3d::addBoxFrame(Vec3 pos, Color color, Vec3 size, Vec3 margin) {
    BoxFrame boxFrame;
    boxFrame.pos = pos;
    boxFrame.color = color;
    boxFrame.size = size;
    boxFrame.margin = margin;
    boxFrameList.push_back(boxFrame);
}

void Debug3d::addText(Vec3 pos, const std::string &text, Color color, bool centered) {
    Text _text;
    _text.pos = pos;
    _text.text = text;
    _text.color = color;
    _text.centered = centered;
    textList.push_back(_text);
}

#endif
