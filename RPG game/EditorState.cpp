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

EditorState::EditorState(StateData* state_data)
	:State(state_data), pauseMenu(*this->window, *state_data->font), isEscapePressed(false)
{
	this->initBackground();
	this->initFont();
	//this->initButtons();
	this->initKeybinds();
	this->initPauseMenu();
	this->initTexturRect();
	this->initTileMap();	
	this->initGUI(); // For selectorRect
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
	this->mousePosText.setFont(*this->stateData->font);


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
	//this->buttons.emplace("GAME", new gui::Button(sf::Vector2f(380.f, 510.f), &this->font, "GAME",
	//	sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40));
	//
	//this->buttons.emplace("SETTINGS", new gui::Button(sf::Vector2f(350.f, 600.f), &this->font, "SETTINGS",
	//	sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40));
	//
	//this->buttons.emplace("EDITOR", new gui::Button(sf::Vector2f(350.f, 700), &this->font, "EDITOR",
	//	sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40));
	//
	//this->buttons.emplace("EXIT", new gui::Button(sf::Vector2f(400.f, 800.f), &this->font, "EXIT",
	//	sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40));
}

void EditorState::initGUI()
{
	this->selectorRect.setFillColor(sf::Color::Transparent);
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Red);

}

void EditorState::initPauseMenu()
{
	this->pauseMenu.addButton(sf::Vector2f(this->window->getSize().x / 2.f, 500.f), "RESUME");
	this->pauseMenu.addButton(sf::Vector2f(this->window->getSize().x / 2.f, 800.f), "EXIT");
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, static_cast<unsigned>(this->stateData->window->getSize().x / this->stateData->gridSize), 
														   static_cast<unsigned>(this->stateData->window->getSize().y / this->stateData->gridSize), 
		this->tileMapTexture);
}

void EditorState::initTexturRect()
{
	if (!this->tileMapTexture.loadFromFile("Textures/tilesheet.png"))
	{
		std::cout << "ERROR::EDITORSTATE::COULDNT LOAD TEXTURE" << '\n';
	}

	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->gridSize), static_cast<int>(this->gridSize));

	this->currentTexture.setSize(sf::Vector2f(20.f, 20.f));
	this->currentTexture.setTexture(&this->tileMapTexture);
	this->currentTexture.setTextureRect(this->textureRect);
}


void EditorState::updateMouseScroll(const float& dt)
{
	
}

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("close"))))
	{
		if (!this->isEscapePressed)
		{
			this->isEscapePressed = true;

			if (!this->paused)
			{
				this->pauseState();
			}
			else
			{
				this->unPauseState();
			}
		}
	}
	else
	{
		this->isEscapePressed = false;
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	
	//Add tile
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())	//Adds a tile to the tileMap
	{		
		this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
	}

	//Remove tile
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())	//Removes a tile from the tileMap
	{
		this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
	}

	//Change texture Rect

	if (*this->stateData->mouseWheelDelta != 0)
	{
		std::cout << static_cast<int>(*stateData->mouseWheelDelta) << '\n';
	}
	
}

void EditorState::updateTextureRect(float mouseScroll)
{
	//Todo update texture rect based on mouse wheel scroll_-----------------------------------------------------------------------------------------------------------------------------
}

void EditorState::updatePauseMenu()
{
	if (this->paused)
	{
		this->quit = this->pauseMenu.isPressed("EXIT");


		if (this->pauseMenu.isPressed("RESUME"))
		{
			this->unPauseState();
		}
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
		//this->quit = true;
	}
}

void EditorState::updateGUI()
{
	this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);

	this->currentTexture.setPosition(sf::Vector2f(this->mousePosView.x + 20.f, this->mousePosView.y));
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
	this->updateKeyTime(dt);
	//this->updateButtons();
	if (paused)
	{
		this->pauseMenu.update(this->mousePosView);
		this->updatePauseMenu();
	}
	else
	{
		this->updateGUI(); 
		this->updateMouseScroll(dt);
		this->updateEditorInput(dt);
		
	}

}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto i : this->buttons)
	{
		i.second->render(target);
	}
}

void EditorState::renderGUI(sf::RenderTarget& target)
{
	target.draw(this->selectorRect);
	target.draw(this->currentTexture);
}

void EditorState::render(sf::RenderTarget* target)
{
	
	if (!target)
	{
		target = window;
	}

	//target->draw(this->background);
	//this->renderButtons(target);
	this->tileMap->render(*target);

	if (this->paused)
	{
		this->pauseMenu.render(*target);
	}
	else
	{
		this->renderGUI(*target);
	}

	

	//std::cout << this->mouseWheelDelta << '\n';

	target->draw(this->mousePosText);
}
