#include "ResourceManager.h"
ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {	
	for (auto& pair : fonts) {
		delete pair.second;
	}
	for (auto& pair : soundBuffers) {
		delete pair.second;
	}
}

sf::Texture& ResourceManager::GetTexture(const std::string& path, bool useMipmap, sf::IntRect area) {
	auto iterator = textures.find(path);
	if (iterator == textures.end()) 
	{		
		std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
		
		if (!texture->loadFromFile(path, useMipmap,area)) 
		{
			texture.reset();
			throw std::runtime_error("Failed to load texture: " + path);
		}

		iterator = textures.try_emplace( path, std::move(texture)).first;
	}
	
	return *iterator->second;
}

sf::Font& ResourceManager::GetFont(const std::string& path) {
	auto iterator = fonts.find(path);
	if (iterator == fonts.end()) 
	{
		sf::Font* font = new sf::Font();
		if (!font->openFromFile(path)) 
		{
			delete font;
			throw std::runtime_error("Failed to load font: " + path);
		}
		iterator = fonts.emplace(path, font).first;
	}
	
	return *iterator->second;
}

sf::SoundBuffer& ResourceManager::GetSound(const std::string& path) {
	auto iterator = soundBuffers.find(path);
	if (iterator == soundBuffers.end())
	{
		sf::SoundBuffer* buffer = new sf::SoundBuffer();
		if (!buffer->loadFromFile(path))
		{
			delete buffer;
			throw std::runtime_error("Failed to load sound: " + path);
		}
		iterator = soundBuffers.emplace(path, buffer).first;
	}

	return *iterator->second;
}