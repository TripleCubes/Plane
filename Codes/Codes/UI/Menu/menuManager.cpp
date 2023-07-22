#include <Codes/UI/Menu/menuManager.h>

#include <Codes/UI/Menu/menu.h>

void lockMouse();
void unlockMouse();

bool MenuManager::allMenusClosed = true;
std::shared_ptr<Menu> MenuManager::currentMenu;

void MenuManager::open(std::shared_ptr<Menu> menu) {
    currentMenu = menu;
    allMenusClosed = false;
    
    unlockMouse();
}

void MenuManager::closeAllMenus() {
    allMenusClosed = true;

    lockMouse();
}

void MenuManager::goBackOneMenu() {
    if (!allMenusClosed) {
        currentMenu->goBackOneMenu();
    }
}

void MenuManager::update() {
    if (!allMenusClosed) {
        currentMenu->updateMenu();
    }
}

void MenuManager::draw() {
    if (!allMenusClosed) {
        currentMenu->drawMenu();
    }
}

bool MenuManager::isAllMenusClosed() {
    return allMenusClosed;
}
