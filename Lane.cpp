#include "Lane.h"
vector<Vector2u> imageContainVc = {Vector2u(14,1)};
vector<string> pathTexture = { "Skin1.png" };
vector<int> sizeTexture = { 24 };
Lane::Lane(int typeObstacle, int dir, int num, float speed, Vector2f pos)
{
	this->num = num;
	Vector2f nowPos = { pos.x - (num-1) * sizeTexture[typeObstacle], pos.y };
	for (int i = 1; i <= num; i++)
	{
		COBSTACLE* now = new COBSTACLE(pathTexture[typeObstacle], imageContainVc[typeObstacle],0.1f,  speed, nowPos, dir); 
		nowPos.x += sizeTexture[typeObstacle];
		obstacle.push_back(now);
	}
}

void Lane::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < num; i++)
	{
		//cout << obstacle[i]->sprite.getPosition().x << ' ' << obstacle[i]->sprite.getPosition().y << endl;
		obstacle[i]->draw(window); 
	}
}

void Lane::move(float delta_time)
{
	for (int i = 0; i < num; i++)
	{
		obstacle[i]->move(delta_time);
	}
}
void render(RenderTarget* target)
{

}