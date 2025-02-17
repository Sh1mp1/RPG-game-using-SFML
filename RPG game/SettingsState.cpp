#include "stdafx.h"
#include "SettingsState.h"


void SettingsState::initKeybinds()
{
	std::ifstream ifs("config/settingsstate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key;
		std::string key_value;
		while (ifs >> key >> key_value)
		{
			this->keybinds.emplace(key, this->supportedKeys->at(key_value));
		}

	}
	ifs.close();
}

SettingsState::SettingsState(StateData* state_data)
	:State(state_data)
{
	this->initKeybinds();
	this->initButtons();
	this->initToggleButtons();
	this->initBackground();
	this->initFont();
	this->initVariables();
	this->initDropDownList();
}

SettingsState::~SettingsState()
{
	for (auto& i : this->buttons)
	{
		delete i.second;
	}

	for (auto& i : this->toggleButtons)
	{
		delete i.second;
	}

	for (auto& i : this->dropDownLists)
	{
		delete i.second;
	}
}


void SettingsState::initFont()
{
	this->mousePosText.setFont(*this->stateData->font);


	this->mousePosText.setOutlineColor(sf::Color::Black);
	this->mousePosText.setOutlineThickness(1.f);
	this->mousePosText.setString("START");
	this->mousePosText.setPosition(sf::Vector2f(0.f, 0.f));
	this->mousePosText.setCharacterSize(15);

	
	this->optionsText.setFont(*this->stateData->font);

	this->optionsText.setPosition(sf::Vector2f(400.f, 300.f));
	this->optionsText.setCharacterSize(35);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));
	this->optionsText.setString("RESOLUTION \n\n\n ANTIALIASING \n\n\n FULLSCREEN \n\n\n VSYNC");
}

void SettingsState::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("Textures/background.jpg"))
	{
		std::cout << "ERROR::SETTINGSSTATE::COULDNT LOAD BACKGROUND" << '\n';
	}
	this->background.setTexture(this->backgroundTexture);

	float scale_x = static_cast<float>(window->getSize().x) / this->backgroundTexture.getSize().x;
	float scale_y = static_cast<float>(window->getSize().y) / this->backgroundTexture.getSize().y;


	this->background.setScale(sf::Vector2f(scale_x, scale_y));
}

void SettingsState::initButtons()
{
	//this->buttons.emplace("SETTINGS", new gui::Button(sf::Vector2f(460.f, 600.f), &this->font, "SETTINGS",
	//	sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40.f));

	float posX = static_cast<float>(this->stateData->window->getSize().x) * 0.8f;

	float posY = static_cast<float>(this->stateData->window->getSize().y);

	this->buttons.emplace("EXIT", new gui::Button(sf::Vector2f(posX, posY * 0.8f), this->stateData->font, "EXIT",
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40));

	this->buttons.emplace("APPLY", new gui::Button(sf::Vector2f(posX, posY * 0.65f), this->stateData->font, "APPLY",
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40));
}

void SettingsState::initToggleButtons()
{
	this->toggleButtons.emplace("FULLSCREEN", new gui::ToggleButton(sf::Vector2f(1000.f, 570.f), sf::Vector2f(40.f, 40.f), this->stateData->gfxSettings->fullScreen));

	this->toggleButtons.emplace("VSYNC", new gui::ToggleButton(sf::Vector2f(1000.f, 684.f), sf::Vector2f(40.f, 40.f), this->stateData->gfxSettings->vsync));
}

