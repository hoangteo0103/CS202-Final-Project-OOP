#ifndef PauseState_H
#define PauseState_H
#include "Button.h"
#include "CPEOPLE.h"
class PauseState
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
    bool resume;
    bool restart;
    bool home;
    void initFonts();
    void initButtons(RenderWindow& app, CPEOPLE* player, CMap* map);
public:
    PauseState();
    virtual ~PauseState();
    //functions
    void initState(RenderWindow& app, CPEOPLE* player, CMap* map);
    void updateButtons();
    const bool& getResume() const;
    const bool& getRestart() const;
    const bool& getHome() const;
    void updateMousePositions(Vector2f mousePosView);
    void update();
    void renderButtons(RenderTarget* target);
    void render(RenderTarget* target);

    void Reset();
};
#endif // PauseState_H