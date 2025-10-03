#include "Player.h"
Player::Player(const std::string& path, const sf::Vector2i& spriteSheetSize, ResourceManager& resourceManager, Dialog* dialog)
{
	sf::IntRect area({0,0}, spriteSheetSize);

	sf::Texture& texture = resourceManager.GetTexture(path,false,area);
	animations = new PlayerAnimations(texture);

	sprite = new sf::Sprite(texture);

	sf::IntRect startArea({0,0}, {64, 96});
	sprite->setTextureRect(startArea);

	sprite->setPosition({ 600.0f, 600.0f });
	sprite->setScale({ 1.0f, 1.0f });

	speed = 200.0f;
	moveDirection = { 0,0 };

	this->dialog = dialog;	
}
Player::~Player()
{
	delete sprite;
}
void Player::Input()
{
	MovementInput();
}
void Player::Update(float deltaTime)
{
	Movement(deltaTime);
	Animation(deltaTime);
}
void Player::MovementInput() 
{
	direction = sf::Vector2f();
	//moveDirection = sf::Vector2f({ 0,0 });

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) 
	{
		moveDirection = sf::Vector2f({ 1,0 });
		direction += moveDirection;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		moveDirection = sf::Vector2f({ -1,0 });
		direction += moveDirection;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		moveDirection = sf::Vector2f({ 0,1 });
		direction += moveDirection;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		moveDirection = sf::Vector2f({ 0,-1 });
		direction += moveDirection;
	}	

	if (std::abs(direction.x) < 0.0001f && std::abs(direction.y) < 0.0001f)
	{
		animations->SetState(PlayerState::Idle);
	}
	else
	{
		animations->SetState(PlayerState::Walking);
	}
}

void Player::Movement(float deltaTime)
{
	if (dialog->IsActive() && currentMap == nullptr) return;

	sf::Vector2f movement = direction * speed * deltaTime;
	sf::Vector2f newPosition = sprite->getPosition();

	// Movimiento en X
	if (movement.x != 0.0f) {
		sf::FloatRect futureBounds = GetBounds();
		futureBounds.position.x += movement.x;
		if (!currentMap->CheckCollision(futureBounds,false)) {
			newPosition.x += movement.x;
		}
	}

	// Movimiento en Y
	if (movement.y != 0.0f) {
		sf::FloatRect futureBounds = GetBounds();
		futureBounds.position.y += movement.y;
		if (!currentMap->CheckCollision(futureBounds,false)) {
			newPosition.y += movement.y;
		}
	}

	sprite->setPosition(newPosition);
}
void Player::Animation(float deltaTime) 
{
	animations->Update(deltaTime, moveDirection);
	sprite->setTextureRect(animations->GetSprite());
}
void Player::Interact() 
{
	if (isInteracting && !dialog->IsActive())
	{
		bool interacted = false;
		//std::cout << "Interacting with NPC or object..." << std::endl;
		if (currentMap != nullptr && !interacted)
		{///TO DO
			interacted = currentMap->CheckCollision(GetBounds(),true);
		}
	}
}
void Player::Draw(sf::RenderWindow& window)
{
	window.draw(*sprite);
}
sf::FloatRect Player::GetBounds()
{
	return sprite->getGlobalBounds();
}
void Player::SetCurrentMap(Map* map, sf::Vector2f position)
{
	currentMap = map;
	sprite->setPosition(position);
}
void Player::HandleEvents(const sf::Event& event)
{
	if (const auto keyEvent = event.getIf<sf::Event::KeyPressed>())
	{

		if (keyEvent->code == sf::Keyboard::Key::E && !isInteracting && !dialog->IsActive())
		{
			std::cout << "Interaccion" << std::endl;
			isInteracting = true;
			Interact();
		}
		if (keyEvent->code == sf::Keyboard::Key::Enter && dialog->IsActive()) 
		{
			dialog->NextDialog();
		}
	}

	if (const auto keyEvent = event.getIf<sf::Event::KeyReleased>())
	{
		if (keyEvent->code == sf::Keyboard::Key::E)
		{
			std::cout << "Dejar interaccion" << std::endl;
			isInteracting = false;
		}
	}
}