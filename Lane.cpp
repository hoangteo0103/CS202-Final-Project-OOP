#include "Lane.h"
vector<Vector2u> imageContainVc = { Vector2u(14,1) };
vector<string> pathTexture = { "Skin1.png" };
vector<int> sizeTexture = { 120};


Lane::Lane(int typeObstacle, int dir, int num, float speed, int type, Vector2f pos)
{
	this->num = num;
	int disBetweenObstacle = 250;
	Vector2f nowPos = { pos.x - (num - 1) * ( sizeTexture[typeObstacle]  + disBetweenObstacle)  , pos.y};
	for (int i = 1; i <= num; i++)
	{
		COBSTACLE* now = new COBSTACLE(pathTexture[typeObstacle], imageContainVc[typeObstacle], 0.1f, speed, nowPos, dir);
		nowPos.x += sizeTexture[typeObstacle] + disBetweenObstacle;
		obstacle.push_back(now);
	}

	string texture_dir;

	random_device rd;
	mt19937 rng(rd());
	
	if (type == 0) {
		uniform_int_distribution<int> range(0, 1);
		int random_index = range(rng);
		texture_dir = ROADTEXTUREPATH[random_index];
	}
	else if (type == 1) {
		uniform_int_distribution<int> range(2, 3);
		int random_index = range(rng);
		texture_dir = ROADTEXTUREPATH[random_index];

		numTrafficLight = 1;

		float start = 400.f;
		for (int i = 0; i < numTrafficLight; i++)
		{
			CTRAFFICLIGHT* tmp = new CTRAFFICLIGHT(Vector2f(start, pos.y), 2.0f, 2.0f, 2.0f);
			start += 500.f;
			lights.push_back(tmp);
		}
	}
	

	if (!(texture.loadFromFile(texture_dir)))
	{
		cout << "Could Not Load Lane File.." << endl;
	}
	position = pos;
	sprite.setTexture(texture);
	this->sprite.setPosition(position);
}


Lane::~Lane() {
	for (auto obj : obstacle)
		delete obj;

	for (auto light : lights)
		delete light;
}


void Lane::updateSpeed()
{	

	for (int i = 0; i < num; i++)
	{

		obstacle[i]->setSpeed(obstacle[i]->origin_speed);
		for (int j = 0; j < numTrafficLight; j++)
		{
			//cout << obstacle[i]->sprite.getPosition().x << ' ' << lights[i]->isVehiclePass() << ' ' << lights[i]->getPos() << endl;
			if ( (obstacle[i]->sprite.getPosition().x  > lights[j]->getPos() + 48.f )  || lights[j]->isVehiclePass()) continue;
			int dis = lights[j]->getPos() + 48.f -  (obstacle[i]->sprite.getPosition().x + obstacle[i]->animation.uv_rect.width);
			obstacle[i]->setSpeed(dis);
		}
	}

}

void Lane::draw(sf::RenderWindow& window)
{

	window.draw(this->sprite);
	for (int i = 0; i < num; i++)
	{
		//cout << obstacle[i]->sprite.getPosition().x << ' ' << obstacle[i]->sprite.getPosition().y << endl;
		obstacle[i]->draw(window);
	}

}
void Lane::checkEnd()
{
	int typeObstacle = 0;
	if (obstacle[0]->getPosition().x < 2880.f) return;
	int disBetweenObstacle = 200; 
	Vector2f nowPos = { position.x - (num - 1) * (sizeTexture[typeObstacle] +disBetweenObstacle) , position.y };
	for (int i = 0; i < num; i++)
	{
		obstacle[i]->sprite.setPosition(nowPos);
		nowPos.x+= sizeTexture[typeObstacle] + disBetweenObstacle;
	}

}


void Lane::update(float delta_time)
{
	for (int i = 0; i < numTrafficLight; i++)
	{
		lights[i]->transition(delta_time);
	}
	for (int i = 0; i < num; i++)
	{
		obstacle[i]->move(delta_time);
	}
	checkEnd();
}
//void render(RenderTarget* target)
//{
//
//}

