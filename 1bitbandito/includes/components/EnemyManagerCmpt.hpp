#ifndef EnemyManager_H
#define EnemyManager_H

#include "component.hpp"
#include "../Object.hpp"
#include "../Map.hpp"

class EnemyManagerCmpt : public Component
{
   
public:
    EnemyManagerCmpt(int maxCount);
    EnemyManagerCmpt();
    virtual void Update(float timeDelta, std::vector<Object*>& gameObjects, Map& mp);
    virtual void Update(float timeDelta);
    void Reset();
    int getWave();
private:
    sf::Vector2f GetRandomSpawnPos(int mapX, int mapY);
    void SpawnNextWave(std::vector<Object*>& gameObjects, int mapX, int mapY);
    bool allEnemiesDead = true;
    int killedEnemies = 0;
    int maxEnemyCount = 50;
    int activeEnemies = 1;
    int totalEnemiesPassed = 0;
    Map* map;
};

#endif