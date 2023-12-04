#include <Codes/GraphicTypes/shader.h>
#include <Codes/GraphicTypes/mesh.h>
#include <vector>

#include <Codes/Debug/print.h>

namespace GlobalGraphics {

Mesh mesh_windowRect;
Shader shader_windowRect;

Mesh mesh_3dBox;
Shader shader_3dBox;

Mesh mesh_point;
Shader shader_point;

void init() {
    std::vector<float> verticies_windowRect = {
        -1,  1,
         1,  1,
        -1, -1,
        
         1,  1,
         1, -1,
        -1, -1,
    };
    mesh_windowRect.init();
    mesh_windowRect.set(MeshType::MESH2D, verticies_windowRect);

    shader_windowRect.init("Shaders/windowRect");



    std::vector<float> verticies_3dBox = {
//      Pos           Normal
        -1,  1, -1,   0,  1,  0,  // A TOP
         1,  1,  1,   0,  1,  0,  // C
        -1,  1,  1,   0,  1,  0,  // D

        -1,  1, -1,   0,  1,  0,  // A
         1,  1, -1,   0,  1,  0,  // B
         1,  1,  1,   0,  1,  0,  // C

        -1, -1, -1,   0, -1,  0,  // E BOTTOM
        -1, -1,  1,   0, -1,  0,  // H
         1, -1,  1,   0, -1,  0,  // G

        -1, -1, -1,   0, -1,  0,  // E
         1, -1,  1,   0, -1,  0,  // G
         1, -1, -1,   0, -1,  0,  // F

        -1,  1, -1,  -1,  0,  0,  // A LEFT
        -1,  1,  1,  -1,  0,  0,  // D
        -1, -1,  1,  -1,  0,  0,  // H

        -1,  1, -1,  -1,  0,  0,  // A
        -1, -1,  1,  -1,  0,  0,  // H
        -1, -1, -1,  -1,  0,  0,  // E

         1,  1, -1,   1,  0,  0,  // B RIGHT
         1, -1,  1,   1,  0,  0,  // G
         1,  1,  1,   1,  0,  0,  // C

         1,  1, -1,   1,  0,  0,  // B
         1, -1, -1,   1,  0,  0,  // F
         1, -1,  1,   1,  0,  0,  // G

        -1,  1,  1,   0,  0,  1,  // D FORWARD
         1,  1,  1,   0,  0,  1,  // C
        -1, -1,  1,   0,  0,  1,  // H

         1,  1,  1,   0,  0,  1,  // C
         1, -1,  1,   0,  0,  1,  // G
        -1, -1,  1,   0,  0,  1,  // H

        -1,  1, -1,   0,  0, -1,  // A BACKWARD
        -1, -1, -1,   0,  0, -1,  // E
         1,  1, -1,   0,  0, -1,  // B

         1,  1, -1,   0,  0, -1,  // B
        -1, -1, -1,   0,  0, -1,  // E
         1, -1, -1,   0,  0, -1,  // F
    };
    mesh_3dBox.init();
    mesh_3dBox.set(MeshType::MESH3D, verticies_3dBox);
    shader_3dBox.init("Shaders/_3dBox");



    mesh_point.init();
    std::vector<float> verticies_point = {
        0, 0, 0,
    };
    mesh_point.set(MeshType::MESH3D_POINTS, verticies_point);

    shader_point.init("Shaders/Debug/point");
}
}
