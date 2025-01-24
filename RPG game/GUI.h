#pragma once


enum buttonState { BTN_IDLE = 0 , BTN_HOVER, BTN_ACTIVE };

namespace gui
{
	class Button
	{
	private:
		short unsigned buttonState;

		sf::RectangleShape shape;

		sf::Font* font;
		sf::Text text;


		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		void initShape(sf::Vector2f& centrePos);
	public:
		Button(sf::Vector2f pos, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, const unsigned int characterSize);
		~Button();

		//Accessors
		const bool isPressed() const;
		const sf::FloatRect& getBounds() const;
		const sf::FloatRect& getRectangleBound() const;
		const std::string getString() const;

		//Modifiers
		void setText(const std::string text);

		//Functions
		void update(sf::Vector2f mousePos);
		void render(sf::RenderTarget& target);
		void render(sf::RenderTarget& target, const bool& drawShape);
	};

	class DropDownList
	{
	private:
		sf::Font& font;
		gui::Button* activeElement;

		std::vector<gui::Button*> list;
		bool showList;
		bool isMousePressed;

	public:
		DropDownList(sf::Font& font, std::vector<std::string> list, unsigned int defaultIndex = 0);
		~DropDownList();

		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};
}

