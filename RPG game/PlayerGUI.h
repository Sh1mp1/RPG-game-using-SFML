#pragma once

#include "Player.h"

class Player;


class PlayerGUI
{
private:
	Player* player;

	sf::Font font;

	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;

	//Initialization functions
	void initFont();
	void initHpBar();

public:
	PlayerGUI(Player* player);
	~PlayerGUI();
	
	//Functions
	void update(const float& dt);

	void updateHpBar();

	void renderHpBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

