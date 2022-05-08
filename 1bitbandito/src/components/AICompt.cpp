

#include "AICompt.hpp"

AICompt::AICompt() {

}

void AICompt::SetMoveCmpt(std::shared_ptr<MoveCmpt> mvcmpt) {
	moveCmpt = mvcmpt;
}

void AICompt::SetWeaponCmpt(std::shared_ptr<WeaponCmpt> wpncmpt) {
	weaponCmpt = wpncmpt;
}

void AICompt::Update(float timeDelta, Object* target,Map& map) {

	timeSinceLastMove += timeDelta;
	sf::Vector2f dir = CanShoot(target, map);
	//std::cout << dir.x << ", " << dir.y << std::endl;
	if (dir != sf::Vector2f( -1, -1 ) ){
		weaponCmpt->Shoot(dir, moveCmpt->getTilePos());
		return;
	}
	
	sf::Vector2f mdir = Move(target);
	moveCmpt->updatePosition(mdir,map);
}

void AICompt::Update(float dt) {

}


bool AICompt::HasLineOfSight(std::shared_ptr<MoveCmpt> tmvcmpt,Map& map,int axis) {
	float diffy = tmvcmpt->getTilePos().y - moveCmpt->getTilePos().y;

	float diffx = tmvcmpt->getTilePos().x - moveCmpt->getTilePos().x;
	if (diffy < 0) diffy *= -1;
	if (diffx < 0) diffx *= -1;

	if (axis < 2) {
		for (int i = 0; i < diffy; i++) {
			if (axis == 0) {
				//std::cout << "axis check 0" << std::endl;

				//std::cout << moveCmpt->getTilePos().x << ", " << (moveCmpt->getTilePos().y + i) << ": " << map.GetTileAtPos(moveCmpt->getTilePos().x, moveCmpt->getTilePos().y + i) << std::endl;

				if (map.GetTileAtPos(moveCmpt->getTilePos().x , moveCmpt->getTilePos().y + i) > 7) {
					
					return false;
				}
			}
			if (axis == 1) {
				//std::cout << "axis check 1" << std::endl;
					
				//std::cout << (moveCmpt->getTilePos().x) << ", "<< (moveCmpt->getTilePos().y-i) << ": "<< map.GetTileAtPos(moveCmpt->getTilePos().x, moveCmpt->getTilePos().y - i-1  ) << std::endl;
				if (moveCmpt->getTilePos().y - i < 0) break;
				if (map.GetTileAtPos(moveCmpt->getTilePos().x, moveCmpt->getTilePos().y - i) > 7) {
					return false;
				}
			}
		}
	}
	else {
		for (int i = 0; i < diffx; i++) {
			if (axis == 2) {
				//std::cout << "axis check 2" << std::endl;

				if (map.GetTileAtPos(moveCmpt->getTilePos().x + i, moveCmpt->getTilePos().y) > 7) {
					return false;
				}
			}
			if (axis == 3) {
				//std::cout << "axis check 3" << std::endl;

				if (map.GetTileAtPos(moveCmpt->getTilePos().x - i, moveCmpt->getTilePos().y) > 7) {
					return false;
				}
			}
		}
	}
	
	return true;
}

sf::Vector2f AICompt::CanShoot(Object* target,Map& map) {
	auto tmvcmpt = target->GetComponent<MoveCmpt>();
	if (tmvcmpt->getTilePos().x == moveCmpt->getTilePos().x) {
		//std::cout << "X is equal" << std::endl;

			//IF TARGET IS LOWER
		if (tmvcmpt->getTilePos().y > moveCmpt->getTilePos().y) {
			//std::cout << "Checking Lower" << std::endl;

			if (!HasLineOfSight(tmvcmpt,map,0))
				return { -1,-1 };

			return { 0,1 };
		}
		else {
			//IF TARGET IS HIGHER
			//std::cout << "Checking Higher" << std::endl;

			if (!HasLineOfSight(tmvcmpt, map,1))
				return { -1,-1 };

			return { 0,-1 };
		}
	}
	if (tmvcmpt->getTilePos().y == moveCmpt->getTilePos().y) {
		//std::cout << "Y is equal" << std::endl;
		//IF TARGET IS RIGHT
		if (tmvcmpt->getTilePos().x > moveCmpt->getTilePos().x) {

			//std::cout << "Checking Right" << std::endl;
			if (!HasLineOfSight(tmvcmpt, map, 2))
				return { -1,-1 };


			return { 1,0 };
		}
		else {
			//IF TARGET IS LEFT
			//std::cout << "Checking Left" << std::endl;
			if (!HasLineOfSight(tmvcmpt, map, 3))
				return { -1,-1 };

			return { -1,0 };
		}
	}
	return { -1,-1 };
}

sf::Vector2f AICompt::Move(Object* target) {
	if (timeSinceLastMove < moveSpeed) return { 0,0 };
	timeSinceLastMove = 0;
	sf::Vector2f distanceToMove = { 0,0 };
	auto tmvcmpt = target->GetComponent<MoveCmpt>();
	if (tmvcmpt->getTilePos().x != moveCmpt->getTilePos().x) {
		if (tmvcmpt->getTilePos().x > moveCmpt->getTilePos().x) {
			distanceToMove += { 1,0 };
		}
		else {
			distanceToMove += { -1,0 };
		}
	}
	if (tmvcmpt->getTilePos().y != moveCmpt->getTilePos().y) {
		if (tmvcmpt->getTilePos().y > moveCmpt->getTilePos().y) {
			distanceToMove +={ 0,1 };
		}
		else {
			distanceToMove+={ 0,-1 };
		}
	}
	//std::cout << "moving: "<< distanceToMove.x << ", "<< distanceToMove.y << std::endl;
	return distanceToMove;
}