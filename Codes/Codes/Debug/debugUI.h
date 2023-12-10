#ifdef DEBUG
    #ifndef DEBUGUI_H
    #define DEBUGUI_H

    #include <Codes/Types/vec2.h>
    #include <Codes/Types/vec3.h>
    #include <Codes/Types/intPos.h>
    #include <Codes/Types/color.h>
    #include <vector>
    #include <string>

    #define DRAWUITEXT(str, pos, color) DebugUI::addDebugStr(str, pos, color)
    #define DRAWUILINE(pos1, pos2, color, size) DebugUI::addLine(pos1, pos2, color, size)

    class DebugUI {
    public:
        struct DebugStr {
            std::string str;
            Vec2 pos;
            Color color;
        };
        struct Line {
            Vec2 pos1;
            Vec2 pos2;
            Color color;
            float size = 2;
        };

        static void update();

        static void addDebugStr(const std::string &str, Vec2 pos, Color color);
        static void addDebugStr(const char *text, Vec2 pos, Color color);
        static void addDebugStr(int num, Vec2 pos, Color color);
        static void addDebugStr(float num, Vec2 pos, Color color);
        static void addDebugStr(Vec2 vec, Vec2 pos, Color color);
        static void addDebugStr(Vec3 vec, Vec2 pos, Color color);
        static void addDebugStr(IntPos intPos, Vec2 pos, Color color);
        static void addDebugStr(bool b, Vec2 pos, Color color);
        static const std::vector<DebugStr> &getDebugStrList() { return debugStrList; };

        static void addLine(Vec2 pos1, Vec2 pos2, Color color, float size);
        static const std::vector<Line> &getLineList() { return lineList; };

    private:
        static std::vector<DebugStr> debugStrList;
        static std::vector<Line> lineList;
    };

    #endif
#else
    #ifndef DEBUGUI_H
    #define DEBUGUI_H

    #define DRAWUITEXT(str, pos, color)
    #define DRAWUILINE(pos1, pos2, color, size)

    #endif
#endif
