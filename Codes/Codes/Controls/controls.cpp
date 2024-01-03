#include <Codes/Controls/controls.h>

#include <Codes/Settings/settings.h>
#include <Codes/View/camera.h>
#include <Codes/Game/GameSelection/gameSelection.h>
#include <Codes/RayCast/blockRayCast.h>
#include <Codes/Chunks/chunkLoader.h>
#include <Codes/Entities/entityList.h>

#include <Codes/Input/input.h>
#include <Codes/Time/time.h>
#include <Codes/Types/vec2.h>

#include <Codes/Debug/print.h>

extern BlockRayCastResult savedBlockRayCastResult;

void lockMouse();
void unlockMouse();

float Controls::cameraRotationX = 0;
float Controls::cameraRotationY = 0;

void Controls::update() {
    updateSettings();

    if (Settings::isFreeCam()) {
        updateCameraDir();
        updateMovements();
    }

    if (Settings::getMouseMode() == Settings::MouseMode::SELECT) {
        updateGameSelection();
    } else if (Settings::getMouseMode() == Settings::MouseMode::CHUNK) {
        updateChunkPlacing();
    }

    // updatePlaceBreak();

    updateDebugLogKeys();
}

void Controls::updateSettings() {
    if (Input::justPressed("M")) {
        Settings::wireframeMode = !Settings::wireframeMode;
    }

    if (Input::justPressed("N")) {
        Settings::perspectiveProjection = !Settings::perspectiveProjection;
    }

    if (Input::justPressed("B")) {
        Settings::freeCam = !Settings::freeCam;
        if (Settings::isFreeCam()) {
            lockMouse();
        } else {
            unlockMouse();
        }
    }
}

void Controls::updateCameraDir() {
    Vec2 mouseMoveOffset = Input::getMouseMoveOffset();

    cameraRotationX -= mouseMoveOffset.y * 0.17;
    if (cameraRotationX > 89.99)
    {
        cameraRotationX = 89.99;
    }
    else if (cameraRotationX < -89.99)
    {
        cameraRotationX = -89.99;
    }
    cameraRotationY -= mouseMoveOffset.x * 0.17;

    Camera::dir = Vec3(0, 0, -1).rotateXYDeg(cameraRotationX, cameraRotationY);
}

void Controls::updateMovements() {
    Vec3 moveDir;
    Vec3 cameraDir = Camera::getDir();
    cameraDir.y = 0;
    cameraDir = cameraDir.normalize();
    Vec3 cameraDirRotated90 = cameraDir.rotateYDeg(90);
    if (Input::pressed("W")) {
        moveDir += cameraDir;
    }
    if (Input::pressed("A")) {
        moveDir += cameraDirRotated90;
    }
    if (Input::pressed("S")) {
        moveDir -= cameraDir;
    }
    if (Input::pressed("D")) {
        moveDir -= cameraDirRotated90;
    }
    if (Input::pressed("SPACE")) {
        moveDir.y += 1;
    }
    if (Input::pressed("LEFT_SHIFT")) {
        moveDir.y -= 1;
    }
    
    if (moveDir != Vec3(0, 0, 0)) {
        Camera::pos += moveDir * 15 * Time::getDeltaTime();
    }
}

void Controls::updatePlaceBreak() {
    if (Input::justPressed(MouseButton::RIGHT)) {
        if (!savedBlockRayCastResult.hasPlacingPos) {
            return;
        }

        ChunkLoader::chunkLoadCheck_setBlockAndUpdate(savedBlockRayCastResult.placingPos, BlockType::GREEN);        

        return;
    }

    if (Input::justPressed(MouseButton::LEFT)) {
        if (!savedBlockRayCastResult.found) {
            return;
        }

        ChunkLoader::chunkLoadCheck_setBlockAndUpdate(savedBlockRayCastResult.selectedPos, BlockType::EMPTY);        

        return;
    }
}

void Controls::updateChunkPlacing() {
    if (!savedBlockRayCastResult.found) {
        return;
    }

    if (Input::justPressed(MouseButton::LEFT)) {
        IntPos chunkPos = savedBlockRayCastResult.selectedPos.getChunkPos();
        ChunkLoader::loadChunkTerrainAndMesh(chunkPos.x, chunkPos.z);
    }
}

void Controls::updateGameSelection() {
    if (!savedBlockRayCastResult.found) {
        return;
    }

    if (Input::justPressed(MouseButton::LEFT)) {
        IntPos startPos = savedBlockRayCastResult.selectedPos;
        startPos.y = -100;
        GameSelection::startSelection(startPos);
    }

    if (Input::pressed(MouseButton::LEFT)) {
        IntPos endPos = savedBlockRayCastResult.selectedPos;
        endPos.y = 100;
        GameSelection::setSelectionEndPos(endPos);
    }

    if (Input::justReleased(MouseButton::LEFT)) {
        IntPos endPos = savedBlockRayCastResult.selectedPos;
        endPos.y = 100;
        GameSelection::endSelection(endPos);
    }
}

void Controls::updateDebugLogKeys() {
    if (Input::justPressed("1")) {
        if (savedBlockRayCastResult.found) {
            PRINTLN(savedBlockRayCastResult.selectedPos);
        }
    }

    if (Input::justPressed("2")) {
        if (savedBlockRayCastResult.found) {
            Vec3 pos = Vec3(savedBlockRayCastResult.selectedPos.x, 20, savedBlockRayCastResult.selectedPos.z);
            EntityList::add(pos);
        }
    }
}
