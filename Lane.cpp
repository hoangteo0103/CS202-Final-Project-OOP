#include "Lane.h"
vector<Vector2u> imageContainVc = { Vector2u(14,1) };
vector<string> pathTexture = { "Skin1.png" };
vector<int> sizeTexture = { 120};


Lane::Lane(int typeObstacle, int dir, int num, float speed, string texture_dir, Vector2f pos)
{
	this->num = num;
	Vector2f nowPos = { pos.x - (num - 1) * sizeTexture[typeObstacle], pos.y };
	for (int i = 1; i <= num; i++)
	{
		COBSTACLE* now = new COBSTACLE(pathTexture[typeObstacle], imageContainVc[typeObstacle], 0.1f, speed, nowPos, dir);
		nowPos.x += sizeTexture[typeObstacle];
		obstacle.push_back(now);
	}

	numTrafficLight = 1; 

	float start = 400.f;
	for (int i = 0; i < numTrafficLight; i++)
	{
		CTRAFFICLIGHT *tmp = new CTRAFFICLIGHT(Vector2f(start, pos.y), 2.0f, 2.0f, 2.0f);
		start += 500.f;
		lights.push_back(tmp); 
	}

	if (!(texture.loadFromFile(texture_dir)))
	{
		cout << "Could Not Load Lane File.." << endl;
	}
	position = pos;
	sprite.setTexture(texture);
	this->sprite.setPosition(position);
}

void Lane::updateSpeed()
{
	for (int i = 0; i < num; i++)
	{

		obstacle[i]->setSpeed(obstacle[i]->origin_speed);
		for (int j = 0; j < numTrafficLight; j++)
		{
			//cout << obstacle[i]->sprite.getPosition().x << ' ' << lights[i]->isVehiclePass() << ' ' << lights[i]->getPos() << endl;
			if ( (obstacle[i]->sprite.getPosition().x  > lights[i]->getPos() + 48.f )  || lights[i]->isVehiclePass()) continue;
			int dis = lights[i]->getPos() + 48.f -  (obstacle[i]->sprite.getPosition().x + obstacle[i]->animation.uv_rect.width);
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

	for (int i = 0; i < numTrafficLight; i++)
	{
		lights[i]->draw(window);
	}
}
void Lane::checkEnd()
{
	int typeObstacle = 0;
	if (obstacle[num - 1]->getPosition().x < 2880.f) return;
	Vector2f nowPos = { position.x - (num - 1) * sizeTexture[typeObstacle], position.y };
	for (int i = 0; i < num; i++)
	{
		obstacle[i]->sprite.setPosition(nowPos);
	}

}
void Lane::update(float delta_time)
{
	
	for (int i = 0; i < num; i++)
	{
		obstacle[i]->move(delta_time);
	}
	checkEnd(); 
	for (int i = 0; i < numTrafficLight; i++)
	{
		lights[i]->transition(delta_time); 
	}
}
//void render(RenderTarget* target)
//{
//
//}