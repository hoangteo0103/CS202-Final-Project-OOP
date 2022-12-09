#ifndef PauseState_H
#define PauseState_H
#include "GameState.h"

class PauseState : public State
{
private:
	Texture t;
	Sprite background;
	Font font;
	map<string, Button*> buttons;

private:
	void initFonts();
	void initButtons();

public:
	PauseState(RenderWindow* app, stack<State*>* states);
	virtual ~PauseState();

public:
	void updateKeyBinds();
	void updateButtons();
	void endState();
	void update();
	void render(RenderTarget* target = NULL);
	void renderButtons(RenderTarget* target = NULL);
};

#endif // PauseState_H