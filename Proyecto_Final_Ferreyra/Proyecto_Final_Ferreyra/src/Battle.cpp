#include "Battle.h"

Battle::Battle(ResourceManager& resourceManager, int playerLife, int enemyLife, Asset* enemySprite, std::function<void(bool&,Asset*)> callback) : playerHealth(playerLife), enemyHealth(enemyLife), callback(callback)
{
	playerSprite = new Asset(&resourceManager.GetTexture("../textures/PlayerIdle.png", false, sf::IntRect()), sf::Vector2f({150.0f,400.0f }), sf::IntRect({0,0}, {63,96}), false);
	this->enemySprite = enemySprite;
	//playerLifeSprite = new Asset(&resourceManager.GetTexture("../textures/PlayerIdle.png", false, sf::IntRect()), sf::Vector2f({ 0.0f,0.0f }), sf::IntRect({ 0,0 }, { 378,768 }), false);
	//enemyLifeSprite = new Asset(&resourceManager.GetTexture("../textures/PlayerIdle.png", false, sf::IntRect()), sf::Vector2f({ 0.0f,0.0f }), sf::IntRect({ 0,0 }, { 378,768 }), false);

	font = resourceManager.GetFont("../fonts/dogicapixel.ttf");	
	pointsText = new sf::Text(font);
	playerText = new sf::Text(font);
	enemyText = new sf::Text(font);
	keysText = new sf::Text(font);
	roundText = new sf::Text(font);
	roundText->setCharacterSize(40);
	roundText->setPosition({ 500.0f, 170.0f });

	timeBar = new Bar(&resourceManager.GetTexture("../textures/battle/barTimer.png", false, sf::IntRect()), sf::IntRect({ 0,0 }, { 194,44 }), 194);
	timeBar->GetBar()->GetSprite()->setPosition({ 540.0f, 100.0f });

	for (int i = 0; i < 3; i++)
	{
		Asset* keyAsset = new Asset(&resourceManager.GetTexture("../textures/battle/keyButton.png", false, sf::IntRect()), sf::Vector2f({ 400.0f + (200 * i),300.0f}), sf::IntRect({0,0}, {64,64}), false);
		keysAssets.push_back(keyAsset);
	}
	allKeysChar = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	allKeys = { sf::Keyboard::Key::A, sf::Keyboard::Key::B, sf::Keyboard::Key::C, sf::Keyboard::Key::D, sf::Keyboard::Key::E,
				sf::Keyboard::Key::F, sf::Keyboard::Key::G, sf::Keyboard::Key::H, sf::Keyboard::Key::I, sf::Keyboard::Key::J,
				sf::Keyboard::Key::K, sf::Keyboard::Key::L, sf::Keyboard::Key::M, sf::Keyboard::Key::N, sf::Keyboard::Key::O,
				sf::Keyboard::Key::P, sf::Keyboard::Key::Q, sf::Keyboard::Key::R, sf::Keyboard::Key::S, sf::Keyboard::Key::T,
				sf::Keyboard::Key::U, sf::Keyboard::Key::V, sf::Keyboard::Key::W, sf::Keyboard::Key::X, sf::Keyboard::Key::Y,
				sf::Keyboard::Key::Z };

	battleActive = true;
	UpdateStats();
} 
Battle::~Battle()
{
	delete playerSprite;
	//delete enemySprite;
	delete playerLifeSprite;
	delete enemyLifeSprite;
	delete pointsText;
	delete playerText;
	delete enemyText;
	delete keysText;
	delete roundText;
	delete timeBar;
	for (auto keyAsset : keysAssets)
	{
		delete keyAsset;
	}
}

