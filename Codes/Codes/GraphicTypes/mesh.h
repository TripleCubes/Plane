#ifndef SETABLEMESH_H
#define SETABLEMESH_H

#include <Codes/GraphicTypes/graphicTypeData.h>
#include <memory>
#include <vector>

class GraphicTypeData_Mesh;

enum class MeshType {
    MESH2D, 
    MESH3D,
    MESH3D_NO_NORMALS,
    MESH3D_POINTS,
    MESH3D_FRAME,
    MESH3D_COLOR_PALLETE, 
    MESH3D_TEXTURE,
    MESH3D_ARRAY_TEXTURE,
};

class Mesh {
public:
    Mesh(const Mesh&) = delete;
    Mesh &operator = (const Mesh&) = delete;

    Mesh();
    void init();
    ~Mesh();

    void set(MeshType meshType, const std::vector<float> &verticies);
    void set(MeshType meshType, const std::vector<float> &verticies, 
                const std::vector<unsigned int> &indicies);
    void draw() const;

private:
    std::shared_ptr<GraphicTypeData_Mesh> dataPtr;
};

class GraphicTypeData_Mesh: public GraphicTypeData {
public:
    void init();
    void release() override;

    void set(MeshType meshType, const std::vector<float> &verticies);
    void set(MeshType meshType, const std::vector<float> &verticies, 
                const std::vector<unsigned int> &indicies);
    void draw() const;

private:
    MeshType meshType;
    bool meshSetted = false;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    int numberOfVerticies = 0;
    bool hasIndicies = false;
    int numberOfIndicies = 0;

    void setEBO(const std::vector<unsigned int> &indicies);
};

#endif
