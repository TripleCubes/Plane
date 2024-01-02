#include <Codes/Entities/entityList.h>

#include <Codes/Entities/unit.h>

std::vector<std::shared_ptr<Entity>> EntityList::list;

void EntityList::init() {
    // list.push_back(std::make_shared<Unit>());
}

void EntityList::update() {
    for (const auto &entity: list) {
        entity->update();
    }
}

const std::vector<std::shared_ptr<Entity>> &EntityList::getList() {
    return list;
}
