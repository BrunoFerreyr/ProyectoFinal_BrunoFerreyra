#pragma once
#include <SFML/Graphics.hpp>
#include "SceneID.h"

class Scene
{
public:
	Scene(sf::RenderWindow& window);
	virtual ~Scene();

	virtual void Initialize();
	virtual void Draw() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Input() = 0;
	virtual void HandleEvents(const sf::Event& event) = 0;
	virtual SceneID GetNextSceneID() const;
	virtual bool GetWantsChange() const;
	virtual void SetWantsChange(bool value);

protected:
	SceneID nextSceneID;
	sf::RenderWindow& window;
	bool wantsChange;
};