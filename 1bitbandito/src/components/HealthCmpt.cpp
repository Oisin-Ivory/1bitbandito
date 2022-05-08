#include "HealthCmpt.hpp"


void HealthCmpt::DealDamage(int damage) {
	hitSound.play();
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}

HealthCmpt::HealthCmpt() {

	healSoundBuffer.loadFromFile("resources/sound/heal.wav");
	healSound.setBuffer(healSoundBuffer);

	hitSoundBuffer.loadFromFile("resources/sound/hit.wav");
	hitSound.setBuffer(hitSoundBuffer);
}

void HealthCmpt::HealHealth(int heal) {
	health += heal;
	healSound.play();
	if (health > 100) {
		health = 100;
	}
}

int HealthCmpt::getHealth() {
	return health;
}

void HealthCmpt::setHealth(int nhealth) {
	health = nhealth;
}

void HealthCmpt::Update(float timeDelta) {

}

