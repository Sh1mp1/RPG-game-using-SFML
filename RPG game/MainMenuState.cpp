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

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
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
	if (!this->font.loadFromFile("Font/Roboto-Black.ttf"))
	{
		std::cout << "ERROR::MAINEMENUSTATE::COULDNT LOAD FONT" << '\n';
	}
	this->mousePosText.setFont(this->font);


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

	float scale_x = static_cast<float>(window->getSize().x) / this->backgroundTexture.getSize().x;
	float scale_y = static_cast<float>(window->getSize().y) / this->backgroundTexture.getSize().y;


	this->background.setScale(sf::Vector2f(scale_x, scale_y));
}

void MainMenuState::initButtons()
{
	this->buttons.emplace("GAME", new Button(sf::Vector2f(380.f, 510.f), &this->font, "GAME", 
						sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80)));

	this->buttons.emplace("SETTINGS", new Button(sf::Vector2f(350.f, 600.f), &this->font, "SETTINGS",
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80)));

	this->buttons.emplace("EDITOR", new Button(sf::Vector2f(350.f, 700), &this->font, "EDITOR",
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80)));

	this->buttons.emplace("EXIT", new Button(sf::Vector2f(400.f, 800.f), &this->font, "EXIT", 
						sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80)));
}


void MainMenuState::updateInput(const float& dt)
{
}

void MainMenuState::updateButtons()
{

	//Updates all button states and changes their color with mouse interaction
	for (auto i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

	//Push new gamestate to stack when "GAME" or a PLAY button is pressed
	if (this->buttons.at("GAME")->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	//Exits when "EXIT" button is pressed
	if (this->buttons.at("EXIT")->isPressed())
	{
		this->quit = true;
	}

	if (this->buttons.at("EDITOR")->isPressed())
	{
		this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
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

void MainMenuState::renderButtons(sf::RenderTarget* target)
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
	this->renderButtons(target);
	target->draw(this->mousePosText);

}
