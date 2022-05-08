
#include "AnimatedSpriteCmpt.hpp"
void AnimatedSpriteCmpt::Draw(sf::RenderWindow& window, float timeDelta)
{
    Update(timeDelta);
    window.draw(m_sprite);
}

AnimatedSpriteCmpt::AnimatedSpriteCmpt()
{
}

void AnimatedSpriteCmpt::AddTexture(sf::Texture& texture) {
    textures.push_back(texture);
}

void AnimatedSpriteCmpt::Update(float timeDelta) {
    timeSinceCycle += timeDelta;
    if (textures.size() == 0)
        return;
    //std::cout << timeSinceCycle << " < " << cycleTime << "timeSinceCycle < cycleTime" << std::endl;
    if (timeSinceCycle > cycleTime && textures.size() > 0) {
        setTexture(textures[currentTextureIndex]);
        currentTextureIndex++;
        if (currentTextureIndex >= textures.size())
            currentTextureIndex = 0;

        timeSinceCycle = 0;
    }
}

void AnimatedSpriteCmpt::setScale(Map& map) {
    m_sprite.setScale(map.textureScale, map.textureScale);

}
void AnimatedSpriteCmpt::setTexture(const sf::Texture& texture)
{
    m_sprite.setTexture(texture);
}

void AnimatedSpriteCmpt::setPosition(sf::Vector2f position)
{
    m_sprite.setPosition(position);

}