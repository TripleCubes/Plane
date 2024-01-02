#include <Codes/Game/GameSelection/gameSelection.h>

#include <Codes/Chunks/chunkLoader.h>
#include <Codes/Chunks/chunk.h>
#include <Codes/Types/vec3.h>
#include <Codes/Globals/globalConsts.h>
#include <algorithm>
#include <cmath>

#include <Codes/Debug/print.h>

bool GameSelection::selecting = false;
IntPos GameSelection::selectionStart;
IntPos GameSelection::selectionEnd;
Mesh GameSelection::mesh;
bool GameSelection::meshSetted = false;

void GameSelection::init() {
    mesh.init();
}

void GameSelection::startSelection(IntPos pos) {
    selecting = true;
    selectionStart = pos;
}

void GameSelection::setSelectionEndPos(IntPos pos) {
    if (selectionEnd == pos) {
        return;
    }

    selectionEnd = pos;
    updateMesh();
}

void GameSelection::endSelection(IntPos pos) {
    setSelectionEndPos(pos);
    selecting = false;
}

void GameSelection::discardSelection() {
    selecting = false;
    selectionStart = IntPos(0, 0, 0);
    selectionEnd = IntPos(0, 0, 0);
    updateMesh();
}

IntPos GameSelection::getSelectionTopLeft() {
    return IntPos(std::min(selectionStart.x, selectionEnd.x), 
                    std::min(selectionStart.y, selectionEnd.y), 
                    std::min(selectionStart.z, selectionEnd.z));
}

IntPos GameSelection::getSelectionBottomRight() {
    return IntPos(std::max(selectionStart.x, selectionEnd.x), 
                    std::max(selectionStart.y, selectionEnd.y), 
                    std::max(selectionStart.z, selectionEnd.z));
}

void GameSelection::updateMesh() {
    std::unordered_map<IntPos, bool, IntPosHash> faceCheckedList;
    std::vector<IntPos> faceCheckedListOrder;
    createFaceCheckedList(faceCheckedList, faceCheckedListOrder);

    std::vector<Surface> surfaceList;
    createSurfaceList(surfaceList, faceCheckedList, faceCheckedListOrder);

    if (surfaceList.size() == 0) {
        meshSetted = false;
        return;
    }

    std::vector<float> verticies;
    createVerticies(verticies, surfaceList);

    mesh.set(MeshType::MESH3D, verticies);

    meshSetted = true;
}

void GameSelection::draw() {
    if (!meshSetted) {
        return;
    }

    mesh.draw();
}

void GameSelection::createFaceCheckedList(std::unordered_map<IntPos, bool, IntPosHash> &faceCheckedList,
                                            std::vector<IntPos> &faceCheckedListOrder) {
    int minX = std::min(selectionStart.x, selectionEnd.x);
    int minY = std::min(selectionStart.y, selectionEnd.y);
    int minZ = std::min(selectionStart.z, selectionEnd.z);
    int maxX = std::max(selectionStart.x, selectionEnd.x);
    int maxY = std::max(selectionStart.y, selectionEnd.y);
    int maxZ = std::max(selectionStart.z, selectionEnd.z);

    int minChunkX = IntPos::getChunkPos(minX);
    int minChunkY = IntPos::getChunkPos(minY);
    int minChunkZ = IntPos::getChunkPos(minZ);
    int maxChunkX = IntPos::getChunkPos(maxX);
    int maxChunkY = IntPos::getChunkPos(maxY);
    int maxChunkZ = IntPos::getChunkPos(maxZ);

    const auto &chunkList = ChunkLoader::getChunkList();

    for (int chunkX = minChunkX; chunkX <= maxChunkX; chunkX++) {
    for (int chunkY = minChunkY; chunkY <= maxChunkY; chunkY++) {
    for (int chunkZ = minChunkZ; chunkZ <= maxChunkZ; chunkZ++) {
        IntPos chunkPos = IntPos(chunkX, chunkY, chunkZ);

        if (!ChunkLoader::chunkLoaded(chunkPos)) {
            if (chunkPos.y != IntPos::getChunkPos(GROUND_HEIGHT)) {
                continue;
            }

            for (int i = 0; i < CHUNK_VOLUME; i++) {
                IntPos blockPos = Chunk::indexToPos(i) + chunkPos * CHUNK_WIDTH;

                if (blockPos.y != GROUND_HEIGHT) {
                    continue;
                }

                if (blockPos.x < minX || blockPos.x > maxX 
                || blockPos.y < minY || blockPos.y > maxY
                || blockPos.z < minZ || blockPos.z > maxZ) {
                    continue;
                }

                faceCheckedList.insert(std::make_pair(blockPos, false));
                faceCheckedListOrder.push_back(blockPos);
            }

            continue;
        }

        const auto &chunk = chunkList.at(chunkPos);
        for (int i = 0; i < CHUNK_VOLUME; i++) {
            IntPos blockPos = Chunk::indexToPos(i) + chunkPos * CHUNK_WIDTH;

            if (blockPos.y != GROUND_HEIGHT && !chunk->isSolidBlock(i)) {
                continue;
            }

            if (blockPos.x < minX || blockPos.x > maxX 
            || blockPos.y < minY || blockPos.y > maxY
            || blockPos.z < minZ || blockPos.z > maxZ) {
                continue;
            }

            // TO DO: Handle above chunk
            if (blockPos.y < CHUNK_VOLUME - 1 && chunk->isSolidBlock(Chunk::addYToIndex(1, i))) {
                continue;
            }

            faceCheckedList.insert(std::make_pair(blockPos, false));
            faceCheckedListOrder.push_back(blockPos);
        }
    }
    }
    }
}

