#include <Codes/UI/Menu/menu.h>

#include <Codes/UI/ui.h>
#include <Codes/UI/Menu/menuManager.h>
#include <Codes/Types/color.h>

#include <Codes/Debug/print.h>

extern int currentWindowWidth;
extern int currentWindowHeight;

const float PADDING_LEFT = 50;
const float PADDING_TOP = 50;
const float UIELEMENT_YCURSOR_STEP = 60;

Menu::Menu(const std::string &menuTitle): menuTitle(menuTitle), openMenuButton(menuTitle),
scrollBar(currentWindowWidth - SCROLLBAR_WIDTH, 0, currentWindowHeight, Color(1, 0.65, 0.57, 1)) {
    uiElementYCursor = 100;
}

void Menu::addSelfSharedPtr(std::shared_ptr<Menu> selfSharedPtr) {
    this->selfSharedPtr = selfSharedPtr;
    openMenuButton.addMenuSharedPtr(this->selfSharedPtr);

    selfSharedPtrAdded = true;
}

void Menu::addUpperLevelMenu(std::shared_ptr<Menu> upperLevelMenu) {
    this->upperLevelMenu = upperLevelMenu;
    root = false;
    getFullMenuTitle();
}

void Menu::addUIElement(const MenuUIElement &uiElement) {
    std::shared_ptr<MenuUIElement> uiElementPtr = std::make_shared<MenuUIElement>(uiElement);
    uiElementPtr->setUIElementRelativePos(PADDING_LEFT, uiElementYCursor);

    uiElementList.push_back(uiElementPtr);

    uiElementYCursor += UIELEMENT_YCURSOR_STEP;

    scrollBar.setPageHeight(currentWindowHeight, uiElementYCursor + PADDING_TOP);
}

void Menu::addSubMenu(const std::string &subMenuTitle) {
    if (!selfSharedPtrAdded) {
        LINEINFORMATION();
        PRINTLN("selfSharedPtr not added");
        return;
    }

    std::shared_ptr<Menu> subMenu = std::make_shared<Menu>(subMenuTitle);
    subMenu->addSelfSharedPtr(subMenu);
    subMenu->addUpperLevelMenu(this->selfSharedPtr);
    subMenu->setUIElementRelativePos(PADDING_LEFT, uiElementYCursor);
    subMenu->menuDepth = this->menuDepth + 1;

    subMenuList.push_back(subMenu);
    uiElementList.push_back(subMenu);

    uiElementYCursor += UIELEMENT_YCURSOR_STEP;

    scrollBar.setPageHeight(currentWindowHeight, uiElementYCursor + PADDING_TOP);
}

void Menu::getFullMenuTitle() {
    if (root) {
        LINEINFORMATION();
        PRINTLN("Cant call getFullMenuTitle() on root menu");
        return;
    }

    fullMenuTitle = menuTitle;
    Menu *currentMenu = upperLevelMenu.get();
    while (!currentMenu->root) {
        fullMenuTitle = currentMenu->menuTitle + "  >  " + fullMenuTitle;
        currentMenu = currentMenu->upperLevelMenu.get();
    }
}

Menu *Menu::getSubMenu(const std::string &subMenuTitle) const {
    for (const auto &subMenu: subMenuList) {
        if (subMenu->menuTitle == subMenuTitle) {
            return subMenu.get();
        }
    }

    LINEINFORMATION();
    PRINTLN("Submenu not found");
    return NULL;
}

void Menu::open() const {
    MenuManager::open(selfSharedPtr);
}

void Menu::goBackOneMenu() const {
    if (root || menuDepth == 1) {
        MenuManager::closeAllMenus();
        return;
    }

    upperLevelMenu->open();
}

void Menu::updateMenu() {
    scrollBar.update();

    for (const auto &uiElement: uiElementList) {
        uiElement->updateUIElement();
        uiElement->setScrolledY(scrollBar.getScrollValue());
    }
}

void Menu::drawMenu() const {
    UI::drawRectWH(0, 0, currentWindowWidth, currentWindowHeight, Color(0, 0, 0, 0.3));
    UI::drawTextBox(PADDING_LEFT, PADDING_TOP + scrollBar.getScrollValue(), fullMenuTitle, Color(1, 1, 1, 1));

    scrollBar.draw();

    for (const auto &uiElement: uiElementList) {
        uiElement->drawUIElement();
    }
}

void Menu::updateUIElement() {
    openMenuButton.updateUIElement();
}

void Menu::drawUIElement() const {
    openMenuButton.drawUIElement();
}

void Menu::setUIElementRelativePos(float x, float y) {
    openMenuButton.setUIElementRelativePos(x, y);
}

void Menu::setScrolledY(float scrolledY) {
    openMenuButton.setScrolledY(scrolledY);
}
