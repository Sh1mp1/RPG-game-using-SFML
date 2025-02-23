#pragma once

#include "Player.h"

class Player;


class PlayerGUI
{
private:
	Player* player;

	sf::VideoMode& videoMode;

	sf::Font font;

	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;
	sf::Text hpText;

	sf::RectangleShape expBarBack;
	sf::RectangleShape expBarInner;
	sf::Text expText;

	//Initialization functions
	void initFont();
	void initHpBar();
	void initExpBar();

public:
	PlayerGUI(Player* player, sf::VideoMode& video_mode);
	~PlayerGUI();
	
	//Functions
	void update(const float& dt);

	const float p2pX(const float modifier);
	const float p2pY(const float modifier);

	void updateHpBar();
	void updateExpBar();

	void renderHpBar(sf::RenderTarget& target);
	void renderExpBar(sf::RenderTarget& target);

	void render(sf::RenderTarget& target);
};

