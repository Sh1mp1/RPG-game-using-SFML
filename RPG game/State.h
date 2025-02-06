#pragma once
#include "Entity.h"
#include "PauseMenu.h"
#include "GraphicsSettings.h"

class Entity;
class PauseMenu;
class GraphicsSettings;
class State;

class StateData
{
public:
	StateData()	{}

	//Variables
	float gridSize;
	sf::RenderWindow* window;
	std::map <std::string, int>* supportedKeys;
	std::stack<State*>* states;
	GraphicsSettings* gfxSettings;
	sf::Font* font;
	float* mouseWheelDelta;
};

class State
{
protected:
	GraphicsSettings& gfxSettings;

	StateData* stateData;

	sf::RenderWindow* window;
	
	std::stack<State*>* states;

	std::map <std::string, int>* supportedKeys;
	std::map <std::string, int> keybinds;

	bool quit;
	bool paused;

	float keyTime;
	float keyTimeMax;

	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;
	sf::Vector2u mousePosGridWindow;

	//Resources
	std::map <std::string, sf::Texture*> textures;

	//Functions
	virtual void initKeybinds() = 0;

public:
	State(StateData* state_data);
	virtual ~State();


	//Accessor
	const bool& getQuit() const;
	const bool& getKeyTime();

	//Functions
	virtual void endState();
	virtual void updateMousePositions(const sf::View* view = nullptr);
	virtual void updateKeyTime(const float& dt);


	void pauseState();
	void unPauseState();

	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

