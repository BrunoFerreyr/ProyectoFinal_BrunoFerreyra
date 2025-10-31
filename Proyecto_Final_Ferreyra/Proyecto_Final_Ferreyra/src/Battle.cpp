#include "Battle.h"

Battle::Battle(ResourceManager& resourceManager,AudioManager& audio, int playerLife, const BattleData& data, std::function<void(bool&,int)> callback) : audioManager(audio), playerHealth(playerLife), battleData(data),enemySprite(*data.enemySprite), callback(callback)
{
	playerSprite = new Asset({&resourceManager.GetTexture("../textures/PlayerIdle.png", false, sf::IntRect()), sf::Vector2f({150.0f,400.0f}), sf::IntRect({0,0}, {63,96}), false ,true,nullptr});
	enemyHealth = battleData.enemyHealth;
	
	font = resourceManager.GetFont("../../res/fonts/dogicapixel.ttf");	
	pointsText = new sf::Text(font);
	playerText = new sf::Text(font);
	enemyText = new sf::Text(font);
	roundText = new sf::Text(font);
	roundText->setCharacterSize(40);
	roundText->setPosition({ 500.0f, 170.0f });
	enemySprite.setPosition({ 1000.0f, 400.0f });

	timeBar = new Bar(&resourceManager.GetTexture("../textures/battle/barTimer.png", false, sf::IntRect()), sf::IntRect({ 0,0 }, { 194,44 }), 194);
	timeBar->GetBarAsset()->GetSprite()->setPosition({ 540.0f, 100.0f });

	sf::Vector2f timeBarPosition = timeBar->GetBarAsset()->GetSprite()->getPosition();
	timeBarBackground = new Asset({ &resourceManager.GetTexture("../textures/battle/barTimerBackground.png", false, sf::IntRect()), sf::Vector2f({ timeBarPosition.x - 3, timeBarPosition.y - 3 }), sf::IntRect({ 0,0 }, { 200,50 }), false, true, nullptr });
	
	sf::IntRect backgroundArea({ 0, 0 }, { 1280, 720 });
	sf::Texture& backgroundTexture = resourceManager.GetTexture("../textures/battle/background.png", false, backgroundArea);
	background = new sf::Sprite(backgroundTexture);

	CreateKeyTexts(resourceManager);
	LoadAllBuffers();
	UpdateStats();	

	battleActive = true;
} 
Battle::~Battle()
{
	delete playerSprite;
	delete playerLifeSprite;
	delete enemyLifeSprite;
	delete pointsText;
	delete playerText;
	delete enemyText;
	delete roundText;
	delete timeBar;
	delete timeBarBackground;
	delete background;
	for (auto keyAsset : keysAssets)
	{
		delete keyAsset;
	}
	for (auto keyText : keysText)
	{
		delete keyText;
	}
	for (auto keySprite : keysSprites)
	{
		delete keySprite;
	}
}

void Battle::CreateKeyTexts(ResourceManager& resourceManager)
{
	float spacing = 200.0f; 
	int numButtons = battleData.totalInputs;

	float centerX = 640.0f;
	float startX = centerX - ((numButtons - 1) * spacing) / 2.0f;
	for (int i = 0; i < battleData.totalInputs; i++)
	{
		float x = startX + i * spacing;
		Asset* keyAsset = new Asset({ &resourceManager.GetTexture("../textures/battle/keyButton.png", false, sf::IntRect()), sf::Vector2f({x,300.0f}), sf::IntRect({0,0}, {64,64}), false, true, nullptr });
		sf::Text* keyText = new sf::Text(font);
		keyText->setCharacterSize(40);
		keyText->setFillColor(sf::Color::Black);
		keyText->setPosition({ x + 16.0f, 310.0f });

		keysText.push_back(keyText);
		keysAssets.push_back(keyAsset);
	}

	allKeysChar = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	allKeys = { sf::Keyboard::Key::A, sf::Keyboard::Key::B, sf::Keyboard::Key::C, sf::Keyboard::Key::D, sf::Keyboard::Key::E,
				sf::Keyboard::Key::F, sf::Keyboard::Key::G, sf::Keyboard::Key::H, sf::Keyboard::Key::I, sf::Keyboard::Key::J,
				sf::Keyboard::Key::K, sf::Keyboard::Key::L, sf::Keyboard::Key::M, sf::Keyboard::Key::N, sf::Keyboard::Key::O,
				sf::Keyboard::Key::P, sf::Keyboard::Key::Q, sf::Keyboard::Key::R, sf::Keyboard::Key::S, sf::Keyboard::Key::T,
				sf::Keyboard::Key::U, sf::Keyboard::Key::V, sf::Keyboard::Key::W, sf::Keyboard::Key::X, sf::Keyboard::Key::Y,
				sf::Keyboard::Key::Z };
}
void Battle::LoadAllBuffers() 
{
	correctClickBuffer.loadFromFile("../../res/audios/sfx/sfx_battleClickCorrect.ogg");
	wrongClickBuffer.loadFromFile("../../res/audios/sfx/sfx_battleClickWrong.ogg");
	attackBuffer.loadFromFile("../../res/audios/sfx/sfx_attack.ogg");
	criticalHitBuffer.loadFromFile("../../res/audios/sfx/sfx_criticalHit.ogg");
	receibeDamageBuffer.loadFromFile("../../res/audios/sfx/sfx_receibeDamage.ogg");
	receibeHighDamageBuffer.loadFromFile("../../res/audios/sfx/sfx_highDamageReceibed.ogg");
	winBuffer.loadFromFile("../../res/audios/sfx/sfx_winEffect.ogg");
	loseBuffer.loadFromFile("../../res/audios/sfx/sfx_loseEffect.ogg");
}

