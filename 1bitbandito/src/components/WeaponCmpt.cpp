#include "WeaponCmpt.hpp"
#include "HealthCmpt.hpp"

WeaponCmpt::WeaponCmpt() {
	for (int i = 0; i < 6; i++) {
		Object bulletToAdd;
		bulletToAdd.AttachComponent<AnimatedSpriteCmpt>();
		bulletToAdd.GetComponent<AnimatedSpriteCmpt>()->AddTexture(TextureManager::GetTexture(TextureManager::AddTexture("resources/tools/bullet_frame0.png")));
		bulletToAdd.GetComponent<AnimatedSpriteCmpt>()->AddTexture(TextureManager::GetTexture(TextureManager::AddTexture("resources/tools/bullet_frame1.png")));
		bulletToAdd.GetComponent<AnimatedSpriteCmpt>()->cycleTime = shotSpeed;
		bulletToAdd.AttachComponent<MoveCmpt>(true, sf::Vector2f(0, 0));
		bullets.push_back(bulletToAdd);
		
		bulletTimes.push_back(0);

		std::vector<Object*> objvec;
		hitTargets.push_back(objvec);
	}

	shootSoundBuffer.loadFromFile("resources/sound/heal.wav");
	shootSound.setBuffer(shootSoundBuffer);
}



float  WeaponCmpt::GetAvailableBulletIndex() {
	for (int i = 0; i < bullets.size(); i++) {
		if (!bullets[i].GetComponent<MoveCmpt>()->isMoving)
			return i;
	}
	return -1;
}
void WeaponCmpt::Shoot(sf::Vector2f dir,sf::Vector2f startingPos) {
	if (timeSinceLastShot < fireDelay) return;

	float index = GetAvailableBulletIndex();
	if (index == -1)return;
	//std::cout << timeSinceLastShot << ", " << fireDelay << std::endl;
	auto mvcmpt = bullets[index].GetComponent<MoveCmpt>();
	if (mvcmpt->isMoving == true)
		return;

	shootSound.play();
	mvcmpt->setPositionTile(startingPos + dir);
	//std::cout << "setting bullet position at tile: " << startingPos.x << ", " << startingPos.y << std::endl;
	mvcmpt->m_velocity = dir;
	mvcmpt->isMoving = true;

	timeSinceLastShot = 0;
	//std::cout << "pew" << std::endl;
}

std::vector<Object>& WeaponCmpt::GetBullets() {
	return bullets;
}

void WeaponCmpt::Update() {

}
void WeaponCmpt::Update(float time,std::vector<Object*> m_gameObjects) {


	timeSinceLastShot += time;
	for (int i = 0; i < bullets.size(); i++) {
		bulletTimes[i] += time;
		bullets[i].GetComponent<AnimatedSpriteCmpt>()->Update(time);
	}

	for (int bindex = 0; bindex < bullets.size(); bindex++) {
		auto animspcmpt = bullets[bindex].GetComponent<AnimatedSpriteCmpt>();
		if (animspcmpt != nullptr) {
			animspcmpt->Update(time);
		}
		for (Object* target : m_gameObjects) {
			if (target->isactive == false) continue;
			auto healthcmpt = target->GetComponent<HealthCmpt>();
			if (healthcmpt == nullptr) continue;
			auto mvcmpt = target->GetComponent<MoveCmpt>();
			if (mvcmpt == nullptr) continue;
			if (bullets[bindex].GetComponent<MoveCmpt>()->getTilePos() == mvcmpt->getTilePos() && !IsTargetHit(bindex,target)) {
				if (bullets[bindex].GetComponent<MoveCmpt>()->isMoving == false)continue;
				AddHitTargetToBullet(bindex, target);
				healthcmpt->DealDamage(50);
				//std::cout << "Damaging health is: " << healthcmpt->getHealth() << std::endl;
				if (healthcmpt->getHealth() == 0) {
					target->isactive = false;
					healthcmpt->HealHealth(100);
					//std::cout << "Disabling target: " << target->isactive << std::endl;
					auto twpncmpt = target->GetComponent<WeaponCmpt>();
					if (twpncmpt != nullptr) {
						for (auto bullet : twpncmpt->GetBullets()) {
							auto bmvcmpt = bullet.GetComponent<MoveCmpt>();
							bmvcmpt->isMoving = false;
						}
					}
				}
			}
			
		}
	}
}



void WeaponCmpt::Draw(sf::RenderWindow& window,Map& map) {
	for (int i = 0; i < bullets.size();i++) {
		auto mvecmpt = bullets[i].GetComponent<MoveCmpt>();
		auto sprtcmpt = bullets[i].GetComponent<AnimatedSpriteCmpt>();
		if (mvecmpt->isMoving) {
			//std::cout << i << " is moving | " << bulletTimes[i] << " > " << shotSpeed << (bulletTimes[i] > shotSpeed) << std::endl;
			if (bulletTimes[i] > shotSpeed) {
				//std::cout << i << " is ready to move " << std::endl;
				if (!mvecmpt->updatePosition(mvecmpt->m_velocity, map)) {
					mvecmpt->isMoving = false;
					hitTargets[i].clear();
				}
				//std::cout << "Drawing bullet at position: " << mvecmpt->getTilePos().x << ", " << mvecmpt->getTilePos().y << std::endl;
				//std::cout << "Updating bullet pos by: " << mvecmpt->m_velocity.x << ", " << mvecmpt->m_velocity.y << std::endl;
				bulletTimes[i] = 0;
			}
			sprtcmpt->setPosition(mvecmpt->getPosition());
			sprtcmpt->Draw(window,0);
		}
	}
}

void WeaponCmpt::AddHitTargetToBullet(int bullet, Object* obj) {
	hitTargets[bullet].push_back(obj);
}

bool WeaponCmpt::IsTargetHit(int bullet, Object* obj){
	if (hitTargets[bullet].size() == 0) return false;
	for (Object* object : hitTargets[bullet]) {

		if (object == obj) return true;
	}

	return false;
}

void WeaponCmpt::Reset() {
	for (auto bullet : bullets) {
		bullet.GetComponent<MoveCmpt>()->isMoving = false;
	}
}