#ifdef DEBUG
    #ifndef DEBUG3D_H
    #define DEBUG3D_H

    #include <Codes/Types/vec3.h>
    #include <Codes/Types/color.h>
    #include <vector>

    #define DRAWPOINT(a, b, c) Debug3D::drawPoint(a, b, c)

    class Debug3D {
    public:
        struct Point {
            Vec3 pos;
            Color color;
            float size = 2;
        };

        static void update();

        static void drawPoint(Vec3 pos, Color color, float size);
        static const std::vector<Point> &getPointList() { return pointList; }

    private:    
        static std::vector<Point> pointList;
    };

    #endif
#else
    #ifndef DEBUG3D_H
    #define DEBUG3D_H

    #define DRAWPOINT(a, b, c)

    #endif
#endif
