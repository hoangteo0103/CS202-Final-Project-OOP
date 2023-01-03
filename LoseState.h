#ifndef LOSESTATE_H
#define LOSESTATE_H
#include "Button.h"
#include "CPEOPLE.h"
class LoseState
{
private:
    bool ok;

    // Texture
    RectangleShape background;
    RectangleShape container;
    Texture texture;

    // Update
    Vector2i mousePosWindow;
    Vector2f mousePosView;
    map<string, Button* > buttons;

private:
    void initButtons(RenderWindow& app, CPEOPLE* player, CMap* map);

public:
    LoseState();
    virtual ~LoseState();
    //functions

    // Init
    void initState(RenderWindow& app, CPEOPLE* player, CMap* map);

    const bool& getOk() const;

    // Update
    void updateMousePositions(Vector2f mousePosView);
    void updateButtons();
    void update();
    void hide();
    
    // Render
    void renderButtons(RenderTarget* target);
    void render(RenderTarget* target);
};
#endif 