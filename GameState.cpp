#include "GameState.h"

void GameState::Reset()
{
    this->ok = false;
    this->isUpdated = false;
    this->clock.Reset();
    this->paused = false;
    this->previousTime = 0;
}

void GameState::initFonts()
{
    if (!this->font.loadFromFile("External/font/Contb.ttf"))
    {

    }
    //texture.loadFromFile("images/game1.png");
    this->background.setTexture(texture);
}

GameState::GameState(RenderWindow* app, stack<State*>* states,bool saved) : State(app, states)
//, pausemenu(app, states)
{
    // Init
    this->ok = false;
    this->isUpdated = false;
    this->clock.Start();
    this->initFonts();
    this->buttons["PAUSE_STATE_BTN"] = new Button(this->app->getSize().x - 500.0, this->app->getSize().y - 500.0, 500.0, 500.0,
        &this->font, "PAUSE", Color(70, 70, 70, 200), Color(100, 100, 100, 255), Color(20, 20, 20, 200));
    
    map.init("dup_map.png"); 
    _view.init((*app), map.getSize());
    
    test = new CTRAFFICLIGHT(Vector2f(map.getSize().x / 2, map.getSize().y - 500),  2.0f, 2.0f,  2.0f);
    player = new CPEOPLE("girl.png", sf::Vector2u(6, 9), 0.1f, 300.0f, Vector2f(map.getSize().x / 2, map.getSize().y - 500));
}


GameState ::~GameState()
{
    //delete this->pmenu;
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}



void GameState::updateKeyBinds()
{
    this->checkForQuit();
}

void GameState::endState()
{
    this->quit = true;
    cout << "End MainMenu" << endl;
}

void GameState::updatePaused()
{
    //this->pausemenu.updateMousePositions();
}

void GameState::updateBeginner(int time_now)
{
    ifstream ifs("Leaderboard/leaderboardBeginner.ini");
    vector< int > tmp;
    tmp.push_back(time_now);
    int time;
    while (ifs >> time)
    {
        tmp.push_back(time);
    }
    sort(tmp.begin(), tmp.end());
    ofstream ofs("Leaderboard/leaderboardBeginner.ini");
    for (int i = 0; i < min(10, (int)tmp.size()); i++)
    {
        ofs << tmp[i] << endl;
    }
}
void GameState::updateIntermediate(int time_now)
{
    ifstream ifs("Leaderboard/leaderboardIntermediate.ini");
    vector< int > tmp;
    tmp.push_back(time_now);
    int time;
    while (ifs >> time)
    {
        tmp.push_back(time);
    }
    sort(tmp.begin(), tmp.end());
    ofstream ofs("Leaderboard/leaderboardIntermediate.ini");
    for (int i = 0; i < min(10, (int)tmp.size()); i++)
    {
        ofs << tmp[i] << endl;
    }
}

void GameState::updateExpert(int time_now)
{
    ifstream ifs("Leaderboard/leaderboardExpert.ini");
    vector< int > tmp;
    tmp.push_back(time_now);
    int time;
    while (ifs >> time)
    {
        tmp.push_back(time);
    }
    sort(tmp.begin(), tmp.end());
    ofstream ofs("Leaderboard/leaderboardExpert.ini");
    for (int i = 0; i < min(10, (int)tmp.size()); i++)
    {
        ofs << tmp[i] << endl;
    }
}

void GameState::updateLeaderBoard()
{
   
}


void GameState::updateWinState()
{
    
}

void GameState::updateLoseState()
{
   
}

void GameState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
    if (this->buttons["PAUSE_STATE_BTN"]->isPressed())
    {
        this->states->push(new PauseState(this->app, this->states));
        this->quit = true;
    }
}

void GameState::update()
{

    this->updateMousePositions();
    this->updateKeyBinds();
    this->updateButtons();
    delta_time = delta_clock.restart().asSeconds();

    player->update(delta_time, map.getSize());
    Vector2f beforeView = _view.getCenter();
    _view.update(*app, *player);
    Vector2f afterView = _view.getCenter();
    Vector2f dis = beforeView - afterView;
    for (auto& it : this->buttons)
    {
        it.second->move(dis);
    }
    test->transition(delta_time);
}

void GameState::renderButtons(RenderTarget* target)
{
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}

void GameState::render(RenderTarget* target)
{
    if (!target)
		target = this->app;
    
	target->draw(this->background);
    map.draw(*this->app);
    player->draw(*this->app); 
    test->draw(*this->app);
    this->renderButtons(target);
}

