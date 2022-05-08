#ifndef WPNCMPT_H
#define WPNCMPT_H

#include "Component.hpp"
#include "../Object.hpp"
#include "../Map.hpp"
#include "spriteCmpt.hpp"
#include "MoveCmpt.hpp"
#include "AnimatedSpriteCmpt.hpp"
#include "SFML/Audio.hpp"
class WeaponCmpt : public Component {

public:
	WeaponCmpt();
	void Shoot(sf::Vector2f dir,sf::Vector2f startingpos);
	std::vector<Object>& GetBullets();
	void Update();
	void Update(float time, std::vector<Object*> m_gameObjects);
	void Draw(sf::RenderWindow& window, Map& map);
	int bulletIndex = 0;
	std::vector<Object> bullets;
	void AddHitTargetToBullet(int bullet, Object* obj);
	bool IsTargetHit(int bullet, Object* obj);
	void Reset();
private:
	float GetAvailableBulletIndex();
	float timeSinceLastShot = 10;
	float fireDelay = 0.5;

	std::vector<std::vector<Object*>> hitTargets;
	std::vector<float> bulletTimes;
	float shotSpeed = 0.25;


	sf::Sound shootSound;
	sf::SoundBuffer shootSoundBuffer;

};
#endif
