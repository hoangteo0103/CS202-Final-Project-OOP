#ifndef MODSKINSTATE_H
#define MODSKINSTATE_H
#include "Button.h"
#include "CPEOPLE.h"
class ModSkinState
{
private:
    int choice;

    // Texure
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
    ModSkinState();
    virtual ~ModSkinState();
    //functions
    // Init
    void initState(RenderWindow& app, CPEOPLE* player, CMap* map);

    // Update
    const int& getChoice() const;
    void updateMousePositions(Vector2f mousePosView);
    void updateButtons();
    void update();

    // Render
    void renderButtons(RenderTarget* target);
    void render(RenderTarget* target);
};
#endif 