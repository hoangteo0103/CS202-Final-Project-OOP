#include "Lane.h"
vector<Vector2u> imageContainVc = { Vector2u(14,1) };
vector<string> pathTexture = { "Skin1.png" };
vector<int> sizeTexture = { 120};


Lane::Lane(int typeObstacle, int dir, int num, float speed, int type, Vector2f pos)
{
	this->numTrafficLight = 0;

	sf::Vector2u imageContainer;

	random_device rd;
	mt19937 rng(rd());

	if (type == 0) {
		// random road texture
		uniform_int_distribution<int> road_pool(0, ROAD_ANIMAL_TEXTURE_PATH.size()-1);
		int random_road = road_pool(rng);
		this->road_path = ROAD_ANIMAL_TEXTURE_PATH[random_road];

		//random obstacle texture
		uniform_int_distribution<int> obs_pool(0, ANIMAL_TEXTURE_PATH.size() - 1);
		int random_obs = obs_pool(rng);
		this->obstacle_path = ANIMAL_TEXTURE_PATH[random_obs].first;
		imageContainer = ANIMAL_TEXTURE_PATH[random_obs].second;
	}
	else if (type == 1) {
		// random road texture
		uniform_int_distribution<int> road_pool(0, ROAD_VEHICLE_TEXTURE_PATH.size()-1);
		int random_road = road_pool(rng);
		this->road_path = ROAD_VEHICLE_TEXTURE_PATH[random_road];

		numTrafficLight = 1;
		float start = 1500.f;
		for (int i = 0; i < numTrafficLight; i++)
		{
			CTRAFFICLIGHT* tmp = new CTRAFFICLIGHT(Vector2f(start, pos.y - 60.f), 20.0f, 20.0f, 20.0f);
			start += 500.f;
			lights.push_back(tmp);
		}

		//random obstacle texture
		uniform_int_distribution<int> obs_pool(0, VEHICLE_TEXTURE_PATH.size()-1);
		int random_obs = obs_pool(rng);
		this->obstacle_path = VEHICLE_TEXTURE_PATH[random_obs].first;
		imageContainer = VEHICLE_TEXTURE_PATH[random_obs].second;
	}
	if (!(texture.loadFromFile(this->road_path)))
	{
		cout << "Could Not Load Lane File.." << endl;
	}
	position = pos;
	sprite.setTexture(texture);
	this->sprite.setPosition(position);


	// random for obstacle of specified road

	cout << "road_path: " << this->road_path << endl;
	cout << "obstacle_path: " << this->obstacle_path << endl;
	cout << "Image container: " << imageContainer.x << "-" << imageContainer.y << endl;

	this->num = num;
	int disBetweenObstacle = 200;
	cout << "DIR :" << dir << endl;

	if (dir!=1)
	{
		Vector2f nowPos = { pos.x - (num - 1) * (sizeTexture[typeObstacle] + disBetweenObstacle)  , pos.y };
		for (int i = 1; i <= num; i++)
		{
			COBSTACLE* now = new COBSTACLE(this->obstacle_path, imageContainer, 0.1f, speed, nowPos, dir);
			nowPos.x += (sizeTexture[typeObstacle] + disBetweenObstacle);
			obstacle.push_back(now);
		}
	}
	else {
		Vector2f nowPos = { 2880.f +  (num - 1) * (sizeTexture[typeObstacle] + disBetweenObstacle)  , pos.y };
		for (int i = 1; i <= num; i++)
		{
			COBSTACLE* now = new COBSTACLE(this->obstacle_path, imageContainer, 0.1f, speed, nowPos, dir);
			nowPos.x -= (sizeTexture[typeObstacle] + disBetweenObstacle);
			obstacle.push_back(now);
		}
	}


}


Lane::~Lane() {
	for (auto obj : obstacle)
		delete obj;

	for (auto light : lights)
		delete light;
}


void Lane::updateSpeed()
{	
	if (type == 0) return; 
	if (this->dir == 2)
	{
		for (int i = 0; i < num; i++)
		{

			obstacle[i]->setSpeed(obstacle[i]->origin_speed);
			for (int j = 0; j < numTrafficLight; j++)
			{
				if ((obstacle[i]->sprite.getPosition().x > lights[j]->getPos() + 48.f) || lights[j]->isVehiclePass()) continue;
				int dis = lights[j]->getPos() - (obstacle[i]->sprite.getPosition().x + obstacle[i]->animation.uv_rect.width);
				if(dis < obstacle[i]->speed) 
					obstacle[i]->setSpeed(dis);
			}
		}
	}
	else {
		for (int i = 0; i < num; i++)
		{
			obstacle[i]->setSpeed(obstacle[i]->origin_speed);
			for (int j = 0; j < numTrafficLight; j++)
			{
				cout << "GG" << obstacle[i]->sprite.getPosition().x << ' ' << obstacle[i]->animation.uv_rect.width << ' ' << lights[j]->getPos() << endl;
				if ((obstacle[i]->sprite.getPosition().x  <= lights[j]->getPos()) || lights[j]->isVehiclePass()) continue;
				int dis = obstacle[i]->sprite.getPosition().x - lights[j]->getPos()  - obstacle[i]->animation.uv_rect.width - 96.f;
				if (dis < obstacle[i]->speed)
					obstacle[i]->setSpeed(dis);
			}
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
	for (int i = 0; i < numTrafficLight; i++)
	{
		lights[i]->draw(window);
	}

}
void Lane::checkEnd()
{
	if (dir == 2)
	{
		int typeObstacle = 0;
		if (obstacle[0]->getPosition().x < 2880.f) return;
		int disBetweenObstacle = 600;
		Vector2f nowPos = { position.x - (num - 1) * (sizeTexture[typeObstacle] + disBetweenObstacle) , position.y };
		for (int i = 0; i < num; i++)
		{
			obstacle[i]->sprite.setPosition(nowPos);
			nowPos.x += sizeTexture[typeObstacle] + disBetweenObstacle;
		}
	}
	else {
		int typeObstacle = 0;
		//cout << obstacle[0]->getPosition().x << endl; 
		if (obstacle[0]->getPosition().x > 0.f) return;
		int disBetweenObstacle = 600;
		Vector2f nowPos = { 2880.f + (num - 1) * (sizeTexture[typeObstacle] + disBetweenObstacle)  , position.y };
		for (int i = 0; i < num; i++)
		{
			obstacle[i]->sprite.setPosition(nowPos);
			nowPos.x -= sizeTexture[typeObstacle] + disBetweenObstacle;
		}
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
		if (i != (num - 1) && (abs(obstacle[i]->getPosition().x - obstacle[i + 1]->getPosition().x) < 400.f)) continue;
		obstacle[i]->move(delta_time);
	}
	checkEnd();
}
//void render(RenderTarget* target)
//{
//
//}

