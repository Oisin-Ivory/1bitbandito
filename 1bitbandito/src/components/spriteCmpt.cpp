#include "spriteCmpt.hpp"
void spriteCmpt::Draw(sf::RenderWindow &window, float timeDelta)
{ 
    window.draw(m_sprite);
}

spriteCmpt::spriteCmpt()
{
}

void spriteCmpt::Update(float timeDelta) {

}

void spriteCmpt::setScale(Map& map) {
    m_sprite.setScale(map.textureScale, map.textureScale);
}
///Use texture to set our sprite
void spriteCmpt::setTexture(const sf::Texture& texture)
{
    m_sprite.setTexture(texture);
}

///set position
void spriteCmpt::setPosition(sf::Vector2f position)
{
    m_sprite.setPosition(position);

}
