#include <Codes/Entities/unit.h>

Unit::Unit() {
    for (int i = 0; i < 6; i++) {
        createPhysicPoints(i);
    }
}
