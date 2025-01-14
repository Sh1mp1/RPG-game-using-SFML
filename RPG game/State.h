#pragma once
#include "Entity.h"

class State
{
protected:

	sf::RenderWindow* window;
	
	std::stack<State*>* states;

	std::map <std::string, int>* supportedKeys;
	std::map <std::string, int> keybinds;

	bool quit;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	std::map <std::string, sf::Texture*> textures;

	//Functions
	virtual void initKeybinds() = 0;

public:
	State(sf::RenderWindow* window, std::map <std::string, int>* supported_Keys, std::stack<State*>* states);
	virtual ~State();


	//Accessor
	const bool& getQuit() const;

	//Functions
	virtual void endState();
	virtual void updateMousePositions();

	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

