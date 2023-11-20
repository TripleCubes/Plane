#include <Codes/Entities/entityList.h>

#include <Codes/Entities/entity.h>

std::vector<Entity> EntityList::list;

void EntityList::init() {
    list.push_back(Entity());
}

const std::vector<Entity> &EntityList::getList() {
    return list;
}
