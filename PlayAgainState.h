#ifndef PLAYAGAINSTATE_H
#define PLAYAGAINSTATE_H
#include "Button.h"
#include "CPEOPLE.h"
class PlayAgainState
{
private:
    RectangleShape background;
    RectangleShape container;
    Texture texture;
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
    void initButtons(RenderWindow& app, CPEOPLE* player, CMap* map);
    void initState(RenderWindow& app, CPEOPLE* player, CMap* map);
    void updateButtons();
    const bool& getYes() const;
    const bool& getNo() const;
    void updateMousePositions(Vector2f mousePosView);
    void update();
    void renderButtons(RenderTarget* target);
    void render(RenderTarget* target);
};
#endif // PAUSEMENU_H
