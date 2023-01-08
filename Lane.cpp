#include "Lane.h"
vector<Vector2u> imageContainVc = { Vector2u(14,1) };
vector<string> pathTexture = { "Skin1.png" };
vector<int> sizeTexture = { 250};


Lane::Lane(int typeObstacle, int dir, int num, float speed, int type, Vector2f pos)
{
	random_device rd;
	mt19937 rng(rd());

	uniform_real_distribution<float> time_rand(0, 5.0f);
	switch_time = time_rand(rng);
	now_time = 0;
	this->numTrafficLight = 0;

	sf::Vector2u imageContainer;


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

		uniform_int_distribution<int> num_light(1, 3);

		numTrafficLight = num_light(rng);
		float start = 1500.f;
		for (int i = 0; i < numTrafficLight; i++)
		{
			CTRAFFICLIGHT* tmp = new CTRAFFICLIGHT(Vector2f(start, pos.y-70.f), 10.0f, 1.0f, 5.0f);
			start += 1000.f;
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
	cout << "dir: " << dir << endl;

	this->num = num;
	int disBetweenObstacle = 250;

	if (dir!=1)
	{
		Vector2f nowPos = {0.f - (num - 1) * (sizeTexture[typeObstacle] + disBetweenObstacle)  , pos.y};
		for (int i = 1; i <= num; i++)
		{
			COBSTACLE* now = new COBSTACLE(this->obstacle_path, imageContainer, 0.1f, speed, nowPos, dir);
			nowPos.x += (sizeTexture[typeObstacle] + disBetweenObstacle);
			obstacle.push_back(now);
		}
		reverse(obstacle.begin(), obstacle.end());
	}
	else {
		Vector2f nowPos = { 2880.f +  (num - 1) * (sizeTexture[typeObstacle] + disBetweenObstacle)  , pos.y};
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
		for (int i = 0; i < num; i++)
		{
			bool ok = true;
			for (int j = 0; j < numTrafficLight; j++)
			{
				ok &= lights[j]->isVehiclePass();
					obstacle[i]->setSpeed(obstacle[i]->origin_speed);
			}
			obstacle[i]->setSpeed(ok ? obstacle[i]->origin_speed : 0);
		}
}

void Lane::draw(sf::RenderWindow& window)
{
	window.draw(this->sprite);
	if(switch_time <= now_time)
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
		int disBetweenObstacle = 250;
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
		int disBetweenObstacle = 250;
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
	now_time += delta_time;
	for (int i = 0; i < numTrafficLight; i++)
	{
		lights[i]->transition(delta_time);
	}
	if (now_time < switch_time) return;
	
	for (int i = 0; i < num; i++)
		obstacle[i]->move(delta_time);
	checkEnd();
}

Lane::Lane(istream& in)
{
	in >> now_time >> switch_time;
	in >> position.x >> position.y;
	in >> num >> numTrafficLight >> type >> dir;
	in >> obstacle_path >> road_path; 
	for (int i = 0; i < num; i++)
	{
		COBSTACLE* now = new COBSTACLE(in);
		obstacle.push_back(now);
	}
	for (int i = 0; i < numTrafficLight; i++)
	{
		CTRAFFICLIGHT* now = new CTRAFFICLIGHT(in);
		lights.push_back(now);
	}

	// Init 
	if (!(texture.loadFromFile("asset/road/road0.png")))
	{
		cout << "Could Not Load Lane File.." << endl;
	}
	this->sprite.setTexture(texture);
	this->sprite.setPosition(position);
}

void Lane::saveLane(ostream& out)
{
	out << now_time << ' ' << switch_time << '\n';
	out << position.x << ' ' << position.y << '\n';
	out << num << ' ' << numTrafficLight << ' ' << type << ' ' << dir << '\n';
	out << obstacle_path << ' ' << road_path << '\n';
	// save obstacle first then trafficlight

	for (int i = 0; i < num; i++)
	{
		this->obstacle[i]->saveObstacle(out);
	}
	for (int i = 0; i < numTrafficLight; i++)
	{
		this->lights[i]->saveLight(out);
	}
}
