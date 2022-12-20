#include "GameState.h"

void GameState::Reset(int level)
{
    this->ok = false;
    this->isUpdated = false;
    this->paused = false;
    this->restart = false;
    this->current_level = level;
    //this->clock.Reset();
    lane_management->reset(speed[mode], this->current_level, map.getSize(), this->win_line_y);
    starting_position.x = map.getSize().x / 2;
    starting_position.y = lane_management->getNumOfLanes() * (this->distance_between_lane + ROADHEIGHT) + this->win_line_y;
    player->reset(starting_position);
    view->reset(*this->app, *player);
   
    
    
    this->resetButton();
}

void GameState::initFonts()
{
    if (!this->font.loadFromFile("External/font/Contb.ttf"))
    {

    }
    //texture.loadFromFile("images/game1.png");
    this->background.setTexture(texture);
}

GameState::GameState(RenderWindow* app, stack<State*>* states, int mode, bool saved) : State(app, states)
//, PauseState(app, states)
{
    // Init
    if (!saved)
    {

        this->mode = mode; 
        this->restart = false;
        this->ok = false;
        this->clock.Start();
        this->isUpdated = false;
        this->initFonts();

        this->win_line_y = 200;
        this->current_level = 1;
        this->distance_between_lane = 100;

        map.init("grasses.png");
        view = new CView;
        view->init((*app), map.getSize());

        lane_management = new LanePack(this->distance_between_lane);

        lane_management->init(speed[mode], this->current_level, map.getSize(), this->win_line_y);

    
        starting_position.x = map.getSize().x / 2;
        starting_position.y = lane_management->getNumOfLanes() * (this->distance_between_lane + ROADHEIGHT) + this->win_line_y;

        player = new CPEOPLE("skin_1_vertical.png", sf::Vector2u(9, 3), 0.1f, 300.0f, starting_position);

    
        this->buttons.clear();

        this->buttons["PAUSE_STATE_BTN"] = new Button(player->getPosition().x + this->app->getSize().x / 2 - 50.0, player->getPosition().y - this->app->getSize().y / 2, 50.0, 50.0,
            &this->font, "PAUSE", Color(70, 70, 70, 200), Color(100, 100, 100, 255), Color(20, 20, 20, 200));

        this->buttons["CURRENT_LEVEL_BTN"] = new Button(player->getPosition().x - this->app->getSize().x / 2, player->getPosition().y - this->app->getSize().y / 2, 75.0, 50.0,
            &this->font, "LV: " + to_string(current_level), Color::White, Color::White, Color::White);
        std::map<string, Button*>::iterator it = this->buttons.find("CURRENT_LEVEL_BTN");
        it->second->setTextColor(Color::Black);


    }
    else {
        // Phan nay tu canh minh code 
    }
}


GameState ::~GameState()
{
    //delete this->pmenu;
    for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }

    delete view;
    delete player;
    delete lane_management;
}

const bool& GameState::getLose() const
{
    return this->player->isDead();
}

const bool& GameState::getWin() const
{
    if (this->current_level >= 6) {
        this->player->setDead(); 
        return true;
    }
    return false;
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
    if (!this->isUpdated)
    {
        this->hideButton(true);
        this->winState.initState(*app, player, &map);
        this->isUpdated = true;
    }
    if (this->ok)
    {
        this->againState.updateMousePositions(mousePosView);
        this->againState.update();
        if (this->againState.getYes())
        {
            this->Reset();
        }
        if (this->againState.getNo())
            this->endState();
    }
    else
    {
        this->winState.updateMousePositions(mousePosView);
        this->winState.update();

        if (this->winState.getOk())
        {
            this->ok = true;
            this->againState.initState(*app, player, &map);
        }
    }
}   

void GameState::updateLoseState()
{
    if (!this->isUpdated)
    {
        this->hideButton(true);
        this->loseState.initState(*app, player, &map);
        this->isUpdated = true;
    }
    if (this->ok)
    {
        this->againState.updateMousePositions(mousePosView);
        this->againState.update();
        if (this->againState.getYes())
        {
            this->Reset();
        }
        if (this->againState.getNo())
            this->endState();
    }
    else
    {
        this->loseState.updateMousePositions(mousePosView);
        this->loseState.update();

        if (this->loseState.getOk())
        {
            this->ok = true;
            this->againState.initState(*app,player,&map);
        }
    }
}

