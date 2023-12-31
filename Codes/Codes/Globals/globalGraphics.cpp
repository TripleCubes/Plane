#include <Codes/GraphicTypes/shader.h>
#include <Codes/GraphicTypes/mesh.h>
#include <vector>

#include <Codes/Debug/print.h>

namespace GlobalGraphics {

// Draw a full screen rect with texture
Mesh mesh_windowRect;
Shader shader_windowRect;

// Draw a 3d box with all sides filled
Mesh mesh_3dBox;
Shader shader_3dBox;

Mesh mesh_point;
Shader shader_point;

Mesh mesh_line;
Shader shader_line;

Mesh mesh_surface;
Shader shader_surface;

Mesh mesh_UILine;
Shader shader_UILine;

// Draw a 3d box with all sides unfilled
Mesh mesh_boxFrame;
Shader shader_boxFrame;

Mesh mesh_3dText;
Mesh mesh_3dTextFlipped;
Shader shader_3dText;

void init_windowRect() {
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

    shader_windowRect.init("Shaders/Global/windowRect");
}

void init_3dBox() {
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
    shader_3dBox.init("Shaders/Global/_3dBox");
}

void init_point() {
    mesh_point.init();
    std::vector<float> verticies_point = {
        0, 0, 0,
    };
    mesh_point.set(MeshType::MESH3D_POINTS, verticies_point);

    shader_point.init("Shaders/Global/point");
}

void init_line() {
    mesh_line.init();
    std::vector<float> verticies_line = {
        0, 0, 0,
        1, 1, 1,
    };
    mesh_line.set(MeshType::MESH3D_FRAME, verticies_line);

    shader_line.init("Shaders/Global/line");
}

void init_surface() {
    mesh_surface.init();
    std::vector<float> verticies_surface = {
        0, 0, 0,
        1, 0, 0,
        0, 0, 1,
        1, 0, 1,
    };
    std::vector<unsigned int> indicies_surface = {
        0, 1, 2,
        1, 3, 2,
    };
    mesh_surface.set(MeshType::MESH3D_NO_NORMALS, verticies_surface, indicies_surface);
    shader_surface.init("Shaders/Global/surface");
}

void init_boxFrame() {
    mesh_boxFrame.init();
    std::vector<float> verticies_boxFrame = {
        0, 1, 0, // A 0
        1, 1, 0, // B 1
        1, 1, 1, // C 2
        0, 1, 1, // D 3
        0, 0, 0, // E 4
        1, 0, 0, // F 5
        1, 0, 1, // G 6
        0, 0, 1, // H 7
    };
    std::vector<unsigned int> indicies_boxFrame = {
        0, 1,
        1, 2,
        2, 3,
        3, 0,
        0, 4,
        1, 5,
        2, 6,
        3, 7,
        4, 5,
        5, 6,
        6, 7,
        7, 4
    };
    mesh_boxFrame.set(MeshType::MESH3D_FRAME, verticies_boxFrame, indicies_boxFrame);
    shader_boxFrame.init("Shaders/Global/boxFrame");
}

void init_UILine() {
    mesh_UILine.init();
    std::vector<float> verticies = {
        0, 0,
        1, 1,
    };
    mesh_UILine.set(MeshType::MESH2D_LINE, verticies);
    shader_UILine.init("Shaders/Global/_UILine");
}

void init_3dtext() {
    mesh_3dText.init();
    std::vector<float> verticies = {
        0, 0, 0,
        1, 0, 0,
        1, 1, 0,
        0, 1, 0,
    };
    std::vector<unsigned int> indicies {
        0, 3, 1,
        1, 3, 2,
    };
    mesh_3dText.set(MeshType::MESH3D_NO_NORMALS, verticies, indicies);

    mesh_3dTextFlipped.init();
    std::vector<unsigned int> indiciesFlipped {
        0, 1, 3,
        1, 2, 3,
    };
    mesh_3dTextFlipped.set(MeshType::MESH3D_NO_NORMALS, verticies, indiciesFlipped);

    shader_3dText.init("Shaders/Global/_3dText");
}

void init() {
    init_windowRect();
    init_3dBox();
    init_point();
    init_line();
    init_surface();
    init_boxFrame();
    init_UILine();
    init_3dtext();
}
}
