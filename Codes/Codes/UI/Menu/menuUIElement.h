#ifndef MENUUIELEMENT_H
#define MENUUIELEMENT_H

class MenuUIElement {
public:
    virtual void updateUIElement();
    virtual void drawUIElement() const;
    virtual void setUIElementRelativePos(float x, float y);
    virtual void setScrolledY(float scrolledY);

private:
};

#endif
