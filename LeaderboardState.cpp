#include "LeaderboardState.h"

//void LeaderboardState::initFonts()
//{
//    if (!this->font.loadFromFile("External/font/Contb.ttf"))
//    {
//    }
//    
//}

void LeaderboardState::initBackground()
{
    texture.loadFromFile("External/images/high_score.png");
    this->background.setTexture(texture);
}

void LeaderboardState::initSounds()
{
    if (!this->theme.openFromFile("sound/main_menu/Movie_theater.ogg"))
        cout << "COULD NOT LOAD THEME MUSIC" << endl;
    this->theme.setLoop(true);
    this->theme.setVolume(40);
    this->theme.play();
}

void LeaderboardState::initBeginner()
{
    ifstream ifs("Leaderboard/leaderboardBeginner.ini");
    vector<int > tmp;
    int  time;
    while (ifs >> time)
    {
        tmp.push_back(time);
    }
    sort(tmp.begin(), tmp.end());
    reverse(tmp.begin(), tmp.end());
    int x = this->app->getSize().x / 2.f - 30 - 215, y = 198;
    for (int i = 0; i < tmp.size(); i++)
    {
        string label = to_string(i) + "a";
        string str_time = to_string(tmp[i]);
        this->buttons[label] = new Button("External/texture", x, y, 60, 40,
            "lv_button", "sound/main_menu/empty.ogg", "sound/main_menu/empty.ogg");
        this->buttons[label]->setTexture("External/texture/lv_button/lv" + to_string(tmp[i]));
        y += 44;
    }
}

void LeaderboardState::initIntermediate()
{
    ifstream ifs("Leaderboard/leaderboardIntermediate.ini");
    vector<int > tmp;
    int  time;
    while (ifs >> time)
    {
        tmp.push_back(time);
    }
    sort(tmp.begin(), tmp.end());
    reverse(tmp.begin(), tmp.end());
    int x = this->app->getSize().x/2.f-30, y = 198;
    for (int i = 0; i < tmp.size(); i++)
    {
        string label = to_string(i) + "b";
        string str_time = to_string(tmp[i]);
        this->buttons[label] = new Button("External/texture", x, y, 60, 40,
            "lv_button", "sound/main_menu/empty.ogg", "sound/main_menu/empty.ogg");
        this->buttons[label]->setTexture("External/texture/lv_button/lv" + to_string(tmp[i]));
        y += 44;
    }
}

void LeaderboardState::initExpert()
{
    ifstream ifs("Leaderboard/leaderboardExpert.ini");
    vector<int > tmp;
    int  time;
    while (ifs >> time)
    {
        tmp.push_back(time);
    }
    sort(tmp.begin(), tmp.end());
    reverse(tmp.begin(), tmp.end());

    int x = this->app->getSize().x / 2.f - 30 + 215, y = 198;
    for (int i = 0; i < tmp.size(); i++)
    {
        string label = to_string(i) + "c";
        string str_time = to_string(tmp[i]);
        this->buttons[label] = new Button("External/texture" , x, y, 60, 40,
            "lv_button", "sound/main_menu/empty.ogg", "sound/main_menu/empty.ogg");
        this->buttons[label]->setTexture("External/texture/lv_button/lv" + to_string(tmp[i]));

        y += 44;
    }
}

LeaderboardState::LeaderboardState(RenderWindow* app, stack<State*>* states)
    :State(app, states)
{
    //this->initFonts();
    this->initBackground();
    this->initSounds();
    this->buttons["BACK_TO_MENU_STATE"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 655, 400, 50, "back_to_menu_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");

    this->initBeginner();
    this->initIntermediate();
    this->initExpert();
}

LeaderboardState ::~LeaderboardState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void LeaderboardState::endState()
{

}

void LeaderboardState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
    if (this->buttons["BACK_TO_MENU_STATE"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new MainMenuState(this->app, this->states));
    }
}

void LeaderboardState::update()
{
    this->updateMousePositions();
    this->updateButtons();
}

void LeaderboardState::renderButtons(RenderTarget* target)
{
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}

void LeaderboardState::render(RenderTarget* target)
{
    if (!target)
        target = this->app;

    target->draw(this->background);
    this->renderButtons(target);
}


