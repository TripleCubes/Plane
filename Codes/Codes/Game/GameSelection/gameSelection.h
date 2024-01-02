#ifndef SELECTION_H
#define SELECTION_H

#include <Codes/Types/intpos.h>

#include <Codes/GraphicTypes/mesh.h>
#include <unordered_map>
#include <vector>

class GameSelection {
public:
    static void init();

    static void startSelection(IntPos pos);
    static void setSelectionEndPos(IntPos pos);
    static void endSelection(IntPos pos);
    static void discardSelection();

    static void draw();

private:
    static bool selecting;
    static IntPos selectionStart;
    static IntPos selectionEnd;

    static Mesh mesh;
    static bool meshSetted;

    static void updateMesh();

    struct Surface {
        int w = 0;
        int h = 0;
        IntPos blockPos;
    };

    static void createFaceCheckedList(std::unordered_map<IntPos, bool, IntPosHash> &faceCheckedList,
                                        std::vector<IntPos> &faceCheckedListOrder);
    static void createSurfaceList(std::vector<Surface> &surfaceList, 
                                    std::unordered_map<IntPos, bool, IntPosHash> &faceCheckedList,
                                    std::vector<IntPos> &faceCheckedListOrder);
    static void createVerticies(std::vector<float> &verticies, std::vector<Surface> &surfaceList);
};

#endif
