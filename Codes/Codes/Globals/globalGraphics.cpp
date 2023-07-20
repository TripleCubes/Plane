#include <Codes/GraphicTypes/shader.h>
#include <Codes/GraphicTypes/mesh.h>
#include <vector>

#include <Codes/Debug/print.h>

namespace GlobalGraphics {

Mesh mesh_windowRect;
Shader shader_windowRect;

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
}
}
