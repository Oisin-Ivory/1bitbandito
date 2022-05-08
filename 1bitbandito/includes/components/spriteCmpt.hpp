#ifndef SPRITECMPT_H
#define SPRITECMPT_H

#include <iostream>
#include "Component.hpp"
#include "../Map.hpp"
class spriteCmpt : public Component
{
public:
    spriteCmpt();
    virtual void Update(float timeDelta);
    void Draw(sf::RenderWindow& window, float timeDelta);
    void setTexture(const sf::Texture& texture);
    void setPosition(sf::Vector2f position);
    void setScale(Map& map);

    private:
    sf::Sprite m_sprite;
    float m_timeDelta;
};

#endif