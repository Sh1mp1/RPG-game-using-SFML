#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	if (!this->font.loadFromFile("Font/Roboto-Black.ttf"))
	{
		std::cout << "ERROR::PLAYERGUI::COULDNT LOAD FONT" << '\n';
	}
}

void PlayerGUI::initHpBar()
{
	
	this->hpBarBack.setSize(sf::Vector2f(250.f, 40.f));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setOutlineThickness(1.f);
	this->hpBarBack.setOutlineColor(sf::Color::White);
	this->hpBarBack.setPosition(20.f, 20.f);

	this->hpBarInner.setSize(sf::Vector2f(250.f, 40.f));
	this->hpBarInner.setFillColor(sf::Color::Red);	
	this->hpBarInner.setPosition(20.f, 20.f);


}

PlayerGUI::PlayerGUI(Player* player)
	:player(player)
{
	this->initFont();
	this->initHpBar();
}

PlayerGUI::~PlayerGUI()
{
}

//Functions
void PlayerGUI::update(const float& dt)
{
}

void PlayerGUI::updateHpBar()
{
	float percentage = static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);
	this->hpBarInner.setSize(sf::Vector2f(percentage * this->hpBarBack.getSize().x, this->hpBarInner.getSize().y));
}

void PlayerGUI::renderHpBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderHpBar(target);
}
