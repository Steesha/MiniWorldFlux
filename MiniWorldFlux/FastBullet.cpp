#include "pch.h"
#include "FastBullet.h"

FastBullet::FastBullet() : AbstractModule("FastBullet", Category::Combat) {
	this->addValue(this->interval);
}

FastBullet* FastBullet::getInstance() {
	static FastBullet* inst = new FastBullet();
	return inst;
}

void FastBullet::onEnabled() {
	IngameCheck;
	if (!this->start) {
		SDK::Weapon* weapon = Game::thePlayer->getWeapon();
		if (weapon->currentWeaponAttr->itemID == 0) {
			NotificationManager::getInstance().notify("No weapon in hand!", NotiLevel::ERR, 3);
			return;
		}
		this->originInterval = weapon->currentWeaponAttr->shootInterval;
		weapon->currentWeaponAttr->shootInterval = static_cast<short>(this->interval->getValueLong());
		this->start = true;
	}
}

void FastBullet::onDisabled() {
	if (this->start) {
		SDK::Weapon* weapon = Game::thePlayer->getWeapon();
		weapon->currentWeaponAttr->shootInterval = this->originInterval;
		this->originInterval = 0;
		this->start = false;
	}
}
