#pragma once


enum buttonState { BTN_IDLE = 0 , BTN_HOVER, BTN_ACTIVE };

class Button
{
private:
	short unsigned buttonState;

	sf::Font* font;
	sf::Text text;


	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;


public:
	Button(sf::Vector2f pos, sf::Font* font, std::string text , sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, const unsigned int characterSize);
	~Button();

	//Accessors
	const bool isPressed() const;
	const sf::FloatRect& getBounds() const;

	//Functions
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget& target);
};