void GameSelection::createSurfaceList(std::vector<Surface> &surfaceList, 
                                        std::unordered_map<IntPos, bool, IntPosHash> &faceCheckedList,
                                        std::vector<IntPos> &faceCheckedListOrder) {
    for (auto facePos: faceCheckedListOrder) {
        if (faceCheckedList.at(facePos)) {
            continue;
        }

        IntPos blockPos = facePos;
        int surfaceW = 1;
        int surfaceH = 1;

        faceCheckedList.at(facePos) = true;
        IntPos checkingPos = blockPos + IntPos(1, 0, 0);
        while (faceCheckedList.find(checkingPos) != faceCheckedList.end()
                && !faceCheckedList.at(checkingPos)) {
            surfaceW++;
            faceCheckedList.at(checkingPos) = true;
            checkingPos = checkingPos + IntPos(1, 0, 0);
        }

        IntPos checkingPos_z = blockPos + IntPos(0, 0, 1);
        while (true) {
            IntPos checkingPos = checkingPos_z;
            for (int i = 0; i < surfaceW; i++) {
                if (faceCheckedList.find(checkingPos) == faceCheckedList.end()
                    || faceCheckedList.at(checkingPos)) {
                    while (checkingPos != checkingPos_z) {
                        checkingPos = checkingPos + IntPos(-1, 0, 0);
                        faceCheckedList.at(checkingPos) = false;
                    }
                    goto stopYCheck;
                }
                faceCheckedList.at(checkingPos) = true;
                checkingPos = checkingPos + IntPos(1, 0, 0);
            }

            surfaceH++;
            checkingPos_z = checkingPos_z + IntPos(0, 0, 1);
        }
        stopYCheck:

        Surface surface;
        surface.blockPos = blockPos;
        surface.w = surfaceW;
        surface.h = surfaceH;
        surfaceList.push_back(surface);
    }
}

void GameSelection::createVerticies(std::vector<float> &verticies, std::vector<Surface> &surfaceList) {
    for (Surface &surface: surfaceList) {
        std::vector<float> surfaceVerticies;

        Vec3 pos(surface.blockPos);
        float w = surface.w;
        float h = surface.h;

        surfaceVerticies = {
//          Pos                         Normal
            pos.x  , pos.y+1, pos.z  ,  0,  1,  0,  // A TOP
            pos.x+w, pos.y+1, pos.z+h,  0,  1,  0,  // C
            pos.x  , pos.y+1, pos.z+h,  0,  1,  0,  // D

            pos.x  , pos.y+1, pos.z  ,  0,  1,  0,  // A
            pos.x+w, pos.y+1, pos.z  ,  0,  1,  0,  // B
            pos.x+w, pos.y+1, pos.z+h,  0,  1,  0,  // C
        };

        verticies.insert(verticies.end(), surfaceVerticies.begin(), surfaceVerticies.end());
    }
}
