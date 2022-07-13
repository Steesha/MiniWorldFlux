#include "pch.h"
#include "Speed.h"

Speed::Speed() : AbstractModule("Speed", Category::Movement) {

	this->addValue(this->walkSpeed);
	this->addValue(this->sprintSpeed);
	this->addValue(this->sneakSpeed);
	this->addValue(this->swimSpeed);
	this->addValue(this->hopForce);
	this->addValue(this->forwardForce);
	this->addValue(this->mode);

	EventManager::getInstance().reg(Events::EventRenderOverlay, MakeHandler(this, &Speed::onRenderOverlay));
}

Speed* Speed::getInstance() {
	static Speed* inst = new Speed();
	return inst;
}

void Speed::onEnabled() {
		
}

void Speed::onDisabled() {
	IngameCheck;
		
	Game::thePlayer->setWalkSpeed(-1);
	Game::thePlayer->setRunSpeed(-1);
	Game::thePlayer->setSneakSpeed(-1);
	Game::thePlayer->setSwimSpeed(-1);
		
}

void Speed::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;

	if (this->mode->isCurrentMode("Speed")) {
	
		float walkSpeed = this->walkSpeed->getValue();
		float sprintSpeed = this->sprintSpeed->getValue();
		float sneakSpeed = this->sneakSpeed->getValue();
		float swimSpeed = this->swimSpeed->getValue();

		if (Game::thePlayer->getWalkSpeed() != walkSpeed)
			Game::thePlayer->setWalkSpeed(walkSpeed);

		if (Game::thePlayer->getRunSpeed() != sprintSpeed)
			Game::thePlayer->setRunSpeed(sprintSpeed);

		if (Game::thePlayer->getSneakSpeed() != sneakSpeed)
			Game::thePlayer->setSneakSpeed(sneakSpeed);

		if (Game::thePlayer->getSwimSpeed() != swimSpeed)
			Game::thePlayer->setSwimSpeed(swimSpeed);

	}
	else if (this->mode->isCurrentMode("Motion")) {
		
		float motionX = Game::thePlayer->getObject()->playerLocoMotion->motionX;
		float motionY = Game::thePlayer->getObject()->playerLocoMotion->motionY;
		float motionZ = Game::thePlayer->getObject()->playerLocoMotion->motionZ;

#ifdef _DEBUG
		ImGui::Begin("Speed");
		ImGui::Text("MotionXYZ: %.2f\t%.2f\t%.2f", motionX, motionY, motionZ);
		ImGui::End();
#endif

		// JumpState == 1 -> onGround
		if (Game::hasGameInput() && Game::thePlayer->getJumpState()) {

			// Motion X
			if (motionX <= SDK::MOTION_MAX_FORWARD_SPEED) {
				if (motionX > 0)
					Game::thePlayer->getObject()->playerLocoMotion->motionX *= this->forwardForce->getValue();
				else
					Game::thePlayer->getObject()->playerLocoMotion->motionX *= this->forwardForce->getValue();
			}

			// Motion Z
			if (motionZ <= SDK::MOTION_MAX_FORWARD_SPEED) {
				if (motionZ > 0)
					Game::thePlayer->getObject()->playerLocoMotion->motionZ *= this->forwardForce->getValue();
				else
					Game::thePlayer->getObject()->playerLocoMotion->motionZ *= this->forwardForce->getValue();
			}

			// Motion Y
			Game::thePlayer->getObject()->playerLocoMotion->motionY = this->hopForce->getValue();

		}

	}

	

}