void GameState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
    if (this->buttons["PAUSE_STATE_BTN"]->isPressed())
        {
            this->clock.Pause();
            this->paused = true;
            this->pmenu.initState(*app, player, &map);
        }
}


void GameState::updateUnpaused()
{
    float now_time = clock.GetElapsedSeconds();
    delta_time = now_time - previous_time;
    previous_time = now_time;
    if (this->getWin()) {
        this->clock.Pause();
        this->updateWinState();
        return;
    }
    if (!this->getLose())
    {
        lane_management->update(delta_time);

        Vector2f beforePos = player->getPosition();

        player->update(delta_time, map.getSize());
        view->update(*app, *player);

        this->updateMovingButton(player->getPosition() - beforePos);

        if (player->isCollision(lane_management)) {
            player->animation.resetFrameDead();
        }

        if (isPassLevel()) {
            ++this->current_level;
            this->Reset(this->current_level);
        }
    }
    else {
        //this->clock.Pause();
        if (this->player->isDeadFrameEnd())
        {
            updateLoseState();
        }
        else {
            player->updateAfterDead(delta_time, map.getSize());
        }

    }
    
    
}
void GameState::updatePaused()
{
    if (this->paused)
    {
        this->pmenu.updateMousePositions(mousePosView);
        this->pmenu.update();

        if (this->pmenu.getResume())
        {
            this->pmenu.Reset();
            this->clock.Start();
            this->paused = false; 
        }
        if (this->pmenu.getExit())
        {
            this->pmenu.Reset();
            this->app->close();
        }
    }
}

void GameState::endGame()
{

}

void GameState::update()
{

    this->updateMousePositions();
    this->updateKeyBinds();
    this->updateButtons();
    
    if (!this->paused)
    {
        updateUnpaused();
    }
    else {
        updatePaused(); 
    }

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

    lane_management->draw(*this->app);
    player->draw(*this->app); 
    this->renderButtons(target);
    if (this->getLose())
    {
        if (!this->ok)
        {
            this->loseState.render(target);
        }
           else
                this->againState.render(target);
    }
    if (this->getWin())
    {
        if (!this->ok)
            this->winState.render(target);
        else
            this->againState.render(target);
    }
    if (this->paused)
    {
        this->pmenu.render(target);
    }
}

void GameState::updateMovingButton(Vector2f& distance)
{
    for (auto it = this->buttons.begin();it!=this->buttons.end();++it)
    {
        if (player->getPosition().x > app->getSize().x / 2 && player->getPosition().x < map.getSize().x - app->getSize().x / 2)
            it->second->move(Vector2f(distance.x, 0));
        if (player->getPosition().y > app->getSize().y / 2 && player->getPosition().y < map.getSize().y - app->getSize().y / 2)
            it->second->move(Vector2f(0, distance.y));
    }
}

void GameState::hideButton(bool hide)
{
    if (hide)
    {
        std::map<string, Button*>::iterator it = this->buttons.find("PAUSE_STATE_BTN");
        it->second->move(Vector2f(+51.f, 0));
        it = this->buttons.find("CURRENT_LEVEL_BTN");
        it->second->move(Vector2f(-76.f, 0));
    }
    else
    {
        std::map<string, Button*>::iterator it = this->buttons.find("PAUSE_STATE_BTN");
        it->second->move(Vector2f(-51.f, 0));
        it = this->buttons.find("CURRENT_LEVEL_BTN");
        it->second->move(Vector2f(+76.f, 0));
    }
   
}

void GameState::resetButton()
{
    std::map<string, Button*>::iterator it = this->buttons.find("PAUSE_STATE_BTN");
    it->second->setPosition(Vector2f(player->getPosition().x + this->app->getSize().x / 2 - 50.0, player->getPosition().y - this->app->getSize().y / 2));
    it = this->buttons.find("CURRENT_LEVEL_BTN");
    it->second->setPosition(Vector2f(player->getPosition().x - this->app->getSize().x / 2, player->getPosition().y - this->app->getSize().y / 2));
    it->second->updateText("LV: " + to_string(current_level));
}


const bool& GameState::isPassLevel() const {
    return (player->getPosition().y < win_line_y - player->animation.uv_rect.height / 2);
}

void GameState::playAgain() {
    this->Reset();

}