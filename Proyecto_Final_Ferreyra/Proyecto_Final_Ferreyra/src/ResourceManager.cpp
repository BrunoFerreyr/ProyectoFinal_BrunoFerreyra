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
	std::string pathh = path;
	pathh = GetResourcePath(pathh);
	auto iterator = textures.find(pathh);
	if (iterator == textures.end()) 
	{		
		std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
		
		if (!texture->loadFromFile(pathh, useMipmap,area))
		{
			texture.reset();
			throw std::runtime_error("Failed to load texture: " + pathh);
		}

		iterator = textures.try_emplace(pathh, std::move(texture)).first;
	}
	
	return *iterator->second;
}

sf::Font& ResourceManager::GetFont(const std::string& path) {
	std::string pathh = path;
	pathh = GetResourcePath(pathh);
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

std::string ResourceManager::GetResourcePath(const std::string& relativePath) 
{
	// Si no existe, intenta con "res/" + path sin los "../"
	std::string resPath = "../../res/" + relativePath.substr(3); // quita los "../"
	if (std::filesystem::exists(resPath))
		return resPath;

	// Si no existe ninguna, devuelve la original (para debug)
	return relativePath;
}