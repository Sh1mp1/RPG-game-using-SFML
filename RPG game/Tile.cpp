#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
{
}

Tile::Tile(sf::Vector2f pos, float gridSize)
{
	this->shape.setSize(sf::Vector2f(gridSize, gridSize));
	this->shape.setFillColor(sf::Color(200, 200, 200, 100));
	this->shape.setPosition(sf::Vector2f(0.f, 0.f));

	this->shape.setPosition(pos);
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


