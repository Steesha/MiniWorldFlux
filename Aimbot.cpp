#include "Aimbot.h"

Aimbot::Aimbot() : AbstractModule("Aimbot", Category::Combat) {

	this->priority->addMode("Distance3D");

	this->addValue(this->priority);
	this->addValue(this->targetLine);
	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &Aimbot::onRenderOverlay));
}

Aimbot* Aimbot::getInstance() {
	static Aimbot* inst = new Aimbot();
	return inst;
}

void Aimbot::onEnabled() {

}

void Aimbot::onDisabled() {
	this->target = nullptr;
}

void Aimbot::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;
	SinglePlayerCheck;

	this->target = nullptr;
	if (ClickGui::getInstance()->getToggle()) return;

	Vec2 view = Game::getGameViewSize();
	view.x *= 0.5f;
	view.y *= 0.5f;

	if (this->priority->isCurrentMode("Distance3D")) {
	
		std::stable_sort(Game::playerInWorld.begin(), Game::playerInWorld.end(), AimbotScreenDisSorter());
		std::stable_sort(Game::playerInWorld.begin(), Game::playerInWorld.end(), AimbotDisSorter());
		if (TeamCheck) {
			for (SDK::ClientPlayer* p : Game::playerInWorld) {
				if (!Team::isSameTeam(p)) {
					this->target = p;
					break;
				}
			}
		}
		else {
			this->target = Game::playerInWorld[0];
		}
		

	}	
	else if (this->priority->isCurrentMode("Dist2Cross")) {
		
		std::stable_sort(Game::playerInWorld.begin(), Game::playerInWorld.end(), AimbotDisSorter());
		std::stable_sort(Game::playerInWorld.begin(), Game::playerInWorld.end(), AimbotScreenDisSorter());

		SDK::ClientPlayer* tar = nullptr;
		if (TeamCheck) {

			for (SDK::ClientPlayer* p : Game::playerInWorld) {
				if (!Team::isSameTeam(p)) {
					tar = p;
					break;
				}
			}

		}
		else {
			tar = Game::playerInWorld[0];
		}

		if (tar != nullptr) {
			
			Vec3 ePos = { tar->actorBody->entity->posX, tar->actorBody->entity->posY + this->headOffset, tar->actorBody->entity->posZ };
			Vec2 eScPos;
			Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &ePos, &view, &eScPos);
			if (Utility::getDistance2D(view, eScPos) > this->aimRange)
				this->target = nullptr;
			else
				this->target = tar;

		}
		else {
			this->target = nullptr;
		}
		
	}

	if (this->target == nullptr) {
		ImGui::GetForegroundDrawList()->AddCircle(ImVec2(view.x, view.y), this->aimRange, IM_COL32(0, 255, 0, 240));
		return;
	}
	else {
		ImGui::GetForegroundDrawList()->AddCircle(ImVec2(view.x, view.y), this->aimRange, IM_COL32(255, 0, 0, 240));
	}

	Vec3 ePos = { this->target->actorBody->entity->posX, this->target->actorBody->entity->posY + this->headOffset, this->target->actorBody->entity->posZ };
	Vec2 eScPos;
		
	Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &ePos, &view, &eScPos);

	if (this->targetLine->getValue())
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(view.x, view.y), ImVec2(eScPos.x, eScPos.y), IM_COL32(255, 0, 0, 230));

	if (ImGui::IsKeyDown(ImGuiKey_C)) {
		
		Vec3 lpCamPos = Game::thePlayer->getCameraPosition();
		Vec2 angle = Utility::calcAimAngle(&lpCamPos, &ePos);
		Game::thePlayer->setYaw(angle.x);
		Game::thePlayer->setPitch(angle.y);
	}
}

bool AimbotDisSorter::operator()(SDK::ClientPlayer* p1, SDK::ClientPlayer* p2) {
	
	Vec3 p1Pos = { p1->actorBody->entity->posX, p1->actorBody->entity->posY, p1->actorBody->entity->posZ };
	Vec3 p2Pos = { p2->actorBody->entity->posX, p2->actorBody->entity->posY, p2->actorBody->entity->posZ };

	return Utility::getDistance3D(Game::thePlayer->getPosition(), p1Pos) < Utility::getDistance3D(Game::thePlayer->getPosition(), p2Pos);
}

bool AimbotScreenDisSorter::operator()(SDK::ClientPlayer* p1, SDK::ClientPlayer* p2) {

	Vec3 p1Pos = { p1->actorBody->entity->posX, p1->actorBody->entity->posY, p1->actorBody->entity->posZ };
	Vec3 p2Pos = { p2->actorBody->entity->posX, p2->actorBody->entity->posY, p2->actorBody->entity->posZ };
	Vec2 p1ScPos;
	Vec2 p2ScPos;

	Vec2 view = Game::getGameViewSize();
	view.x *= 0.5f;
	view.y *= 0.5f;

	Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &p1Pos, &view, &p1ScPos);
	Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &p2Pos, &view, &p2ScPos);

	return Utility::getDistance2D(view, p1ScPos) < Utility::getDistance2D(view, p2ScPos);
}

SDK::ClientPlayer* Aimbot::getTarget() {
	return this->target;
}

