#include "stdafx.h"
#include "Tile.h"


void Tile::initShape(sf::Vector2f pos, float gridSize)
{
	this->shape.setSize(sf::Vector2f(gridSize, gridSize));
	this->shape.setFillColor(sf::Color(255, 255, 255, 255));
	this->shape.setPosition(sf::Vector2f(0.f, 0.f));

	this->shape.setPosition(pos);
}

void Tile::initTexture(const sf::Texture& texture, const sf::IntRect& texture_rect)
{
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_rect);
}

Tile::Tile()
{
}

Tile::Tile(sf::Vector2f pos, float gridSize, const sf::Texture& texture, const sf::IntRect& texture_rect)
{
	this->initShape(pos, gridSize);
	this->initTexture(texture, texture_rect);
}

Tile::~Tile()
{
}

//Functions

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}


