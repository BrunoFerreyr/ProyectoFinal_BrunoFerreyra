#include "Scene.h"

Scene::Scene(sf::RenderWindow& window) : window(window)
{
	wantsChange = false;
}
Scene::~Scene()
{
}
void Scene::Initialize()
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