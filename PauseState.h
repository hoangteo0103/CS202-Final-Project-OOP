#ifndef PauseState_H
#define PauseState_H
#include "Button.h"
#include "CPEOPLE.h"
class PauseState
{
private:
    RectangleShape background;
    RectangleShape container;
    Font font;
    Text menutext;
    Vector2i mousePosWindow;
    Vector2f mousePosView;

    map<string, Button* > buttons;
    bool resume;
    void initFonts();
public:
    PauseState();
    virtual ~PauseState();
    //functions
    void initState(RenderWindow& app, CPEOPLE* player);
    void updateButtons();
    const bool& getResume() const;
    void updateMousePositions(Vector2f mousePosView);
    void update();
    void render(RenderTarget& target);
};
#endif // PauseState_H