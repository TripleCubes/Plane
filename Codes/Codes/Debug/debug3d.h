#ifdef DEBUG
    #ifndef DEBUG3D_H
    #define DEBUG3D_H

    #include <Codes/Types/vec3.h>
    #include <Codes/Types/vec2.h>
    #include <Codes/Types/color.h>
    #include <vector>

    #define DRAWPOINT(pos, color, size) Debug3d::drawPoint(pos, color, size)
    #define DRAWSURFACE(pos, color, size) Debug3d::drawSurface(pos, color, size)
    #define DRAWBOXFRAME(pos, color, size, margin) Debug3d::drawBoxFrame(pos, color, size, margin)

    class Debug3d {
    public:
        struct Point {
            Vec3 pos;
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

        static void update();

        static void drawPoint(Vec3 pos, Color color, float size);
        static void drawSurface(Vec3 pos, Color color, Vec2 size);
        static void drawBoxFrame(Vec3 pos, Color color, Vec3 size, Vec3 margin);
        static const std::vector<Point> &getPointList() { return pointList; };
        static const std::vector<Surface> &getSurfaceList() { return surfaceList; };
        static const std::vector<BoxFrame> &getBoxFrameList() { return boxFrameList; };

    private:    
        static std::vector<Point> pointList;
        static std::vector<Surface> surfaceList;
        static std::vector<BoxFrame> boxFrameList;
    };

    #endif
#else
    #ifndef DEBUG3D_H
    #define DEBUG3D_H

    #define DRAWPOINT(pos, color, size)
    #define DRAWSURFACE(pos, color, size)
    #define DRAWBOXFRAME(pos, color, size, margin)

    #endif
#endif
