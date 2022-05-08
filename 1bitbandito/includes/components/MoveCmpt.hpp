#ifndef MoveCmpt_hpp
#define MoveCmpt_hpp

#include "component.hpp"
#include "../Tile.hpp"
#include "../Map.hpp"
class MoveCmpt : public Component
{
  
public:
    MoveCmpt();
    MoveCmpt(int x, int y);
    MoveCmpt(bool projectileState, sf::Vector2f velocity);

    void setPositionTile(sf::Vector2f pos);
    sf::Vector2f getPosition();
    sf::Vector2f getTilePos();
    void setPosition(Map& map);
    void setPosition(sf::Vector2f pos);
    bool updatePosition(sf::Vector2f pos, Map& map);
    

    sf::Vector2f m_velocity;
    bool isProjectile = false;
    bool isMoving = false;
private:
    sf::Vector2f m_position_screen;
    sf::Vector2f m_position_tile;
};

#endif