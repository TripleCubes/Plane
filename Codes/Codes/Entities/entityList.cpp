#include <Codes/Entities/entityList.h>

#include <Codes/Entities/unit.h>
#include <Codes/Types/vec3.h>

std::vector<std::shared_ptr<Entity>> EntityList::list;

void EntityList::init() {
    
}

void EntityList::update() {
    for (const auto &entity: list) {
        entity->update();
    }
}

void EntityList::add(Vec3 pos) {
    auto unit = std::make_shared<Unit>();
    unit->setPos(pos);
    list.push_back(unit);
}

const std::vector<std::shared_ptr<Entity>> &EntityList::getList() {
    return list;
}
