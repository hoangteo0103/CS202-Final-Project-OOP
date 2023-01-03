#ifndef PLAYAGAINSTATE_H
#define PLAYAGAINSTATE_H
#include "Button.h"
#include "CPEOPLE.h"
class PlayAgainState
{
private:
    // Texture
    RectangleShape background;
    RectangleShape container;
    Texture texture;

    // Update
    Vector2i mousePosWindow;
    Vector2f mousePosView;
    map<string, Button* > buttons;
    bool Yes;
    bool No;

private:
    void initButtons(RenderWindow& app, CPEOPLE* player, CMap* map);

public:
    PlayAgainState();
    virtual ~PlayAgainState();
    //functions

    // Init
    void initState(RenderWindow& app, CPEOPLE* player, CMap* map);

    // Update
    const bool& getYes() const;
    const bool& getNo() const;
    void updateMousePositions(Vector2f mousePosView);
    void updateButtons();
    void update();

    // Render
    void renderButtons(RenderTarget* target);
    void render(RenderTarget* target);
};
#endif // PAUSEMENU_H