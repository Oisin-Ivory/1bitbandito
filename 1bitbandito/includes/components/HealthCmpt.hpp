#ifndef HEALTHCMPT_H
#define HEALTHCMPT_H
#include "Component.hpp"
#include <SFML/Audio.hpp>
class HealthCmpt : public Component
{
	virtual void Update(float timeDelta);
public:
	HealthCmpt();
	void DealDamage(int damage);
	void HealHealth(int heal);
	int getHealth();
	void setHealth(int nhealth);
private:
	int health = 100;
	sf::Sound healSound;
	sf::Sound hitSound;
	sf::SoundBuffer healSoundBuffer;
	sf::SoundBuffer hitSoundBuffer;
};

#endif

