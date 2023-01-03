#ifndef PauseState_H
#define PauseState_H
#include "Button.h"
#include "CPEOPLE.h"

class PauseState
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
    bool resume;
    bool save;
    bool restart;
    bool home;

private:
    void initButtons(RenderWindow& app, CPEOPLE* player, CMap* map);

public:
    PauseState();
    virtual ~PauseState();
    //functions

    // Init
    void initState(RenderWindow& app, CPEOPLE* player, CMap* map);

    // Update
    const bool& getResume() const;
    const bool& getSave() const;
    const bool& getRestart() const;
    const bool& getHome() const;
    void Reset();
    void updateMousePositions(Vector2f mousePosView);
    void updateButtons();
    void update();

    // Render
    void renderButtons(RenderTarget* target);
    void render(RenderTarget* target);

};
#endif // PauseState_H