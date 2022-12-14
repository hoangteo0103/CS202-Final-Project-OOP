#include "PauseState.h"
#include "MainMenuState.h"

void PauseState::initFonts()
{
	if (!this->font.loadFromFile("External/font/Contb.ttf"))
	{

	}

	t.loadFromFile("External/images/pause_menu.jpg");
	this->background.setTexture(t);
}

void PauseState::initButtons()
{

}

PauseState::PauseState(RenderWindow* app, stack<State*>* states)
:State(app, states)
{
	this->initFonts();
	this->buttons["CONTINUE_STATE_BTN"] = new Button(680, 200, 400, 50,
		&this->font, "RESUME", Color(70, 70, 70, 200)
		, Color(100, 100, 100, 255), Color(20, 20, 20, 200));
	this->buttons["GAME_STATE_BTN"] = new Button(680, 260, 400, 50,
		&this->font, "RESTART", Color(70, 70, 70, 200)
		, Color(100, 100, 100, 255), Color(20, 20, 20, 200));
	/*this->buttons["SOUND_STATE_BTN"] = new Button(680, 320, 400, 50,
		&this->font, "SOUND", Color(70, 70, 70, 200)
		, Color(100, 100, 100, 255), Color(20, 20, 20, 200));*/
	this->buttons["MAIN_MENU_STATE_BTN"] = new Button(680, 320, 400, 50,
		&this->font, "EXIT", Color(70, 70, 70, 200)
		, Color(100, 100, 100, 255), Color(20, 20, 20, 200));
}

PauseState::~PauseState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void PauseState::updateKeyBinds()
{
	this->checkForQuit();
}

void PauseState::endState()
{
	this->quit = true;

}

void PauseState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
	if (this->buttons["CONTINUE_STATE_BTN"]->isPressed())
	{
		this->quit = true;
	}

	if (this->buttons["GAME_STATE_BTN"]->isPressed())
	{
		// this->states->push (new GameState(this->app, this->states, ?, ?, ?)
		this->quit = true;
	}
	if (this->buttons["MAIN_MENU_STATE_BTN"]->isPressed())
	{
		this->states->push(new MainMenuState(this->app, this->states));
		this->quit = true;
	}
}


void PauseState::update()
{
	this->updateMousePositions();
	this->updateKeyBinds();
	this->updateButtons();
}

void PauseState::renderButtons(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void PauseState::render(RenderTarget* target)
{
	if (!target)
		target = this->app;

	target->draw(this->background);
	this->renderButtons(target);
}