#pragma once


class GraphicsSettings
{
public:
	GraphicsSettings();
	

	//Variables
	std::string title;
	sf::VideoMode resolution;
	bool fullScreen;
	bool vsync;
	unsigned framerateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	//Functions
	void saveToFile(const std::string path);
	
	void loadFromFile(const std::string path);
	
};
