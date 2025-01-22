#pragma once
#include "Entity.h"
#include "Bullet.h"


class Player:																								  
	public Entity																							  
{																											  
private:																									  
																											  
	sf::Font font;																							  
	sf::Text text;																							  
																											  
																											  
	//Initializer functions																					  
	void initVariables();																					  
	void initComponents(sf::Texture& texture_sheet);														  
	void initText();																						  
																											  
public:																										  
	Player(const float x, const float y, sf::Texture& texture_sheet);										  
	~Player();																								  
																											  
	void updateText();																						  
	void updateMovement(const float& dt, sf::Vector2f dir);													  
	void updateInput();																						  
	void updateAnimation(const float& dt);																	  
	void update(const float& dt);																			  
																											  
	void render(sf::RenderTarget& target);																	  
};																											  
																											  
																											  