#ifdef DEBUG
    #ifndef DEBUG3D_H
    #define DEBUG3D_H

    #include <Codes/Types/vec3.h>
    #include <Codes/Types/vec2.h>
    #include <Codes/Types/color.h>
    #include <vector>

    #define DRAWPOINT(pos, color, size) Debug3d::addPoint(pos, color, size)
    #define DRAWLINE(pos1, pos2, color, size) Debug3d::addLine(pos1, pos2, color, size)
    #define DRAWSURFACE(pos, color, size) Debug3d::addBorderedSurface(pos, color, size)
    #define DRAWFADESURFACE(pos, color, size, fadeTime) Debug3d::addFadeBorderedSurface(pos, color, size, fadeTime);
    #define DRAWBOXFRAME(pos, color, size, margin) Debug3d::addBoxFrame(pos, color, size, margin)

    class Debug3d {
    public:
        struct Point {
            Vec3 pos;
            Color color;
            float size = 2;
        };
        struct Line {
            Vec3 pos1;
            Vec3 pos2;
            Color color;
            float size = 2;
        };
        struct Surface {
            Vec3 pos;
            Color color;
            Vec2 size;
        };
        struct BoxFrame {
            Vec3 pos;
            Color color;
            Vec3 size;
            Vec3 margin;
        };
        struct FadeBorderedSurface {
            Surface surface;
            float time = 1;
            float maxTime = 1;
        };

        static void update();

        static void addPoint(Vec3 pos, Color color, float size);
        static void addLine(Vec3 pos1, Vec3 pos2, Color color, float size);
        static void addSurface(Vec3 pos, Color color, Vec2 size);
        static void addBorderedSurface(Vec3 pos, Color color, Vec2 size);
        static void addFadeBorderedSurface(Vec3 pos, Color color, Vec2 size, float fadeTime);
        static void addBoxFrame(Vec3 pos, Color color, Vec3 size, Vec3 margin);
        static const std::vector<Point> &getPointList() { return pointList; };
        static const std::vector<Line> &getLineList() { return lineList; };
        static const std::vector<Surface> &getSurfaceList() { return surfaceList; };
        static const std::vector<BoxFrame> &getBoxFrameList() { return boxFrameList; };

    private:    
        static std::vector<Point> pointList;
        static std::vector<Line> lineList;
        static std::vector<Surface> surfaceList;
        static std::vector<BoxFrame> boxFrameList;
        static std::vector<FadeBorderedSurface> fadeBorderedSurfaceList;
    };

    #endif
#else
    #ifndef DEBUG3D_H
    #define DEBUG3D_H

    #define DRAWPOINT(pos, color, size)
    #define DRAWLINE(pos1, pos2, color, size)
    #define DRAWSURFACE(pos, color, size)
    #define DRAWFADESURFACE(pos, color, size, fadeTime)
    #define DRAWBOXFRAME(pos, color, size, margin)

    #endif
#endif
