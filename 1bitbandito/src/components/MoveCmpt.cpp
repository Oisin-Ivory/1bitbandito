#include "MoveCmpt.hpp"
bool MoveCmpt::updatePosition(sf::Vector2f pos, Map& map) {
    //std::cout << "Trying to move to" << (m_position_tile.x + pos.x) << ", " << (m_position_tile.y + pos.y);
    if ((m_position_tile.x + pos.x) < 0 || (m_position_tile.y + pos.y) < 0 ||
        (m_position_tile.x + pos.x) >= map.mapSize[0] || (m_position_tile.y + pos.y) >= map.mapSize[1]) {
        return false;
    }
    if (map.GetTileAtPos(m_position_tile.x + pos.x, m_position_tile.y + pos.y) > 7) {
        return false;
    }
    m_position_tile.x += pos.x;
    m_position_tile.y += pos.y;
    setPosition(map);
    return true;
}

void MoveCmpt::setPosition(sf::Vector2f pos) {
    m_position_tile.x = pos.x;
    m_position_tile.y = pos.y;
}

void MoveCmpt::setPosition(Map& map) {
    m_position_screen = map.GetTilePos(m_position_tile.x, m_position_tile.y);
   // std::cout << m_position_tile.x << ", " << m_position_tile.y << " position " << std::endl;
}

MoveCmpt::MoveCmpt()
{
    //"safe" defaults
    m_position_tile.x = 0;
    m_position_tile.y = 0;

}

MoveCmpt::MoveCmpt(int x, int y)
{
    m_position_tile.x = x;
    m_position_tile.y = y;
}
MoveCmpt::MoveCmpt(bool projectileState, sf::Vector2f velocity)
{
    m_velocity = velocity;
    isProjectile = projectileState;
}

void MoveCmpt::setPositionTile(sf::Vector2f pos)
{
    m_position_tile = pos;
}

sf::Vector2f MoveCmpt::getPosition()
{
    return m_position_screen;
}

sf::Vector2f MoveCmpt::getTilePos() {
    return m_position_tile;
}