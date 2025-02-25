#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	if (!this->font.loadFromFile("Font/joystix monospace.otf"))
	{
		std::cout << "ERROR::PLAYERGUI::COULDNT LOAD FONT" << '\n';
	}
}

void PlayerGUI::initHpBar()
{	
	this->hpBarBack.setSize(sf::Vector2f(this->p2pX(0.13f), this->p2pY(0.037f)));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setOutlineThickness(1.f);
	this->hpBarBack.setOutlineColor(sf::Color::White);
	this->hpBarBack.setPosition(this->p2pX(0.0104f), this->p2pY(0.13f));

	this->hpBarInner.setSize(sf::Vector2f(this->p2pX(0.13f), this->p2pY(0.037f)));
	this->hpBarInner.setFillColor(sf::Color::Red);	
	this->hpBarInner.setPosition(this->p2pX(0.0104f), this->p2pY(0.13f));

	this->hpText.setFont(this->font);
	this->hpText.setCharacterSize(static_cast<unsigned>(this->p2pX(0.015f)));
	this->hpText.setPosition(sf::Vector2f(this->p2pX(0.02f), this->p2pY(0.13f)));
	this->hpText.setOutlineThickness(1.f);
	this->hpText.setOutlineColor(sf::Color::Black);
	this->hpText.setString(std::to_string(this->player->getAttributeComponent()->hp) + "/" + std::to_string(this->player->getAttributeComponent()->hpMax));
}

void PlayerGUI::initExpBar()
{
	this->expBarBack.setSize(sf::Vector2f(this->p2pX(0.13f), this->p2pY(0.037f)));
	this->expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->expBarBack.setOutlineThickness(1.f);
	this->expBarBack.setOutlineColor(sf::Color::White);
	this->expBarBack.setPosition(this->p2pX(0.0104f), this->p2pY(0.078f));

	this->expBarInner.setSize(sf::Vector2f(0.f, this->p2pY(0.037f)));
	this->expBarInner.setFillColor(sf::Color::Blue);
	this->expBarInner.setPosition(this->p2pX(0.0104f), this->p2pY(0.078f));

	this->expText.setFont(this->font);
	this->expText.setCharacterSize(static_cast<unsigned>(this->p2pX(0.015f)));
	this->expText.setPosition(sf::Vector2f(this->p2pX(0.02f), this->p2pY(0.078f)));
	this->expText.setOutlineThickness(1.f);
	this->expText.setOutlineColor(sf::Color::Black);
	this->expText.setString(std::to_string(this->player->getAttributeComponent()->exp) + "/" + std::to_string(this->player->getAttributeComponent()->expNext));
}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& video_mode)
	:player(player), videoMode(video_mode)
{
	this->initFont();
	this->initHpBar();
	this->initExpBar();
}

PlayerGUI::~PlayerGUI()
{
}

//Functions
void PlayerGUI::update(const float& dt)
{
	////TODO call updateHpBar whenever player takes damage
	//
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	//{
	//	this->player->getAttributeComponent()->takeDamage(1);
	//}
	//
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	//{
	//	this->player->getAttributeComponent()->gainExp(1);
	//}
	//
	//this->updateHpBar();
	//this->updateExpBar();
}

const float PlayerGUI::p2pX(const float modifier)
{
	return modifier * this->videoMode.width;
}

const float PlayerGUI::p2pY(const float modifier)
{
	return modifier * this->videoMode.height;
}

void PlayerGUI::updateHpBar()
{
	float percentage = static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);
	this->hpBarInner.setSize(sf::Vector2f(percentage * this->hpBarBack.getSize().x, this->hpBarInner.getSize().y));
	this->hpText.setString(std::to_string(this->player->getAttributeComponent()->hp) + "/" + std::to_string(this->player->getAttributeComponent()->hpMax));
}

void PlayerGUI::updateExpBar()
{
	float percentage = static_cast<float>(this->player->getAttributeComponent()->exp) / static_cast<float>(this->player->getAttributeComponent()->expNext);
	this->expBarInner.setSize(sf::Vector2f(percentage * this->expBarBack.getSize().x, this->expBarInner.getSize().y));
	this->expText.setString(std::to_string(this->player->getAttributeComponent()->exp) + "/" + std::to_string(this->player->getAttributeComponent()->expNext));
}

void PlayerGUI::renderHpBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->hpText);
}

void PlayerGUI::renderExpBar(sf::RenderTarget& target)
{
	target.draw(this->expBarBack);
	target.draw(this->expBarInner);
	target.draw(this->expText);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderHpBar(target);
	this->renderExpBar(target);
}
