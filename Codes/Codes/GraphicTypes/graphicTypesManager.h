#ifndef GRAPHICTYPESMANAGER_H
#define GRAPHICTYPESMANAGER_H

#include <vector>
#include <memory>

class GraphicTypeData;

class GraphicTypesManager {
public:
    static void releaseAll();
    static void addGraphicTypeData(const std::shared_ptr<GraphicTypeData> &graphicTypeData);
    static void removeGraphicTypeData(const std::shared_ptr<GraphicTypeData> &graphicTypeData);

private:    
    static bool released;
    static std::vector<std::shared_ptr<GraphicTypeData>> graphicTypeDataList;
};

#endif
