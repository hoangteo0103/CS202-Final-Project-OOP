#include "GameState.h"

void GameState::Reset(int level)
{
    if (level >= 6)
        return;

    this->charging.play();
    this->theme.play();
    
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
    this->clock.Reset();
    this->previous_time = 0;
   
    
    
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

void GameState::initSounds()
{
    if (!this->theme.openFromFile("sound/game_state/summer.ogg")) cout << "COULD NOT LOAD THEME MUSIC" << endl;
    this->theme.setLoop(true);
    this->theme.play();
    this->theme.setVolume(50);
    this->win.init("sound/game_state/win.wav");
    this->lose.init("sound/game_state/lose.wav");
    this->levelup.init("sound/game_state/complete_level.wav");
    this->charging.init("sound/game_state/player_reset.wav");
    this->win.setVolume(25);
    this->lose.setVolume(25);
    this->charging.setVolume(25);
    this->levelup.setVolume(25);
}
GameState::GameState(RenderWindow* app, stack<State*>* states, int mode, bool saved) : State(app, states)
//, PauseState(app, states)
{
    // Init
    this->initSounds();
    // this->mode = mode; // @tcm: tui load/save thong so nay = loadGame()/saveGame()
    this->restart = false;
    this->ok = false;
    this->clock.Start();
    this->isUpdated = false;
    this->initFonts();

    this->win_line_y = 200;
    // this->current_level = 1; // @tcm: tui load/save thong so nay = loadGame()/saveGame()
    this->distance_between_lane = 100;
    map.init("grasses.png");



    if (!saved)
    {
        
        view = new CView;
        view->init((*app), map.getSize());

        lane_management = new LanePack(this->distance_between_lane);

        lane_management->init(speed[mode], this->current_level, map.getSize(), this->win_line_y);

        
        starting_position.x = map.getSize().x / 2;
        starting_position.y = lane_management->getNumOfLanes() * (this->distance_between_lane + ROADHEIGHT) + this->win_line_y;

        player = new CPEOPLE("skin_1_vertical.png", sf::Vector2u(9, 3), 0.1f, 300.0f, starting_position);

    
        

    }
    else {
        loadGame();
    
    }
    this->buttons.clear();

    this->buttons["PAUSE_STATE_BTN"] = new Button("External/texture", player->getPosition().x + this->app->getSize().x / 2 - 50.0, player->getPosition().y - this->app->getSize().y / 2, 50.0, 50.0, "pause_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["CURRENT_LEVEL_BTN"] = new Button("External/texture", player->getPosition().x - this->app->getSize().x / 2, player->getPosition().y - this->app->getSize().y / 2, 75.0, 50.0, "lv_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    std::map<string, Button*>::iterator it = this->buttons.find("CURRENT_LEVEL_BTN");
    it->second->setTexture("External/texture/lv_button/lv" + to_string(current_level));
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

        {
            this->Reset();
            this->returnMenu();
        }
          
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
        {
            this->endState();
            this->returnMenu();
        }
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

        player->update(delta_time, map.getSize() , lane_management);
        view->update(*app, *player);

        this->updateMovingButton(player->getPosition() - beforePos);

        if (player->isCollision(lane_management)) {
            player->animation.resetFrameDead();
            this->theme.pause();
            this->lose.play();
        }

        if (isPassLevel() && this->current_level < 6) {
            ++this->current_level;
            this->theme.pause();
            this->levelup.play();
            this->Reset(this->current_level);
        }
        if (isPassLevel() && this->current_level == 6)
            this->win.play();
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
        this->theme.pause();
        if (this->pmenu.getResume())
        {
            this->pmenu.Reset();
            this->clock.Start();
            this->paused = false; 
            this->theme.play();
        }

        if (this->pmenu.getRestart())
        {
            this->pmenu.Reset();
            this->Reset();
            this->paused = false;
        }

        if (this->pmenu.getHome())
        {
            this->pmenu.Reset();
            this->saveGame();
            this->endState();
            this->returnMenu();
        }
    }
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
        it->second->move(Vector2f(+50.f, 0));
        it = this->buttons.find("CURRENT_LEVEL_BTN");
        it->second->move(Vector2f(-75.f, 0));
    }
    else
    {
        std::map<string, Button*>::iterator it = this->buttons.find("PAUSE_STATE_BTN");
        it->second->move(Vector2f(-50.f, 0));
        it = this->buttons.find("CURRENT_LEVEL_BTN");
        it->second->move(Vector2f(+75.f, 0));
    }
   
}

void GameState::resetButton()
{
    std::map<string, Button*>::iterator it = this->buttons.find("PAUSE_STATE_BTN");
    it->second->setPosition(Vector2f(player->getPosition().x + this->app->getSize().x / 2 - 50.0, player->getPosition().y - this->app->getSize().y / 2));
    it = this->buttons.find("CURRENT_LEVEL_BTN");
    it->second->setPosition(Vector2f(player->getPosition().x - this->app->getSize().x / 2, player->getPosition().y - this->app->getSize().y / 2));
    it->second->setTexture("External/texture/lv_button/lv" + to_string(current_level));
}

void GameState::returnMenu()
{
    this->states->push(new MainMenuState(this->app, this->states));
    View _view;
    _view.reset(sf::FloatRect(0, 0, this->app->getSize().x, this->app->getSize().y));
    app->setView(_view);
}

const bool& GameState::isPassLevel() const {
    return (player->getPosition().y < win_line_y - player->animation.uv_rect.height / 2);
}

void GameState::playAgain() {
    this->Reset();

}

// Load and save 

void GameState::saveGame()
{
    // Save 4 files txt in the folder External/Data... : view , player , lanepack , game .
    // Save in the order : Game , Player , Lanepack , view 
    ofstream outGame("External/Data/game_data.txt");
    outGame << this->mode << ' ' << this->current_level;

    ofstream outPlayer("External/Data/player_data.txt");
    outPlayer << this->starting_position.x << ' ' << this->starting_position.y << '\n';
    player->saveCPeople(outPlayer);

    ofstream outLanePack("External/Data/lane_pack_data.txt");
    lane_management->saveLanePack(outLanePack);
    ofstream outView("External/Data/view_data.txt");
    view->saveGame(outView);

}

void GameState::loadGame()
{
    // Load game 
    ifstream inGame("External/Data/game_data.txt");
    inGame >> this->mode;
    inGame >> this->current_level;

    // Load lane pack
    ifstream inLanePack("External/Data/lane_pack_data.txt");
    lane_management = new LanePack(this->distance_between_lane);
    lane_management->loadLanePack(inLanePack);


    // Load CVIEW 
    ifstream inView("External/Data/view_data.txt");
    view = new CView;
    view->loadGame(inView, (*app), map.getSize()); 
    cout << "DM"; 
    
    

    

    // Load player , currently testing

    //starting_position.x = map.getSize().x / 2;
    //starting_position.y = lane_management->getNumOfLanes() * (this->distance_between_lane + ROADHEIGHT) + this->win_line_y;
    //player = new CPEOPLE("skin_1_vertical.png", sf::Vector2u(9, 3), 0.1f, 300.0f, starting_position);
    
    // @tcm: Tui sua lai ham load/save nhu sau nhe
    ifstream inPlayer("External/Data/player_data.txt");
    inPlayer >> starting_position.x >> starting_position.y;
    player = new CPEOPLE(inPlayer); // load = constructor
}