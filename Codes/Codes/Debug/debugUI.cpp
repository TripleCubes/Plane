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

void DebugUI::addDebugStr(Vec2 pos, const std::string &str, Color color, bool centered) {
    DebugStr debugStr;
    debugStr.str = str;
    debugStr.pos = pos;
    debugStr.color = color;
    debugStr.centered = centered;
    debugStrList.push_back(debugStr);
}

void DebugUI::addDebugStr(Vec3 pos, const std::string &str, Color color, bool centered) {
    DebugStr3d debugStr3d;
    debugStr3d.str = str;
    debugStr3d.pos = pos;
    debugStr3d.color = color;
    debugStr3d.centered = centered;
    debugStr3dList.push_back(debugStr3d);
}

void DebugUI::addDebugStr(Vec2 pos, const char *text, Color color, bool centered) {
    std::string str(text);
    addDebugStr(pos, str, color, centered);
}

void DebugUI::addDebugStr(Vec2 pos, int num, Color color, bool centered) {
    std::string str = std::to_string(num);
    addDebugStr(pos, str, color, centered);
}

void DebugUI::addDebugStr(Vec2 pos, float num, Color color, bool centered) {
    std::string str = std::to_string(num);
    addDebugStr(pos, str, color, centered);
}

void DebugUI::addDebugStr(Vec2 pos, Vec2 vec, Color color, bool centered) {
    std::string str = std::to_string(vec.x) + " " + std::to_string(vec.y);
    addDebugStr(pos, str, color, centered);
}

void DebugUI::addDebugStr(Vec2 pos, Vec3 vec, Color color, bool centered) {
    std::string str = std::to_string(vec.x) + " " + std::to_string(vec.y) + " " + std::to_string(vec.z);
    addDebugStr(pos, str, color, centered);
}

void DebugUI::addDebugStr(Vec2 pos, IntPos intPos, Color color, bool centered) {
    std::string str = std::to_string(intPos.x) + " " + std::to_string(intPos.y) + " " + std::to_string(intPos.z);
    addDebugStr(pos, str, color, centered);
}

void DebugUI::addDebugStr(Vec2 pos, bool b, Color color, bool centered) {
    addDebugStr(pos, b? "true" : "false", color, centered);
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
