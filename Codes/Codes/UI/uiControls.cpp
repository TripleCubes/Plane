#include <Codes/UI/uiControls.h>

#include <Codes/Settings/settings.h>
#include <Codes/Game/GameSelection/gameSelection.h>

const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 40;
const Color BUTTON_COLOR = Color(1, 0.65, 0.57, 1);
const Color BUTTON_TEXT_COLOR = Color(1, 1, 1, 1);

extern int currentWindowWidth;
extern int currentWindowHeight; 

Button UIControls::modeButton("Chunk", 10, currentWindowHeight - BUTTON_HEIGHT - 10, BUTTON_WIDTH, BUTTON_HEIGHT, 
                                BUTTON_COLOR, BUTTON_TEXT_COLOR);

void UIControls::update() {
    modeButton.update();

    if (modeButton.justPressed()) {
        if (Settings::getMouseMode() == Settings::MouseMode::CHUNK) {
            Settings::mouseMode = Settings::MouseMode::SELECT;
            modeButton.setButtonTitle("Select");
        } else {
            Settings::mouseMode = Settings::MouseMode::CHUNK;
            modeButton.setButtonTitle("Chunk");
            GameSelection::discardSelection();
        }
    }
}

void UIControls::draw() {
    modeButton.draw();
}
