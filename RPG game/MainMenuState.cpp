#include "stdafx.h"
#include "MainMenuState.h"



void MainMenuState::initKeybinds()
{
	std::ifstream ifs("config/mainmenustate_keybinds.ini");

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

MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data)
{
	this->initBackground();
	this->initFont();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{

	for (auto i : this->buttons)
	{
		delete i.second;
	}
}

void MainMenuState::initFont()
{
	
	this->mousePosText.setFont(*this->stateData->font);


	this->mousePosText.setOutlineColor(sf::Color::Black);
	this->mousePosText.setOutlineThickness(1.f);
	this->mousePosText.setString("START");
	this->mousePosText.setPosition(sf::Vector2f(0.f , 0.f));
	this->mousePosText.setCharacterSize(15);
}

void MainMenuState::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("Textures/background.jpg"))
	{
		std::cout << "ERROR::MAINMENUSTATE::COULDNT LOAD BACKGROUND" << '\n';
	}
	this->background.setTexture(this->backgroundTexture);

	float scale_x = static_cast<float>(this->stateData->window->getSize().x) / this->backgroundTexture.getSize().x;
	float scale_y = static_cast<float>(this->stateData->window->getSize().y) / this->backgroundTexture.getSize().y;


	this->background.setScale(sf::Vector2f(scale_x, scale_y));

	this->backgroundFade.setSize(sf::Vector2f(560.f, 1080.f));
	this->backgroundFade.setFillColor(sf::Color(20, 20, 20, 150));
}

void MainMenuState::initButtons()
{
	this->buttons.emplace("GAME", new gui::Button(sf::Vector2f(280.f, 510.f), this->stateData->font, "GAME",
						sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40));

	this->buttons.emplace("SETTINGS", new gui::Button(sf::Vector2f(280.f, 600.f), this->stateData->font, "SETTINGS",
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40));

	this->buttons.emplace("EDITOR", new gui::Button(sf::Vector2f(280.f, 700), this->stateData->font, "EDITOR",
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40));

	this->buttons.emplace("EXIT", new gui::Button(sf::Vector2f(280.f, 800.f), this->stateData->font, "EXIT",
						sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40));
}


void MainMenuState::updateInput(const float& dt)
{
}

void MainMenuState::updateButtons()
{

	//Updates all button states and changes their color with mouse interaction
	for (auto i : this->buttons)
	{
		i.second->update(this->mousePosWindow);
	}

	//Push new gamestate to stack when "GAME" or a PLAY button is pressed
	if (this->buttons.at("GAME")->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}

	//Exits when "EXIT" button is pressed
	if (this->buttons.at("EXIT")->isPressed())
	{
		this->endState();;
	}

	if (this->buttons.at("EDITOR")->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	if (this->buttons.at("SETTINGS")->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}
}

void MainMenuState::updateText()
{
	this->mousePosText.setPosition(sf::Vector2f(this->mousePosView.x + 10.f, this->mousePosView.y + 10.f));

	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	this->mousePosText.setString(ss.str());
	

}

void MainMenuState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePositions();
	this->updateText();
	this->updateButtons();


}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto i : this->buttons)
	{
		i.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = window;
	}
	target->draw(this->background);
	target->draw(this->backgroundFade);
	this->renderButtons(*target);
	target->draw(this->mousePosText);

}
