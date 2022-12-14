#include "GameState.h"

void GameState::Reset(int level)
{
    this->ok = false;
    this->isUpdated = false;
    this->paused = false;

    this->current_level = level;

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
//, PauseState(app, states)
{
    // Init
    this->ok = false;
    this->isUpdated = false;
    this->initFonts();
    
    this->win_line_y = 200;
    this->current_level = 1;


    map.init("grasses.png"); 
    view = new CView;
    view->init((*app), map.getSize());

    starting_position = sf::Vector2f(map.getSize().x / 2, map.getSize().y - this->app->getSize().y);


    player = new CPEOPLE("skin_1_vertical.png", sf::Vector2u(9, 3), 0.1f, 300.0f, starting_position);

    this->buttons["PAUSE_STATE_BTN"] = new Button(player->getPosition().x + this->app->getSize().x / 2 - 50.0, player->getPosition().y - this->app->getSize().y/2, 50.0, 50.0,
        &this->font, "PAUSE", Color(70, 70, 70, 200), Color(100, 100, 100, 255), Color(20, 20, 20, 200));
    
    lane_management = new LanePack;

    lane_management->init(this->current_level, map.getSize(), this->win_line_y);
}


GameState ::~GameState()
{
    //delete this->pmenu;
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }

    delete view;
    delete player;
    delete lane_management;
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
    //this->PauseState.updateMousePositions();
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
        this->paused = true;
        this->pmenu.initState(*app);
    }
}

void GameState::update()
{

    this->updateMousePositions();
    this->updateKeyBinds();
    this->updateButtons();
    delta_time = delta_clock.restart().asSeconds();


    //road->update(delta_time);
    lane_management->update(delta_time);

    Vector2f beforePos = player->getPosition();

    player->update(delta_time, map.getSize());
    view->update(*app, *player);
    
    this->updateMovingButton(player->getPosition() - beforePos);

    if (player->isCollision(lane_management)) {
        cout << "game_over" << endl;
    }

    if (player->getPosition().y < win_line_y - player->animation.uv_rect.height / 2) {
        player->reset(starting_position);
        view->reset(*this->app, *player);
    }
}

void GameState::endGame()
{

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
    //road->draw(*this->app);
    lane_management->draw(*this->app);
    player->draw(*this->app); 
    this->renderButtons(target);
    if (this->paused)
    {
        cout << 1; 
        this->pmenu.render(*target);
    }
}

void GameState::updateMovingButton(Vector2f& distance)
{
    for (auto& it : this->buttons)
    {
        if (player->getPosition().x > app->getSize().x / 2 && player->getPosition().x < map.getSize().x - app->getSize().x / 2)
            it.second->move(Vector2f(distance.x, 0));
        if (player->getPosition().y > app->getSize().y / 2 && player->getPosition().y < map.getSize().y - app->getSize().y / 2)
            it.second->move(Vector2f(0, distance.y));
    }
}