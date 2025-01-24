#include "stdafx.h"
#include "GUI.h"

void gui::Button::initShape(sf::Vector2f& centrePos, sf::Vector2f& size)
{
	//sf::FloatRect textBounds = this->text.getGlobalBounds();
	//sf::Vector2f size(textBounds.width + 50.f, textBounds.height + 20.f);

	this->shape.setSize(size);

	sf::Vector2f pos(centrePos.x - (size.x / 2.f), centrePos.y - (size.y / 3.f));

	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color::White);

	this->shape.setPosition(pos);
}

gui::Button::Button(sf::Vector2f centrePos, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, const unsigned int characterSize)
{
	this->font = font;

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setOutlineColor(sf::Color::Black);
	this->text.setOutlineThickness(1.f);
	this->text.setCharacterSize(characterSize);

	

	this->text.setPosition(sf::Vector2f(centrePos.x - (this->text.getGlobalBounds().width / 2.f), centrePos.y - (this->text.getGlobalBounds().height / 2.f)));

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	//this->initShape(centrePos);

}

gui::Button::Button(sf::Vector2f centrePos, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, const unsigned int characterSize, sf::Vector2f rectangleSize)
{
	this->font = font;

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setOutlineColor(sf::Color::Black);
	this->text.setOutlineThickness(1.f);
	this->text.setCharacterSize(characterSize);


	this->text.setPosition(sf::Vector2f(centrePos.x - (this->text.getGlobalBounds().width / 2.f), centrePos.y - (this->text.getGlobalBounds().height / 2.f)));

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->initShape(centrePos, rectangleSize);
}

gui::Button::~Button()
{
}

const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}
	
	return false;
}

const sf::FloatRect& gui::Button::getBounds() const
{
	return this->text.getGlobalBounds();
}

const sf::FloatRect& gui::Button::getRectangleBound() const
{
	return this->shape.getGlobalBounds();
}

const std::string gui::Button::getString() const
{
	return this->text.getString();
}

void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::centreText(const sf::Vector2f& centrePos)
{
	sf::FloatRect bounds(this->text.getGlobalBounds());

	this->text.setPosition(sf::Vector2f(centrePos.x - (bounds.width / 2.f), centrePos.y - (bounds.height / 2.f)));
}


void gui::Button::update(sf::Vector2f mousePos)
{
	this->buttonState = BTN_IDLE;

	if (this->text.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->text.setFillColor(this->idleColor);
		this->shape.setFillColor(sf::Color(100, 100, 100, 100));
		break;

	case BTN_HOVER:
		this->text.setFillColor(this->hoverColor);
		this->shape.setFillColor(sf::Color(150, 150, 150, 100));
		break;

	case BTN_ACTIVE:
		this->text.setFillColor(this->activeColor);
		this->shape.setFillColor(sf::Color(200, 200, 200, 100));
		break;

	default:
		this->text.setFillColor(sf::Color::Red);
		break;
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->text);
}

void gui::Button::render(sf::RenderTarget& target, const bool& drawShape)
{
	if (drawShape)
	{
		target.draw(this->shape);
	}
	target.draw(this->text);
}



/*
DROP DOWN LIST -----------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/



gui::DropDownList::DropDownList(sf::Vector2f pos,sf::Font& font, std::vector<std::string> list, unsigned int defaultIndex)
	:font(font), showList(false), isMousePressed(false), centrePos(pos)
{
	this->font = font;

	sf::Text active_element_text(list.at(defaultIndex), this->font, 40);

	sf::Vector2f sizeOffset(10.f, 30.f);

	this->activeElement = new gui::Button(pos, &this->font, list.at(defaultIndex),
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40, active_element_text.getGlobalBounds().getSize() + sizeOffset);	

	sf::FloatRect bounds = this->activeElement->getRectangleBound();

	float height = bounds.height + 0.f;
	
	

	sf::Vector2f size(active_element_text.getGlobalBounds().width + sizeOffset.x, active_element_text.getGlobalBounds().height + sizeOffset.y);


	for (int i = 0; i < list.size(); ++i)
	{
		
		this->list.push_back(new Button(sf::Vector2f(bounds.left + (bounds.width / 2.f), bounds.top + (height * i) + (height + 25.f)), &this->font, list[i],
			sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40, size));	
	}	

	this->list.push_back(this->activeElement);
}

gui::DropDownList::~DropDownList()
{
	for (auto& i : this->list)
	{
		delete i;
	}	
}

void gui::DropDownList::update(const sf::Vector2f& mousePos)
{
	this->activeElement->update(mousePos);

	if (this->activeElement->isPressed())
	{
		if (!this->isMousePressed)
		{
			this->showList = !this->showList;	//Toggles the visibility of list
			this->isMousePressed = true;
		}
	}
	else
	{
		this->isMousePressed = false;
	}

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->update(mousePos);
			if (i->isPressed() && i != this->activeElement)
			{
				this->activeElement->setText(i->getString());
				this->activeElement->centreText(this->centrePos);
				this->showList = false;
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target, true);
	
	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(target, true);
		}
	}
}
