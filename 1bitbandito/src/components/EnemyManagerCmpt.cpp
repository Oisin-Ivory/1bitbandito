#include "EnemyManagerCmpt.hpp"
#include "../TextureManager.hpp"
#include "HealthCmpt.hpp"
#include "MoveCmpt.hpp"
#include "WeaponCmpt.hpp"
#include "AICompt.hpp"
#include "AICompt.hpp"
#include "ReadableInfoCMPT.hpp"

EnemyManagerCmpt::EnemyManagerCmpt(int maxCount) {
    maxEnemyCount = maxCount;
}
EnemyManagerCmpt::EnemyManagerCmpt() {
    maxEnemyCount = 50;
}


void EnemyManagerCmpt::Update(float timeDelta) {

}

void EnemyManagerCmpt::Update(float timeDelta, std::vector<Object*>& gameObjects, Map& map) {
    totalEnemiesPassed = 0;
    killedEnemies = 0;
    for (Object* obj : gameObjects) {
        auto info = obj->GetComponent<ReadableInfoCMPT>();
        if (info == nullptr)continue;

        if (!info->containsComponentDetails("Enemy")) continue;

        //dostuffwithenemies

        totalEnemiesPassed++;
        if (obj->isactive == false) {
            killedEnemies++;
        }

        //done with enemies
        if (killedEnemies == activeEnemies) {
            SpawnNextWave(gameObjects, map.mapSize[0], map.mapSize[1]);
            return;
        }

        if (totalEnemiesPassed == activeEnemies) {
            return;
        }
        
    }
}
void EnemyManagerCmpt::SpawnNextWave(std::vector<Object*>& gameObjects, int mapX, int mapY) {
    int enemiesPassed = 0;
    activeEnemies++;
    bool spawnEnemy = true;
    for (Object* obj : gameObjects) {
        auto info = obj->GetComponent<ReadableInfoCMPT>();
        if (info == nullptr)continue;
        if (info->containsComponentDetails("Player")) {
            obj->GetComponent<HealthCmpt>()->HealHealth(25);
           // std::cout << "Healing player" << std::endl;
        }

        if (!info->containsComponentDetails("Enemy")) continue;

        enemiesPassed++;

        if (spawnEnemy) {
            auto mvcmpt = obj->GetComponent<MoveCmpt>();

            sf:Vector2f spawnPos = GetRandomSpawnPos(mapX, mapY);
            mvcmpt->setPositionTile(spawnPos);
            obj->isactive = true;
        }
        if ((enemiesPassed == activeEnemies) || (enemiesPassed == maxEnemyCount)) {
            spawnEnemy = false;
        }
    }
}


sf::Vector2f EnemyManagerCmpt::GetRandomSpawnPos(int mapX, int mapY) {
    int spawnDir = rand() % 3;
    
    switch (spawnDir)
    {
    //x = 0
    case 0:
        return sf::Vector2f(0, rand() % mapY);
        break;
    //y = 0
    case 1:
        return sf::Vector2f(rand() % mapX, 0);
        break;
    //x = mapwidth
    case 2:
        return sf::Vector2f(mapX, rand() % mapY);
        break;
    //y = mapheight
    case 3:
        return sf::Vector2f(rand() % mapX, mapY);

        break;
    default:
        return sf::Vector2f(0, 0);
        break;
    }
}

void EnemyManagerCmpt::Reset() {
    killedEnemies = 0;
    activeEnemies = 1;
    totalEnemiesPassed = 0;

}

int EnemyManagerCmpt::getWave() {
    return activeEnemies;
}