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

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initButtons();
	this->initBackground();
	this->initFont();
	this->initDropDownList();
}

SettingsState::~SettingsState()
{
	for (auto& i : this->buttons)
	{
		delete i.second;
	}

	if(this->dropDownList)
		delete this->dropDownList;
}


void SettingsState::initFont()
{
	if (!this->font.loadFromFile("Font/Roboto-Black.ttf"))
	{
		std::cout << "ERROR::SETTINGSSTATE::COULDNT LOAD FONT" << '\n';
	}
	this->mousePosText.setFont(this->font);


	this->mousePosText.setOutlineColor(sf::Color::Black);
	this->mousePosText.setOutlineThickness(1.f);
	this->mousePosText.setString("START");
	this->mousePosText.setPosition(sf::Vector2f(0.f, 0.f));
	this->mousePosText.setCharacterSize(15);

	
	this->optionsText.setFont(this->font);

	this->optionsText.setPosition(sf::Vector2f(400.f, 480.f));
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

	this->buttons.emplace("EXIT", new gui::Button(sf::Vector2f(this->window->getSize().x / 2.f, 800.f), &this->font, "EXIT",
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40.f));
}

void SettingsState::initDropDownList()
{
	std::vector<std::string> dropDownText;
	dropDownText.push_back("1920 X 1080");
	dropDownText.push_back("1366 X 768");
	dropDownText.push_back("1280 X 720");
	dropDownText.push_back("800 X 600");

	this->dropDownList = new gui::DropDownList(sf::Vector2f(1000.f, 500.f), this->font, dropDownText, 0);
}


void SettingsState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("close"))))
	{
		this->quit = true;
	}
}

void SettingsState::updateButtons()
{

	//Updates all button states and changes their color with mouse interaction
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}
	
	
	//Exits when "EXIT" button is pressed
	if (this->buttons.at("EXIT")->isPressed())
	{
		this->quit = true;
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
}

void SettingsState::updateDropDownList()
{
	this->dropDownList->update(this->mousePosView);	
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

	this->dropDownList->render(target);
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


