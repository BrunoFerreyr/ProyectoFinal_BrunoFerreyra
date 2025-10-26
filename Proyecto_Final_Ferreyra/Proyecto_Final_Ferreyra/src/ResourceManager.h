#pragma once
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class ResourceManager 
{
public:
	ResourceManager();
	~ResourceManager();

	sf::Texture& GetTexture(const std::string& path, bool useMipmap, sf::IntRect area);
	sf::Font& GetFont(const std::string& path);
	sf::SoundBuffer& GetSound(const std::string& path);
	std::string GetResourcePath(const std::string& relativePath);

private:
	std::map<std::string, std::unique_ptr<sf::Texture>> textures;
	std::map<std::string, sf::Font*> fonts;
	std::map<std::string, sf::SoundBuffer*> soundBuffers;
};