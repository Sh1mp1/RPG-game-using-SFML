#pragma once
#include "WeaponComponent.h"

class Sword :
    public WeaponComponent
{
private:
    sf::Texture texture;


public:
    Sword(sf::Texture& texture, const sf::Vector2f position);
    ~Sword();


    void update(const float& dt, const sf::Vector2f& position, const float& angle);
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool show_hitbox = false);
};