void Battle::StartBattle()
{
}
void Battle::EndBattle()
{
	battleActive = false;
	callback(playerWins, enemySprite);
}
void Battle::Update(float deltaTime)
{
	if (battleEnded)
	{
		waitCounter += deltaTime;
		if (waitCounter >= waitLimit)
		{
			EndBattle();
		}
		return;
	}

	if (!battleActive)
	{
		return;
	}

	if (shouldTap) 
	{
		if (counter == 0) {
			totalPoints = 0;
			ShowKeys();
		}
		counter += deltaTime;
		timeBar->SetPercentage(100 - (counter * 100) / limitCounter);
		//HandleEvents(sf::Event());
		if (counter >= limitCounter)
		{
			shouldTap = false;
			counter = 0;
			DoAction();
		}
	}
	else 
	{		
		waitCounter += deltaTime;
		if (waitCounter >= waitLimit)
		{			
			shouldTap = true;
			waitCounter = 0;
			inputIndex = 0;
			//keysSprites.clear();
			correctKeys.clear();
		}
	}
}
void Battle::Draw(sf::RenderWindow& window)
{
	if (!battleActive) 
	{
		return;
	}

	window.draw(*playerSprite->GetSprite());
	window.draw(*enemySprite->GetSprite());
	//window.draw(*playerLifeSprite->GetSprite());
	//window.draw(*enemyLifeSprite->GetSprite());
	window.draw(*playerText);
	window.draw(*enemyText);
	if (!shouldTap) 
	{
		window.draw(*pointsText);
		return;
	}
	for (auto keyAsset : keysAssets)
	{
		window.draw(*keyAsset->GetSprite());
	}
	window.draw(*roundText);
	window.draw(*keysText);
	window.draw(*timeBar->GetBar()->GetSprite());
}

void Battle::ShowKeys()
{
	keysChar.clear();
	correctKeys.clear();

	keysText->setString("");
	keysText->setCharacterSize(60);
	keysText->setFillColor(sf::Color::Cyan);
	keysText->setPosition({ 470.0f, 300.0f });

	roundText->setString(isAttacking ? "Defending" : "Attacking");
	//keysSprites.clear();
	for (int i = 0; i < totalInputs; i++)
	{
		int randomIndex = rand() % allKeys.size();
		keysChar.push_back(allKeysChar[randomIndex]);
		correctKeys.push_back(allKeys[randomIndex]);
		std::cout << allKeysChar[randomIndex] << std::endl;
		keysText->setString(keysText->getString() + allKeysChar[randomIndex] + "   ");
	}
}

void Battle::DoAction()
{
	//totalPoints += keyPointValue;
	isAttacking = !isAttacking;
	if (isAttacking)
	{
		enemyHealth -= totalPoints;
		//calcular barra enemigo
		if (enemyHealth <= 0)
		{
			enemyHealth = 0;
			PlayerWin();
		}
	}
	else
	{
		playerHealth -= (enemyDamage - totalPoints);
		if (playerHealth <= 0)
		{
			playerHealth = 0;
			PlayerLose();
		}
	}
	UpdateStats();
	shouldTap = false;
}
void Battle::HandleEvents(const sf::Event& event)
{
	if (!battleActive || !shouldTap)
	{
		return;
	}
	if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>())
	{
		if (keyEvent->code == GetCorrectKey())
		{
			totalPoints += keyPointValue;
			inputIndex++;
			if (inputIndex >= totalInputs)
			{
				counter = limitCounter;
				inputIndex = 0;
			}
		}
		else
		{			
			totalPoints = isAttacking? totalPoints + keyPointValue : totalPoints - keyPointValue/2;
			counter = limitCounter;
		}
		
	}
}
sf::Keyboard::Key Battle::GetCorrectKey() const
{
	return correctKeys[inputIndex];
}
void Battle::UpdateStats()
{
	pointsText->setCharacterSize(24);
	if (isAttacking)
	{
		pointsText->setFillColor(sf::Color::Red);
		pointsText->setPosition({ 500.0f, 50.0f });
		pointsText->setString("Damage dealt: " + std::to_string(totalPoints));
	}
	else
	{
		pointsText->setFillColor(sf::Color::Green);
		pointsText->setPosition({ 450.0f, 50.0f });
		pointsText->setString("Damage receibed: " + std::to_string(enemyDamage - totalPoints));
	}

	playerText->setCharacterSize(24);
	playerText->setString("Player: " + std::to_string(playerHealth));
	playerText->setPosition({ 100.0f, 50.0f });

	enemyText->setCharacterSize(24);
	enemyText->setString("Enemy: " + std::to_string(enemyHealth));
	enemyText->setPosition({ 1000.0f, 50.0f });
}

void Battle::PlayerWin()
{
	battleEnded = true;
	pointsText->setString("You Win!");
	playerWins = true;
}
void Battle::PlayerLose()
{
	battleEnded = true;
	playerWins = false;
	pointsText->setString("You Lose!");
}
