#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(unsigned level)
{
	this->level = level;
	this->exp = 0;

	this->expNext = static_cast<unsigned>((50 / 3) * (pow(this->level + 1, 3) - pow(this->level + 1, 2) + ((this->level + 1) * 17) - 12));
	
	this->strength = 1;
	this->vitality = 1;

	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;



	this->hp = 1;
	this->hpMax = 100;
	this->damage = 1;
	this->damageMax = 1;
	this->damageMin = 1;
	this->accuracy = 1;
	this->defence = 1;
	this->luck = 1;

	this->updateLevel();
	this->updateStats(true);
}

AttributeComponent::~AttributeComponent()
{

}

const std::string AttributeComponent::debugPrint()
{
	std::stringstream ss;

	ss << "LEVEL: " << this->level << '\n'
		<< "HP: " << this->hp << '\n'
		<< "HPMAX: " << this->hpMax << '\n'
		<< "EXP: " << this->exp << '\n'
		<< "EXPNext: " << this->expNext << '\n'
		<< "STRNEGHT: " << this->strength << '\n'
		<< "VITALITY: " << this->vitality << '\n'
		<< "DEXTERITY: " << this->dexterity << '\n'
		<< "ACCURACY: " << this->accuracy << '\n'
		<< "AGILITY: " << this->agility << '\n'
		<< "DAMAGE: " << this->damage << '\n'
		<< "DAMAGE_MAX: " << this->damageMax << '\n'
		<< "DAMAGE_MIN: " << this->damageMin << '\n'
		<< "DEFENCE: " << this->defence << '\n'
		<< "INTELLIGENCE: " << this->intelligence << '\n'
		<< "LUCK: " << this->luck << '\n';

	return ss.str();
}

void AttributeComponent::gainExp(const int exp)
{
	this->exp += exp;

	this->updateLevel();
}

void AttributeComponent::loseExp(const int exp)
{
	this->exp -= exp;
	if (this->exp < 0)
	{
		this->exp = 0;
	}
	this->updateLevel();
}

void AttributeComponent::takeDamage(const int damage)
{
	this->hp -= damage;

	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void AttributeComponent::gainHp(const int hp)
{
	this->hp += hp;

	if (this->hp > this->hpMax)
	{
		this->hp = this->hpMax;
	}

	this->updateLevel();
}

//Functions
void AttributeComponent::updateLevel()
{
	while (this->exp >= this->expNext)
	{
		++this->level;
		this->exp -= this->expNext;

		this->expNext = static_cast<unsigned>((50 / 3) * (pow(this->level, 3) - pow(this->level, 2) + (this->level * 17) - 12));
	}
}

void AttributeComponent::update()
{
	this->updateLevel();
}

void AttributeComponent::updateStats(const bool reset)
{
	this->hpMax		= this->vitality * 5 + this->vitality + this->strength + this->intelligence / 5;
	this->damageMax = this->strength * 2 + this->strength / 2 + this->intelligence / 5;
	this->damageMin = this->strength * 2 + this->strength / 4 + this->intelligence / 5;

	this->accuracy	= this->dexterity * 4 + this->dexterity / 3 + this->intelligence / 5;

	this->defence	= this->agility * 2 + this->agility / 4 + this->intelligence / 5;

	this->luck		= this->intelligence * 2 + this->intelligence / 5;

	if (reset)
	{
		this->hp = this->hpMax;
	}
}
