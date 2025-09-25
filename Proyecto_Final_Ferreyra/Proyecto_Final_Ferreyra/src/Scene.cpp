#include "Scene.h"

Scene::Scene(sf::RenderWindow& window) : window(window)
{
	wantsChange = false;
}
Scene::~Scene()
{
}
SceneID Scene::GetNextSceneID() const
{
	return nextSceneID;
}
void Scene::SetNextSceneID(bool value)
{
	wantsChange = value;
}