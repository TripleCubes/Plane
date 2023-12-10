#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include <vector>
#include <memory>
class Entity;

#include <Codes/Types/vec3.h> // TEST

class EntityList {
public:
    static void init();
    static void update();
    static const std::vector<std::shared_ptr<Entity>> &getList(); 

    static void moveEntity0(Vec3 moveVec); // TEST
    static void jumpEntity0(); // TEST

private:
    static std::vector<std::shared_ptr<Entity>> list;
};

#endif
