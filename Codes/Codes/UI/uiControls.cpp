#include <Codes/UI/uiControls.h>

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
        if (modeButton.getButtonTitle() == "Chunk") {
            modeButton.setButtonTitle("Select");
        } else {
            modeButton.setButtonTitle("Chunk");
        }
    }
}

void UIControls::draw() {
    modeButton.draw();
}
