#ifdef DEBUG

#include <Codes/Debug/debugUI.h>

std::vector<DebugUI::DebugStr> DebugUI::debugStrList;
std::vector<DebugUI::DebugStr3d> DebugUI::debugStr3dList;
std::vector<DebugUI::Line> DebugUI::lineList;

void DebugUI::update() {
    debugStrList.clear();
    debugStr3dList.clear();
    lineList.clear();
}

void DebugUI::addDebugStr(const std::string &str, Vec2 pos, Color color) {
    DebugStr debugStr;
    debugStr.str = str;
    debugStr.pos = pos;
    debugStr.color = color;
    debugStrList.push_back(debugStr);
}

void DebugUI::addDebugStr(const std::string &str, Vec3 pos, Color color) {
    DebugStr3d debugStr3d;
    debugStr3d.str = str;
    debugStr3d.pos = pos;
    debugStr3d.color = color;
    debugStr3dList.push_back(debugStr3d);
}

void DebugUI::addDebugStr(const char *text, Vec2 pos, Color color) {
    std::string str(text);
    addDebugStr(str, pos, color);
}

void DebugUI::addDebugStr(int num, Vec2 pos, Color color) {
    std::string str = std::to_string(num);
    addDebugStr(str, pos, color);
}

void DebugUI::addDebugStr(float num, Vec2 pos, Color color) {
    std::string str = std::to_string(num);
    addDebugStr(str, pos, color);
}

void DebugUI::addDebugStr(Vec2 vec, Vec2 pos, Color color) {
    std::string str = std::to_string(vec.x) + " " + std::to_string(vec.y);
    addDebugStr(str, pos, color);
}

void DebugUI::addDebugStr(Vec3 vec, Vec2 pos, Color color) {
    std::string str = std::to_string(vec.x) + " " + std::to_string(vec.y) + " " + std::to_string(vec.z);
    addDebugStr(str, pos, color);
}

void DebugUI::addDebugStr(IntPos intPos, Vec2 pos, Color color) {
    std::string str = std::to_string(intPos.x) + " " + std::to_string(intPos.y) + " " + std::to_string(intPos.z);
    addDebugStr(str, pos, color);
}

void DebugUI::addDebugStr(bool b, Vec2 pos, Color color) {
    addDebugStr(b? "true" : "false", pos, color);
}

void DebugUI::addLine(Vec2 pos1, Vec2 pos2, Color color, float size) {
    Line line;
    line.pos1 = pos1;
    line.pos2 = pos2;
    line.color = color;
    line.size = size;
    lineList.push_back(line);
}

#endif
