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
	:buttonState(0), id(0)
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

gui::Button::Button(sf::Vector2f centrePos, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, const unsigned int characterSize,
	sf::Vector2f rectangleSize, short unsigned id)
	:id(id)
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

const sf::FloatRect gui::Button::getBounds() const
{
	return this->text.getGlobalBounds();
}

const sf::FloatRect gui::Button::getRectangleBounds() const
{
	return this->shape.getGlobalBounds();
}

const std::string gui::Button::getString() const
{
	return this->text.getString();
}

const short unsigned gui::Button::getID() const
{
	return this->id;
}

void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::centreText(const sf::Vector2f& centrePos)
{
	sf::FloatRect bounds(this->text.getGlobalBounds());

	this->text.setPosition(sf::Vector2f(centrePos.x - (bounds.width / 2.f), centrePos.y - (bounds.height / 2.f)));
	this->shape.setPosition(sf::Vector2f(centrePos.x - (this->shape.getGlobalBounds().width / 2.f), centrePos.y - (this->shape.getGlobalBounds().height / 2.f)));
}


void gui::Button::update(sf::Vector2i mousePosWindow)
{
	this->buttonState = BTN_IDLE;

	if (this->text.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
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
DROP DOWN LIST===================================================================================================================================================================
*/



void gui::DropDownList::initList(sf::Vector2f pos, std::vector<std::string> list, unsigned int defaultIndex)
{

	sf::Text active_element_text(list.at(defaultIndex), this->font, 40);
	sf::Vector2f sizeOffset(10.f, 30.f);

	this->activeElement = new gui::Button(pos, &this->font, list.at(defaultIndex),
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40, active_element_text.getGlobalBounds().getSize() + sizeOffset);

	sf::FloatRect bounds = this->activeElement->getRectangleBounds();

	sf::Vector2f size(active_element_text.getGlobalBounds().width + sizeOffset.x, active_element_text.getGlobalBounds().height + sizeOffset.y);


	for (int i = 0; i < list.size(); ++i)
	{
		this->list.push_back(new Button(sf::Vector2f(bounds.left + (bounds.width / 2.f), bounds.top + (bounds.height * i) + (bounds.height + 25.f)), &this->font, list[i],
			sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 40, size, i));
	}

	this->list.push_back(this->activeElement);
}

gui::DropDownList::DropDownList(sf::Vector2f pos,sf::Font& font, std::vector<std::string> list, unsigned int defaultIndex)
	:font(font), showList(false), isMousePressed(false), centrePos(pos)
{
	this->initList(pos, list, defaultIndex);	//Initializes the drop down list and the active element
}

gui::DropDownList::~DropDownList()
{
	for (auto& i : this->list)
	{
		delete i;
	}	
}

const short unsigned gui::DropDownList::getActiveElementID() const
{
	for (int i = 0; i < this->list.size(); ++i)
	{
		if (this->activeElement->getString() == this->list[i]->getString())
		{
			return i;
		}
	}
	return 1;
}

void gui::DropDownList::update(const sf::Vector2i& mousePosWindow)
{
	this->activeElement->update(mousePosWindow);

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
			i->update(mousePosWindow);
			if (i->isPressed() && i != this->activeElement)
			{
				this->activeElement->setText(i->getString());
				this->activeElement->centreText(this->centrePos);	//Replaces the active element to the one that is pressed and centres the text
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

//Texture selector==============================================================================================================================================

void gui::TextureSelector::initRect(float x, float y, float width, float height)
{
	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));
}

void gui::TextureSelector::initSprite(float x, float y, sf::Texture* texture_sheet)
{
	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x, y);	
}

void gui::TextureSelector::initSheet()
{
	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
	}

	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->sheet.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));
	}
}

void gui::TextureSelector::initSelectorRect(float x, float y)
{
	this->selectorRect.setPosition(x, y);
	this->selectorRect.setSize(sf::Vector2f(this->gridSize, this->gridSize));
	this->selectorRect.setFillColor(sf::Color::Transparent);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Red);
}

//Constructor & Destructor

void gui::TextureSelector::initButton()
{
	sf::Vector2f pos(this->bounds.getSize().x - 50.f, this->bounds.getSize().y - 50.f);
	this->hideButton = new gui::Button(pos, &this->font, "HIDE", sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(150, 150, 150), 20,
										sf::Vector2f(70.f, 30.f));
}

gui::TextureSelector::TextureSelector(float x, float y, float width, float height, sf::Texture* texture_sheet, float grid_size, sf::Font& font, sf::Vector2i& mouse_pos_window)
	:isActive(false), gridSize(grid_size), isHidden(false), font(font), mousePosWindow(mouse_pos_window), isButtonPressed(false)
{
	this->initRect(x, y, width, height);

	this->initSprite(x, y, texture_sheet);

	this->initSheet();

	this->initSelectorRect(x, y);

	this->textureRect = sf::IntRect(0, 0, static_cast<int>(gridSize), static_cast<int>(gridSize));

	this->initButton();
}

gui::TextureSelector::~TextureSelector()
{
}

//Functions
const bool& gui::TextureSelector::getIsActive() const
{
	return this->isActive;
}

const sf::Vector2u& gui::TextureSelector::getGridPos() const
{
	return this->mousePosGrid;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

const bool gui::TextureSelector::isHideButtonPressed() const
{
	return this->hideButton->isPressed();
}

//Functions

void gui::TextureSelector::updateButton()
{
	this->hideButton->update(this->mousePosWindow);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!this->isButtonPressed)
		{
			this->isButtonPressed = true;
			if (this->hideButton->isPressed())
			{
				if (this->isHidden)
				{
					this->isHidden = false;
					this->hideButton->setText("HIDE");
					this->hideButton->centreText(sf::Vector2f(this->bounds.getSize().x - 50.f, this->bounds.getSize().y - 50.f));
				}

				else
				{
					this->isHidden = true;
					this->hideButton->setText("SHOW");
					this->hideButton->centreText(sf::Vector2f(this->bounds.getPosition().x + 50.f, this->bounds.getPosition().y + 50.f));
					this->isActive = true;
				}
			}
		}
	}
	else
	{
		this->isButtonPressed = false;
	}
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow)
{
	this->updateButton();
	if (!this->isHidden)
	{
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)) || this->hideButton->getBounds().contains(static_cast<sf::Vector2f>(this->mousePosWindow)))
		{
			this->isActive = true;
			//std::cout << "TRUE" << '\n';
		}
		else
		{
			this->isActive = false;
			//std::cout << "FALSE" << '\n';
		}

		if (this->isActive)
		{
			this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);

			this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

			this->selectorRect.setPosition(this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize);

			this->textureRect.left = static_cast<int>(this->mousePosGrid.x * this->gridSize);
			this->textureRect.top = static_cast<int>(this->mousePosGrid.y * this->gridSize);
		}
	}
	else
	{
		if (this->hideButton->getBounds().contains(static_cast<sf::Vector2f>(this->mousePosWindow)))
		{
			this->isActive = true;
		}
		else
		{
			this->isActive = false;
		}
	}
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
	if (!this->isHidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);

		if (this->isActive)
		{
			target.draw(this->selectorRect);
		}
	}

	this->hideButton->render(target, true);
	//std::cout << this->hideButton->getBounds().left << this->hideButton->getBounds().top << '\n';

	//std::cout << this->mousePosGrid.x << " " << this->mousePosGrid.y << '\n';
}
