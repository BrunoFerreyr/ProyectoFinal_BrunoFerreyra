#include <SFML/Graphics.hpp>
#include "Game.h"
enum class Difficulty
{
	Easy = 1,
	Normal = 2,
	Hard = 3
};
class Enemy 
{

};
constexpr int ReturnEnemyCount(int value, Difficulty diff)
{
	return value * static_cast<int>(diff);
}
int main()
{    
	/*int enemyCount = ReturnEnemyCount(10, Difficulty::Normal);
	Enemy* enemies = new Enemy[enemyCount];
	std::cout << "Enemy count: " <<  enemyCount << std::endl;
	return 0;*/
	Game* game = new Game();
	game->Play();

	delete game;
	return 0;
}