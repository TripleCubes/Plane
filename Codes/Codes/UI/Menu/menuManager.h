#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <memory>

class Menu;

class MenuManager {
public:
    static void open(std::shared_ptr<Menu> menu);
    static void closeAllMenus();
    static void goBackOneMenu();
    static void update();
    static void draw();
    static bool isAllMenusClosed();

private:
    static bool allMenusClosed;
    static std::shared_ptr<Menu> currentMenu;
};

#endif