void Battle::Update(float deltaTime)
{
	if (!battleStarted)
	{
		if (waitCounter == 0) 
		{
			pointsText->setString("Battle is starting");
		}

		waitCounter += deltaTime;
		if (waitCounter >= timeToStart)
		{
			waitCounter = 0;
			battleStarted = true;
			shouldTap = true;
		}
		return;
	}

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
		timeBar->SetPercentage(100 - (counter * 100) / battleData.limitCounter);
		if (counter >= battleData.limitCounter)
		{
			shouldTap = false;
			counter = 0;
			DoAction();
		}
	}
	else 
	{		
		timeBar->SetPercentage(0 + (waitCounter * 100) / waitLimit);
		waitCounter += deltaTime;
		if (waitCounter >= waitLimit)
		{			
			shouldTap = true;
			waitCounter = 0;
			inputIndex = 0;
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

	window.draw(*background);
	window.draw(*playerSprite->GetSprite());
	window.draw(enemySprite);
	window.draw(*playerText);
	window.draw(*enemyText);
	window.draw(*timeBarBackground->GetSprite());
	window.draw(*timeBar->GetBarAsset()->GetSprite());

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
	for (auto keyText : keysText)
	{
		window.draw(*keyText);
	}
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

			audioManager.PlaySFX(correctClickBuffer);
			keysText[inputIndex]->setString("");
			keysAssets[inputIndex]->GetSprite()->setColor(sf::Color::Green);
			inputIndex++;
			if (inputIndex >= battleData.totalInputs)
			{
				counter = battleData.limitCounter;
				for (auto keyAsset : keysAssets)
				{
					keyAsset->GetSprite()->setColor(sf::Color::White);
				}
			}
		}
		else
		{
			audioManager.PlaySFX(wrongClickBuffer);
			totalPoints = isAttacking ? totalPoints + keyPointValue : totalPoints - keyPointValue / 2;
			counter = battleData.limitCounter;
		}
	}
}
void Battle::ShowKeys()
{
	keysChar.clear();
	correctKeys.clear();

	roundText->setString(isAttacking ? "Defending" : "Attacking");
	for (int i = 0; i < battleData.totalInputs; i++)
	{
		int randomIndex = rand() % allKeys.size();
		keysChar.push_back(allKeysChar[randomIndex]);
		correctKeys.push_back(allKeys[randomIndex]);
		keysText[i]->setString(allKeysChar[randomIndex]);
	}
}
sf::Keyboard::Key Battle::GetCorrectKey() const
{
	return correctKeys[inputIndex];
}
void Battle::DoAction()
{
	for (auto keyAsset : keysAssets)
	{
		keyAsset->GetSprite()->setColor(sf::Color::White);
	}

	isAttacking = !isAttacking;
	if (isAttacking)
	{
		if (inputIndex >= battleData.totalInputs) 
		{
			audioManager.PlaySFX(attackBuffer);
			audioManager.PlaySFX(criticalHitBuffer);
		}
		else if(totalPoints < 0)
		{
			totalPoints = 0;
		}
		else 
		{ 
			audioManager.PlaySFX(attackBuffer);
		}
		enemyHealth -= totalPoints;
		
		if (enemyHealth <= 0)
		{
			enemyHealth = 0;
			playerWins = true;
			battleEnded = true;
			audioManager.PlaySFX(winBuffer);
		}
	}
	else
	{
		if (inputIndex <= 1) 
		{
			audioManager.PlaySFX(receibeHighDamageBuffer);
		}
		else
		{
			audioManager.PlaySFX(receibeDamageBuffer);
		}

		if (totalPoints > battleData.enemyDamage) 
		{
			totalPoints = battleData.enemyDamage - 2;
		}
		playerHealth -= (battleData.enemyDamage - totalPoints);
		if (playerHealth <= 0)
		{
			playerHealth = 0;
			battleEnded = true;
			audioManager.PlaySFX(loseBuffer);
		}
	}
	
	UpdateStats();	
	shouldTap = false;
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
		pointsText->setString("Damage receibed: " + std::to_string(battleData.enemyDamage - totalPoints));
	}

	playerText->setCharacterSize(24);
	playerText->setString("Player: " + std::to_string(playerHealth));
	playerText->setPosition({ 100.0f, 50.0f });

	enemyText->setCharacterSize(24);
	enemyText->setString("Enemy: " + std::to_string(enemyHealth));
	enemyText->setPosition({ 1000.0f, 50.0f });

	if (battleEnded)
	{
		if (playerWins)
		{
			pointsText->setFillColor(sf::Color::Green);
			pointsText->setPosition({ 380.0f, 50.0f });
			pointsText->setString("You Win!, you earn " + std::to_string(battleData.metalsAmount) + " metals!!");
		}
		else
		{
			pointsText->setFillColor(sf::Color::Red);
			pointsText->setPosition({ 550.0f, 50.0f });
			pointsText->setString("You Lose!");
		}
	}
}
void Battle::EndBattle()
{
	battleActive = false;
	callback(playerWins, battleData.enemyID);
}




