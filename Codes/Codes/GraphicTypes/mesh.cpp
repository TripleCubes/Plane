#include <Codes/GraphicTypes/mesh.h>

#include <Codes/GraphicTypes/graphicTypesManager.h>
#include <glad/glad.h>

#include <Codes/Debug/print.h>

Mesh::Mesh() {}

void Mesh::init() {
    dataPtr = std::make_unique<GraphicTypeData_Mesh>();
    dataPtr->init();
    GraphicTypesManager::addGraphicTypeData(dataPtr);
}

Mesh::~Mesh() {
    dataPtr->release();
    GraphicTypesManager::removeGraphicTypeData(dataPtr);
}

void Mesh::set(MeshType meshType, const std::vector<float> &verticies) {
    dataPtr->set(meshType, verticies);
}

void Mesh::set(MeshType meshType, const std::vector<float> &verticies, 
            const std::vector<unsigned int> &indicies) {
    dataPtr->set(meshType, verticies, indicies);
}

void Mesh::draw() const {
    dataPtr->draw();
}



void GraphicTypeData_Mesh::init() {
    if (initialized) {
        LINEINFORMATION();
        PRINTLN("Mesh already initialized");
        return;
    }

    initialized = true;
}

void GraphicTypeData_Mesh::release() {
    if (released) {
        return;
    }

    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Cant release not initialized mesh");
        return;
    }

    if (meshSetted) {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        
        if (hasIndicies) {
            glDeleteBuffers(1, &EBO);
        }
    }

    released = true;
}

void GraphicTypeData_Mesh::set(MeshType meshType, const std::vector<float> &verticies, 
                                const std::vector<unsigned int> &indicies) {
    set(meshType, verticies);
    setEBO(indicies);
}

void GraphicTypeData_Mesh::set(MeshType meshType, const std::vector<float> &verticies) {
    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Mesh not initialized");
        return;
    }

    if (released) {
        LINEINFORMATION();
        PRINTLN("Mesh already released");
        return;
    }

    if (verticies.size() == 0) {
        LINEINFORMATION();
        PRINTLN("verticies.size() == 0");
        return;
    }

    if (meshSetted) {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        
        if (hasIndicies) {
            glDeleteBuffers(1, &EBO);
        }
    }

    this->meshType = meshType;
    hasIndicies = false;

    if (meshType == MeshType::MESH2D) {
        numberOfVerticies = verticies.size() / 2;
    } else if (meshType == MeshType::MESH3D) {
        numberOfVerticies = verticies.size() / 6;
    } else if (meshType == MeshType::MESH3D_COLOR_PALLETE) {
        numberOfVerticies = verticies.size() / 7;
    } else if (meshType == MeshType::MESH3D_FRAME) {
        numberOfVerticies = verticies.size() / 3;
    } else if (meshType == MeshType::MESH3D_TEXTURE) {
        numberOfVerticies = verticies.size() / 8;
    } else if (meshType == MeshType::MESH3D_ARRAY_TEXTURE) {
        numberOfVerticies = verticies.size() / 9;
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), &verticies[0], GL_STATIC_DRAW);

    if (meshType == MeshType::MESH2D) {
        // Pos
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
    } else if (meshType == MeshType::MESH3D) {
       // Pos
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // Normal
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    } else if (meshType == MeshType::MESH3D_COLOR_PALLETE) {
        // Pos
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // Normal
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // Color index
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    } else if (meshType == MeshType::MESH3D_FRAME) {
        // Pos
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
    } else if (meshType == MeshType::MESH3D_TEXTURE) {
        // Pos
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // Normal
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // UV
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    } else if (meshType == MeshType::MESH3D_ARRAY_TEXTURE) {
        // Pos
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // Normal
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // UV
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        // Layer
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(8 * sizeof(float)));
        glEnableVertexAttribArray(3);
    }

    meshSetted = true;
}

void GraphicTypeData_Mesh::setEBO(const std::vector<unsigned int> &indicies) {
    hasIndicies = true;
    numberOfIndicies = indicies.size();
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(float), &indicies[0], GL_STATIC_DRAW);
}

void GraphicTypeData_Mesh::draw() const {
    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Mesh not initialized");
        return;
    }

    if (released) {
        LINEINFORMATION();
        PRINTLN("Mesh already released");
        return;
    }

    if (!meshSetted) {
        LINEINFORMATION();
        PRINTLN("Mesh is not setted");
        return;
    }

    glBindVertexArray(VAO);

    if (meshType == MeshType::MESH3D_FRAME) {
        if (hasIndicies) {
            glDrawElements(GL_LINES, numberOfIndicies, GL_UNSIGNED_INT, 0);
        } else {
            glDrawArrays(GL_LINES, 0, numberOfVerticies);
        }

        return;
    }

    if (hasIndicies) {
        glDrawElements(GL_TRIANGLES, numberOfIndicies, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, numberOfVerticies);
    }
}
