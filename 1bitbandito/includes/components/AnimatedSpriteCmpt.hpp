#ifndef ANIMATEDSPRITECMPT_H
#define ANIMATEDSPRITECMPT_H

#include "Component.hpp"
#include "../Map.hpp"
class AnimatedSpriteCmpt : public Component
{
public:
    AnimatedSpriteCmpt();
    virtual void Update(float timeDelta);
    void Draw(sf::RenderWindow& window, float timeDelta);
    void setTexture(const sf::Texture& texture);
    void setPosition(sf::Vector2f position);
    void setScale(Map& map);

    void AddTexture(sf::Texture& texture);
    std::vector<sf::Texture> textures;

    float cycleTime = 1;
    float timeSinceCycle = 10;

private:
    float textureScale = 1;
    int currentTextureIndex = 0;
    sf::Sprite m_sprite;
    float m_timeDelta;
};

#endif