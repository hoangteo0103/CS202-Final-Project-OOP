#ifndef LOSESTATE_H
#define LOSESTATE_H
#include "Button.h"
class LoseState
{
private:
    RectangleShape background;
    RectangleShape container;
    Texture texture;
    Font font;
    Text menutext;
    Vector2i mousePosWindow;
    Vector2f mousePosView;

    map<string, Button* > buttons;
    bool ok;
    void initFonts();
public:
    LoseState();
    virtual ~LoseState();
    //functions
    void initState(RenderWindow& app);
    void updateButtons();
    const bool& getOk() const;
    void updateMousePositions(Vector2f mousePosView);
    void update();
    void render(RenderTarget& target);
};
#endif // PAUSEMENU_H

