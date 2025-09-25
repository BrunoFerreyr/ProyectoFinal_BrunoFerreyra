#pragma once
#include <SFML/Graphics.hpp>

enum class SceneID
{
	MainMenu,
	Gameplay,
};
class Scene
{
public:
	Scene(sf::RenderWindow& window);
	~Scene();

	virtual void Draw() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Input() = 0;
	virtual void HandleEvents(const sf::Event& event) = 0;
	virtual SceneID GetNextSceneID() const;
	virtual void SetNextSceneID(bool value);

protected:
	SceneID nextSceneID;
	sf::RenderWindow& window;
	bool wantsChange;
};