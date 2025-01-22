#pragma once
#include "WeaponComponent.h"

class Gun :
    public WeaponComponent
{
private:



public:
    Gun();
    Gun(sf::Vector2f pos, sf::Texture& texture);
    ~Gun();


    void update(const float& dt, const sf::Vector2f& player_pos, const float& angle);
    void render(sf::RenderTarget& target);
};

