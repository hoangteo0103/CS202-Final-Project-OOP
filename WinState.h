#ifndef WINSTATE_H
#define WINSTATE_H
#include "Button.h"
#include "CPEOPLE.h"
class WinState
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
    WinState();
    virtual ~WinState();
    //functions
    void initButtons(RenderWindow& app, CPEOPLE* player, CMap* map);
    void initState(RenderWindow& app, CPEOPLE* player, CMap* map);
    void updateButtons();
    const bool& getOk() const;
    void updateMousePositions(Vector2f mousePosView);
    void update();
    void renderButtons(RenderTarget* target);
    void render(RenderTarget* target);
};
#endif 