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

	delete this->textureSelector;
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
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->textureSelector = new gui::TextureSelector(20.f, 20.f, 640.f, 576.f, &this->tileMapTexture, this->stateData->gridSize, *this->stateData->font, this->mousePosView);
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

	this->currentTextureGUI.setSize(sf::Vector2f(35.f, 35.f));
	this->currentTextureGUI.setTexture(&this->tileMapTexture);
	this->currentTextureGUI.setTextureRect(this->textureRect);
}


const bool EditorState::isValidPos(const sf::Vector2u mousePosGrid) const
{
	if ((mousePosGrid.x >= 3 && mousePosGrid.y >= 5) || (mousePosGrid.y == 4 && mousePosGrid.x >= 6))
	{
		return false;
	}
	return true;
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
		if (!this->textureSelector->getIsActive())
		{
			this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
		}
		else if (this->isValidPos(this->textureSelector->getGridPos()))
		{
			this->textureRect = this->textureSelector->getTextureRect();
		}
	}

	//Remove tile
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())	//Removes a tile from the tileMap
	{
		this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
	}

	////Change texture Rect
	//
	//if (*this->stateData->mouseWheelDelta != 0)
	//{
	//	//this->updateTextureRect();
	//	std::cout << this->textureRect.getPosition().x << " " << this->textureRect.getPosition().y << '\n';
	//}
	//
}

void EditorState::updateTextureRect()
{
	/*
	Updates the textureRect according to mouse wheel scroll
	
	mouseWheelDelta = -1 when mouse scrolls up
	mouseWheelDelta = 1 when mouse scrolls down
	*/

	//if (*this->stateData->mouseWheelDelta < 0)
	//{
	//	this->textureRect.top += this->textureRect.height;

	//	//Check if the textureRect has reached the very bottom of the tile sheet
	//	if (this->textureRect.top > 512)
	//	{
	//		//Reset the textureRect to the top(1st row) and go to the next column
	//		this->textureRect.top = 0.f;
	//		this->textureRect.left += this->textureRect.width;
	//	}

	//	else if (this->textureRect.top > 256 && this->textureRect.left >= 192)
	//	{
	//		//Reset the textureRect to the top(1st row) and go to the next column
	//		this->textureRect.top = 0.f;
	//		this->textureRect.left += this->textureRect.width;
	//	}
	//	
	//	else if (this->textureRect.top > 192 && this->textureRect.left >= 384)
	//	{
	//		//Reset the textureRect to the top(1st row) and go to the next column
	//		this->textureRect.top = 0.f;
	//		this->textureRect.left += this->textureRect.width;
	//	}

	//	//Check if the textureRect has reached the very last column
	//	if (this->textureRect.left >= 576)
	//	{
	//		//Reset the textureRect to the first column and first row
	//		this->textureRect.left = 0.f;
	//		this->textureRect.top = 0.f;
	//	}
	//}

	//else if (*this->stateData->mouseWheelDelta > 0)
	//{
	//	this->textureRect.top -= this->textureRect.height;

	//	if (this->textureRect.top < 0.f)
	//	{
	//		if (this->textureRect.left >= 384)
	//		{
	//			this->textureRect.left -= this->textureRect.width;
	//			this->textureRect.top = 192;
	//		}

	//		else if (this->textureRect.left >= 192)
	//		{
	//			this->textureRect.left -= this->textureRect.width;
	//			this->textureRect.top = 256;
	//		}

	//		else if (this->textureRect.left >= 0.f)
	//		{
	//			this->textureRect.left -= this->textureRect.width;
	//			this->textureRect.top = 512.f;
	//		}

	//		if (this->textureRect.left < 0.f)
	//		{
	//			this->textureRect.left = 576.f;
	//			this->textureRect.top = 192.f;
	//		}
	//	}
	//}
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
	if (!this->textureSelector->getIsActive())
	{
		this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
	}

	this->textureSelector->update(this->mousePosWindow);
}

void EditorState::updateCurrentTextureGUI()
{
	this->currentTextureGUI.setPosition(sf::Vector2f(this->mousePosView.x + 25.f, this->mousePosView.y - 25.f));
	this->currentTextureGUI.setTexture(&this->tileMapTexture);
	this->currentTextureGUI.setTextureRect(this->textureRect);	
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
		this->updateCurrentTextureGUI();
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
	if (!this->textureSelector->getIsActive())	//Draw the selector rect only when the mouse is outside the tileMap showing all the textures
	{
		target.draw(this->selectorRect);
	}
	
	this->textureSelector->render(target);

	target.draw(this->currentTextureGUI);
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
