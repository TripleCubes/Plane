#ifndef UICONTROLS_H
#define UICONTROLS_H

#include <Codes/UI/button.h>

class UIControls {
public:
    static void update();
    static void draw();

private:
    static Button modeButton;
};

#endif
