#ifndef PLAYAGAINSTATE_H
#define PLAYAGAINSTATE_H
#include "Button.h"
class PlayAgainState
{
private:
    RectangleShape background;
    RectangleShape container;
    Font font;
    Text menutext;
    Vector2i mousePosWindow;
    Vector2f mousePosView;
    bool Yes, No;
    map<string, Button* > buttons;
    void initFonts();
public:
    PlayAgainState();
    virtual ~PlayAgainState();
    //functions
    void initState(RenderWindow& app);
    void updateButtons();
    const bool& getYes() const;
    const bool& getNo() const;
    void updateMousePositions(Vector2f mousePosView);
    void update();
    void render(RenderTarget& target);
};
#endif // PAUSEMENU_H
