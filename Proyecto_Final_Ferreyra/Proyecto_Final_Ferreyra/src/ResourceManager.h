#pragma once
#include <string>
#include <map>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class ResourceManager {
private:
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, sf::Font*> fonts;
	std::map<std::string, sf::SoundBuffer*> soundBuffers;
public:
	ResourceManager();
	~ResourceManager();
	
	sf::Texture& GetTexture(const std::string& path, bool useMipmap, sf::IntRect area);
	sf::Font& GetFont(const std::string& path);
	sf::SoundBuffer& GetSound(const std::string& path);
};