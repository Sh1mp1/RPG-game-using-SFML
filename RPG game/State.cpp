#include "stdafx.h"
#include "State.h"



State::State(StateData* state_data)
	:gfxSettings(*state_data->gfxSettings), keyTime(-2.f), keyTimeMax(4.f)
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

const bool State::getQuit() const
{
	return this->quit;
}

const bool State::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)	//Returns true if keytime is greater than keytimemax;
	{
		this->keyTime = 0.f;
		
		return true;
	}
	return false;
}


//Functions

const float State::p2pX(const float percent)
{
	return std::floor(static_cast<float>(this->stateData->gfxSettings->resolution.width) * (percent));
}

const float State::p2pY(const float percent)
{
	return std::floor(static_cast<float>(this->stateData->gfxSettings->resolution.height) * (percent));
}

const sf::Vector2i State::pos2GridPos(const sf::Vector2f position) const
{
	return sf::Vector2i(
		static_cast<int>(position.x) / static_cast<int>(this->stateData->gridSize),
		static_cast<int>(position.y) / static_cast<int>(this->stateData->gridSize)
	);

	//return sf::Vector2i(position.x / this->gridSize, position.y / this->gridSize);
}

void State::endState()
{
	this->quit = true;
}

void State::updateMousePositions(const sf::View* view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	
	if (view)
	{
		this->window->setView(*view);
	}

	this->mousePosView = this->stateData->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = sf::Vector2i(static_cast<int>(this->mousePosView.x / this->gridSize),
									  static_cast<int>(this->mousePosView.y / this->gridSize));
	this->mousePosGridWindow = sf::Vector2i(
		static_cast<int>(this->mousePosWindow.x / this->gridSize),
		static_cast<int>(this->mousePosWindow.y / this->gridSize));

	this->window->setView(this->window->getDefaultView());
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