#ifdef DEBUG
    #ifndef DEBUGUI_H
    #define DEBUGUI_H

    #include <Codes/Types/vec2.h>
    #include <Codes/Types/vec3.h>
    #include <Codes/Types/intPos.h>
    #include <Codes/Types/color.h>
    #include <vector>
    #include <string>

    #define DRAWUITEXT(pos, str, color, centered) DebugUI::addDebugStr(pos, str, color, centered)
    #define DRAWUILINE(pos1, pos2, color, size) DebugUI::addLine(pos1, pos2, color, size)

    class DebugUI {
    public:
        struct DebugStr {
            std::string str;
            Vec2 pos;
            Color color;
            bool centered = false;
        };
        struct DebugStr3d {
            std::string str;
            Vec3 pos;
            Color color;
            bool centered = false;
        };
        struct Line {
            Vec2 pos1;
            Vec2 pos2;
            Color color;
            float size = 2;
        };

        static void update();

        static void addDebugStr(Vec2 pos, const std::string &str, Color color, bool centered);
        static void addDebugStr(Vec3 pos, const std::string &str, Color color, bool centered);
        static void addDebugStr(Vec2 pos, const char *text, Color color, bool centered);
        static void addDebugStr(Vec2 pos, int num, Color color, bool centered);
        static void addDebugStr(Vec2 pos, float num, Color color, bool centered);
        static void addDebugStr(Vec2 pos, Vec2 vec, Color color, bool centered);
        static void addDebugStr(Vec2 pos, Vec3 vec, Color color, bool centered);
        static void addDebugStr(Vec2 pos, IntPos intPos, Color color, bool centered);
        static void addDebugStr(Vec2 pos, bool b, Color color, bool centered);
        static const std::vector<DebugStr> &getDebugStrList() { return debugStrList; };
        static const std::vector<DebugStr3d> &getDebugStr3dList() { return debugStr3dList; };

        static void addLine(Vec2 pos1, Vec2 pos2, Color color, float size);
        static const std::vector<Line> &getLineList() { return lineList; };

    private:
        static std::vector<DebugStr> debugStrList;
        static std::vector<DebugStr3d> debugStr3dList;
        static std::vector<Line> lineList;
    };

    #endif
#else
    #ifndef DEBUGUI_H
    #define DEBUGUI_H

    #define DRAWUITEXT(pos, str, color, centered)
    #define DRAWUILINE(pos1, pos2, color, size)

    #endif
#endif
