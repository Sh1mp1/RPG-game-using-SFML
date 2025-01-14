#include "stdafx.h"
#include "State.h"



State::State(sf::RenderWindow* window, std::map <std::string, int>* supported_Keys, std::stack<State*>* states)
{
	this->window = window;
	this->quit = false;
	this->supportedKeys = supported_Keys;

	this->states = states;


}

State::~State()
{
	this->supportedKeys = nullptr;

	delete this->supportedKeys;
}

const bool& State::getQuit() const
{
	return this->quit;
}


void State::endState()
{
	this->quit = true;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}


