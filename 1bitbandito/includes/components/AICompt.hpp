#ifndef AICMPT_H
#define AICMPT_H

#include "Component.hpp"
#include "WeaponCmpt.hpp"
#include "MoveCmpt.hpp"

class AICompt : public Component
{
public:
    AICompt();
    void SetMoveCmpt(std::shared_ptr<MoveCmpt> mvcmpt);
    void SetWeaponCmpt(std::shared_ptr<WeaponCmpt> wpncmpt);

    virtual void Update(float timeDelta);
    virtual void Update(float timeDelta, Object* target,Map& map);
private:

    sf::Vector2f Move(Object* obj);
    bool HasLineOfSight(std::shared_ptr<MoveCmpt> tmvcmpt, Map& map, int axis);
    sf::Vector2f CanShoot(Object* target, Map& map);
    std::shared_ptr<MoveCmpt> moveCmpt;
    std::shared_ptr<WeaponCmpt> weaponCmpt;
    float moveSpeed = 1;
    float timeSinceLastMove = 10;
};

#endif