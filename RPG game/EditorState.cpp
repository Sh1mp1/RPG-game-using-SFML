#include "stdafx.h"
#include "EditorState.h"


void EditorState::initKeybinds()
{
	std::ifstream ifs("config/editorstate_keybinds.ini");

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

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initBackground();

	this->initFont();
	this->initButtons();
	this->initKeybinds();
	

}

EditorState::~EditorState()
{

	for (auto i : this->buttons)
	{
		delete i.second;
	}
}

void EditorState::initFont()
{
	if (!this->font.loadFromFile("Font/Roboto-Black.ttf"))
	{
		std::cout << "ERROR::MAINEMENUSTATE::COULDNT LOAD FONT" << '\n';
	}
	this->mousePosText.setFont(this->font);


	this->mousePosText.setOutlineColor(sf::Color::Black);
	this->mousePosText.setOutlineThickness(1.f);
	this->mousePosText.setString("START");
	this->mousePosText.setPosition(sf::Vector2f(0.f, 0.f));
	this->mousePosText.setCharacterSize(15);
}

void EditorState::initBackground()
{
}

void EditorState::initButtons()
{
	this->buttons.emplace("GAME", new gui::Button(sf::Vector2f(380.f, 510.f), &this->font, "GAME",
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40));

	this->buttons.emplace("SETTINGS", new gui::Button(sf::Vector2f(350.f, 600.f), &this->font, "SETTINGS",
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40));

	this->buttons.emplace("EDITOR", new gui::Button(sf::Vector2f(350.f, 700), &this->font, "EDITOR",
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40));

	this->buttons.emplace("EXIT", new gui::Button(sf::Vector2f(400.f, 800.f), &this->font, "EXIT",
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40));
}


void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("close"))))
	{
		this->quit = true;
	}
}

void EditorState::updateButtons()
{

	//Updates all button states and changes their color with mouse interaction
	for (auto i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

	//Push new gamestate to stack when "GAME" or a PLAY button is pressed
	if (this->buttons.at("GAME")->isPressed())
	{
		//this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	//Exits when "EXIT" button is pressed
	if (this->buttons.at("EXIT")->isPressed())
	{
		this->quit = true;
	}
}

void EditorState::updateText()
{
	this->mousePosText.setPosition(sf::Vector2f(this->mousePosView.x + 10.f, this->mousePosView.y + 10.f));

	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	this->mousePosText.setString(ss.str());


}

void EditorState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePositions();
	this->updateText();
	//this->updateButtons();


}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto i : this->buttons)
	{
		i.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = window;
	}
	//target->draw(this->background);
	//this->renderButtons(target);
	target->draw(this->mousePosText);

}
