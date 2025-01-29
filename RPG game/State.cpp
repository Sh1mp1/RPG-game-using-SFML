#include "stdafx.h"
#include "State.h"



State::State(StateData* state_data)
	:gfxSettings(*state_data->gfxSettings), keyTime(0.f), keyTimeMax(2.f)
{
	this->stateData = state_data;

	this->window = state_data->window;
	this->quit = false;
	this->supportedKeys = state_data->supportedKeys;

	this->states = state_data->states;;

	this->gridSize = state_data->gridSize;

	this->paused = false;

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

const bool& State::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)	//Returns true if keytime is greater than keytimemax;
	{
		this->keyTime = 0.f;
		
		return true;
	}
	return false;
}



void State::endState()
{
	this->quit = true;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->stateData->window->mapPixelToCoords(this->mousePosWindow);
	this->mousePosGrid = sf::Vector2u(static_cast<unsigned>(this->mousePosView.x / this->gridSize), 
									  static_cast<unsigned>(this->mousePosView.y / this->gridSize));
}

void State::updateKeyTime(const float& dt)
{
	if (this->keyTime <= this->keyTimeMax)
	{
		this->keyTime += dt * 35.f;
	}
}

void State::pauseState()
{
	this->paused = true;
}

void State::unPauseState()
{
	this->paused = false;
}