void SettingsState::initDropDownList()
{	
	int currentResolutionIndex = 0;
	std::vector<std::string> dropDownText;
	for (int i = 0; i < this->videoModes.size(); ++i)
	{
		dropDownText.push_back(std::to_string(this->videoModes[i].width) + " X " + std::to_string(this->videoModes[i].height));

		if (this->videoModes[i].width == this->stateData->gfxSettings->resolution.width &&
			this->videoModes[i].height == this->stateData->gfxSettings->resolution.height)
		{
			currentResolutionIndex = i;	//Saves the index of the current window resolution in the video modes list
		}

	}
	this->dropDownLists.emplace("RESOLUTION", new gui::DropDownList(sf::Vector2f(1000.f, 300.f), sf::Vector2f(10.f, 30.f), *this->stateData->font, dropDownText, currentResolutionIndex));

	int currentAntiAliasingLevelIndex = 0;
	std::vector<std::string> antiAliasingLevels;	
	for (int i = 0; i <= 4; ++i)
	{
		if (i == 0)
		{
			antiAliasingLevels.push_back("0");
			continue;
		}
		antiAliasingLevels.push_back(std::to_string(i) + "X");

		if (i == this->stateData->gfxSettings->contextSettings.antialiasingLevel)
		{
			currentAntiAliasingLevelIndex = i;
		}
	}

	this->dropDownLists.emplace("ANTIALIASINGLEVEL", new gui::DropDownList(sf::Vector2f(1000.f, 440.f), sf::Vector2f(50.f, 30.f), *this->stateData->font, antiAliasingLevels, 
		currentAntiAliasingLevelIndex));

}

void SettingsState::initWindow()
{
	if (this->gfxSettings.fullScreen)
		this->window->create(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Fullscreen, this->gfxSettings.contextSettings);

	else
		this->window->create(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);


	this->window->setFramerateLimit(this->gfxSettings.framerateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.vsync);
}

void SettingsState::initVariables()
{
	this->videoModes = sf::VideoMode::getFullscreenModes();
}


void SettingsState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("close"))))
	{
		this->endState();
	}
}

void SettingsState::updateButtons()
{

	//Updates all button states and changes their color with mouse interaction
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosWindow);
	}
	
	
	//Exits when "EXIT" button is pressed
	if (this->buttons.at("EXIT")->isPressed())
	{
		this->endState();
	}

	if (this->buttons.at("APPLY")->isPressed())
	{
		short unsigned resolution_id = this->dropDownLists.at("RESOLUTION")->getActiveElementID();

		short unsigned antialiasing_id = this->dropDownLists.at("ANTIALIASINGLEVEL")->getActiveElementID();

		this->gfxSettings.resolution = this->videoModes.at(resolution_id);

		this->gfxSettings.contextSettings.antialiasingLevel = antialiasing_id;

		this->gfxSettings.fullScreen = this->toggleButtons.at("FULLSCREEN")->isEnabled();

		this->gfxSettings.vsync = this->toggleButtons.at("VSYNC")->isEnabled();

		this->gfxSettings.saveToFile("config/window.ini");
		
		this->initWindow();
		
		this->updateButtonPos();

		//std::cout << "X " << this->window->getSize().x << " Y " << this->window->getSize().y;
	}
}

void SettingsState::updateText()
{
	this->mousePosText.setPosition(sf::Vector2f(this->mousePosView.x + 10.f, this->mousePosView.y + 10.f));

	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	this->mousePosText.setString(ss.str());


}

void SettingsState::updateGUI()
{
	this->updateButtons();
	this->updateDropDownList();
	this->updateToggleButtons();
}

void SettingsState::updateDropDownList()
{

	for (auto& i : this->dropDownLists)
	{
		i.second->update(this->mousePosWindow);
	}
}

void SettingsState::updateButtonPos()
{
	float posX = static_cast<float>(this->stateData->window->getSize().x) * 0.8f;

	float posY = static_cast<float>(this->stateData->window->getSize().y);

	this->buttons.at("EXIT")->centreText(sf::Vector2f(posX, posY * 0.8f));
	this->buttons.at("APPLY")->centreText(sf::Vector2f(posX, posY * 0.65f));
}

void SettingsState::updateToggleButtons()
{
	for (auto& i : this->toggleButtons)
	{
		i.second->update(this->mousePosView);
	}
}

void SettingsState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePositions();
	this->updateText();
	this->updateGUI();
}

void SettingsState::renderGUI(sf::RenderTarget& target)
{
	for (auto i : this->buttons)
	{
		i.second->render(target);
	}

	for (auto i : this->toggleButtons)
	{
		i.second->render(target);
	}

	for (auto i : this->dropDownLists)
	{
		i.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	//target->draw(this->background);
	this->renderGUI(*target);
	target->draw(this->mousePosText);
	target->draw(this->optionsText);
}


