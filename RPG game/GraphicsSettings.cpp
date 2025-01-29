#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	this->title = "TITLE";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullScreen = false;
	this->vsync = false;
	this->framerateLimit = 144;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();
}

void GraphicsSettings::saveToFile(const std::string path)
{
	
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		//Todo erase/clear the file first before writing anything
		ofs << this->title << '\n';
		ofs << this->resolution.width << " " << this->resolution.height << '\n';
		ofs << this->framerateLimit << '\n';
		ofs << this->vsync << '\n';
		ofs << this->contextSettings.antialiasingLevel << '\n';
		ofs << this->fullScreen << '\n';
	}
	ofs.close();
	
}

void GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->framerateLimit;
		ifs >> this->vsync;
		ifs >> this->contextSettings.antialiasingLevel;
		ifs >> this->fullScreen;
	}
	ifs.close();
}
