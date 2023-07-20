#include <Codes/GraphicTypes/graphicTypesManager.h>

#include <Codes/GraphicTypes/graphicTypeData.h>
#include <algorithm>

#include <Codes/Debug/print.h>

bool GraphicTypesManager::released = false;
std::vector<std::shared_ptr<GraphicTypeData>> GraphicTypesManager::graphicTypeDataList;

void GraphicTypesManager::releaseAll() {
    for (auto &data: graphicTypeDataList) {
        data->release();
    }

    released = true;
}

void GraphicTypesManager::removeGraphicTypeData(const std::shared_ptr<GraphicTypeData> &graphicTypeData) {
    auto it = std::find(graphicTypeDataList.begin(), graphicTypeDataList.end(), graphicTypeData);
    if (it != graphicTypeDataList.end()) {
        graphicTypeDataList.erase(it);
    }
}

void GraphicTypesManager::addGraphicTypeData(const std::shared_ptr<GraphicTypeData> &graphicTypeData) {    
    graphicTypeDataList.push_back(graphicTypeData);
}
