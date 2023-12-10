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

    class DebugUI {
    public:
        struct DebugStr {
            std::string str;
            Vec2 pos;
            Color color;
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

    private:
        static std::vector<DebugStr> debugStrList;
    };

    #endif
#else
    #ifndef DEBUGUI_H
    #define DEBUGUI_H

    #define DRAWUITEXT(str, pos, color)

    #endif
#endif
