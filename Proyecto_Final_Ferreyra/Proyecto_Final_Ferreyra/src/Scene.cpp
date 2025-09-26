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
bool Scene::GetWantsChange() const
{
	return wantsChange;
}
void Scene::SetWantsChange(bool value)
{
	wantsChange = value;
}