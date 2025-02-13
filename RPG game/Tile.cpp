#include "stdafx.h"
#include "Tile.h"


void Tile::initShape(sf::Vector2u grid_pos, float gridSize)
{
	this->shape.setSize(sf::Vector2f(gridSize, gridSize));
	this->shape.setFillColor(sf::Color(255, 255, 255, 255));

	this->shape.setPosition(static_cast<sf::Vector2f>(grid_pos) * gridSize);
}

void Tile::initTexture(const sf::Texture& texture, const sf::IntRect& texture_rect)
{
	this->textureRect = texture_rect;

	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_rect);
}

Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(sf::Vector2u grid_pos, float gridSize, const sf::Texture& texture, const sf::IntRect& texture_rect, const short type, const bool collision)
	:type(type), collision(collision)
{
	this->initShape(grid_pos, gridSize);
	this->initTexture(texture, texture_rect);

}

Tile::~Tile()
{
}

const bool Tile::hasCollision() const
{
	return this->collision;
}

const std::string Tile::getString() const
{
	std::stringstream ss;
	ss << this->textureRect.left << " " << this->textureRect.top << " " <<
		this->collision << " " << this->type;

	return ss.str();
}

const sf::Vector2f Tile::getPosition() const
{
	return this->shape.getPosition();
}

const sf::Vector2f Tile::getTextureRectPosition() const
{
	return sf::Vector2f(static_cast<float>(this->textureRect.left), static_cast<float>(this->textureRect.top));
}

const sf::FloatRect Tile::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const sf::IntRect& Tile::getTextureRect() const
{
	return this->textureRect;
}

//Functions

const bool Tile::intersects(const sf::FloatRect& bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds);
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}


