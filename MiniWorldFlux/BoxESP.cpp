#include "pch.h"
#include "BoxESP.h"

BoxESP::BoxESP() : AbstractModule("BoxESP", Category::Visual) {

	this->boxMode->addMode("Surface");
	this->boxMode->addMode("Star Ring");

	this->addValue(this->sight);
	this->addValue(this->boxMode);
	this->addValue(this->radius);
	this->addValue(this->ringSpeed);

	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &BoxESP::onRenderOverlay));
}

BoxESP* BoxESP::getInstance() {
	static BoxESP* inst = new BoxESP();
	return inst;
}

void BoxESP::onEnabled() {

}

void BoxESP::onDisabled() {

}

void BoxESP::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;
	SinglePlayerCheck;

	Vec2 view;
	view = Game::getGameViewSize();
	view.x *= 0.5f;
	view.y *= 0.5f;

	if (this->boxMode->isCurrentMode("Star Ring")) {

		ImDrawList* dl = ImGui::GetForegroundDrawList();
		
		Vec3 p0;
		Vec3 p1;
		Vec3 p2;
		Vec3 p3;
		Vec3 p4;
		Vec3 p5;
		Vec3 p6;
		Vec3 p7;

		Vec2 p0Sc;
		Vec2 p1Sc;
		Vec2 p2Sc;
		Vec2 p3Sc;
		Vec2 p4Sc;
		Vec2 p5Sc;
		Vec2 p6Sc;
		Vec2 p7Sc;

		int count = 0;
		for (SDK::ClientPlayer* p : Game::playerInWorld) {

			if (this->direction) {

				this->curYOffset += ringSpeed->getValue();
				curPosition.x = p->actorBody->entity->posX;
				curPosition.y = p->actorBody->entity->posY + this->curYOffset;
				curPosition.z = p->actorBody->entity->posZ;
				if (this->curYOffset >= this->headOffset) this->direction = false;
			}
			else {

				this->curYOffset -= ringSpeed->getValue();
				curPosition.x = p->actorBody->entity->posX;
				curPosition.y = p->actorBody->entity->posY + this->headOffset - (this->headOffset - (this->curYOffset));
				curPosition.z = p->actorBody->entity->posZ;
				if (this->curYOffset <= 0) this->direction = true;
			}

			p0 = this->rotatePointYaw(curPosition, this->radius->getValue(), 45);
			p1 = this->rotatePointYaw(curPosition, this->radius->getValue(), 90);
			p2 = this->rotatePointYaw(curPosition, this->radius->getValue(), 135);
			p3 = this->rotatePointYaw(curPosition, this->radius->getValue(), 180);
			p4 = this->rotatePointYaw(curPosition, this->radius->getValue(), 225);
			p5 = this->rotatePointYaw(curPosition, this->radius->getValue(), 270);
			p6 = this->rotatePointYaw(curPosition, this->radius->getValue(), 315);
			p7 = this->rotatePointYaw(curPosition, this->radius->getValue(), 360);

			bool canDraw = true;
			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &p0, &view, &p0Sc);
			if (!canDraw) continue;
			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &p1, &view, &p1Sc);
			if (!canDraw) continue;
			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &p2, &view, &p2Sc);
			if (!canDraw) continue;
			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &p3, &view, &p3Sc);
			if (!canDraw) continue;
			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &p4, &view, &p4Sc);
			if (!canDraw) continue;
			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &p5, &view, &p5Sc);
			if (!canDraw) continue;
			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &p6, &view, &p6Sc);
			if (!canDraw) continue;
			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &p7, &view, &p7Sc);
			if (!canDraw) continue;

			dl->AddLine(ImVec2(p0Sc.x, p0Sc.y), ImVec2(p5Sc.x, p5Sc.y), Utility::rainbow(50, (count++) * 50), 1.3f);
			dl->AddLine(ImVec2(p0Sc.x, p0Sc.y), ImVec2(p3Sc.x, p3Sc.y), Utility::rainbow(50, (count++) * 50), 1.3f);
			dl->AddLine(ImVec2(p1Sc.x, p1Sc.y), ImVec2(p6Sc.x, p6Sc.y), Utility::rainbow(50, (count++) * 50), 1.3f);
			dl->AddLine(ImVec2(p1Sc.x, p1Sc.y), ImVec2(p4Sc.x, p4Sc.y), Utility::rainbow(50, (count++) * 50), 1.3f);
			dl->AddLine(ImVec2(p2Sc.x, p2Sc.y), ImVec2(p7Sc.x, p7Sc.y), Utility::rainbow(50, (count++) * 50), 1.3f);
			dl->AddLine(ImVec2(p2Sc.x, p2Sc.y), ImVec2(p5Sc.x, p5Sc.y), Utility::rainbow(50, (count++) * 50), 1.3f);
			dl->AddLine(ImVec2(p3Sc.x, p3Sc.y), ImVec2(p6Sc.x, p6Sc.y), Utility::rainbow(50, (count++) * 50), 1.3f);
			dl->AddLine(ImVec2(p4Sc.x, p4Sc.y), ImVec2(p7Sc.x, p7Sc.y), Utility::rainbow(50, (count++) * 50), 1.3f);

		}

	}
	else {

		Vec3 ePos;
		Vec2 eScPos;
		Vec3 eHeadPos;

		Vec3 bp1;
		Vec2 bp1Sc;
		Vec3 bp2;
		Vec2 bp2Sc;
		Vec3 bp3;
		Vec2 bp3Sc;
		Vec3 bp4;
		Vec2 bp4Sc;

		Vec3 tp1;
		Vec2 tp1Sc;
		Vec3 tp2;
		Vec2 tp2Sc;
		Vec3 tp3;
		Vec2 tp3Sc;
		Vec3 tp4;
		Vec2 tp4Sc;

		Vec3 sightStartPos;
		Vec3 sightEndPos;
		Vec2 sightStartScPos;
		Vec2 sightEndScPos;
		
		for (SDK::ClientPlayer* p : Game::playerInWorld) {

			ePos.x = p->actorBody->entity->posX;
			ePos.y = p->actorBody->entity->posY;
			ePos.z = p->actorBody->entity->posZ;

			eHeadPos.x = p->actorBody->entity->posX;
			eHeadPos.y = p->actorBody->entity->posY + this->headOffset;
			eHeadPos.z = p->actorBody->entity->posZ;

			sightStartPos.x = p->actorBody->entity->posX;
			sightStartPos.y = p->actorBody->entity->posY + this->sightXOffset;
			sightStartPos.z = p->actorBody->entity->posZ;

			bool canDraw = true;
			bp1 = this->rotatePointYaw(ePos, this->radius->getValue(), (0 - (p->playerLocoMotion->yaw)) + 45);
			bp2 = this->rotatePointYaw(ePos, this->radius->getValue(), (0 - (p->playerLocoMotion->yaw)) + 135);
			bp3 = this->rotatePointYaw(ePos, this->radius->getValue(), (0 - (p->playerLocoMotion->yaw)) + 225);
			bp4 = this->rotatePointYaw(ePos, this->radius->getValue(), (0 - (p->playerLocoMotion->yaw)) + 315);
			tp1 = this->rotatePointYaw(eHeadPos, this->radius->getValue(), (0 - (p->playerLocoMotion->yaw)) + 45);
			tp2 = this->rotatePointYaw(eHeadPos, this->radius->getValue(), (0 - (p->playerLocoMotion->yaw)) + 135);
			tp3 = this->rotatePointYaw(eHeadPos, this->radius->getValue(), (0 - (p->playerLocoMotion->yaw)) + 225);
			tp4 = this->rotatePointYaw(eHeadPos, this->radius->getValue(), (0 - (p->playerLocoMotion->yaw)) + 315);

			Vec3 sightYaw = this->rotatePointYaw(sightStartPos, this->sightLength, 0 - (p->playerLocoMotion->yaw) - 90);
			Vec3 sightPitch = this->rotatePointPitch(sightStartPos, this->sightLength, 0 - (p->playerLocoMotion->pitch));
			sightEndPos.x = sightYaw.x;
			sightEndPos.y = sightPitch.y;
			sightEndPos.z = sightYaw.z;

			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &bp1, &view, &bp1Sc);
			if (!canDraw) continue;
			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &bp2, &view, &bp2Sc);
			if (!canDraw) continue;
			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &bp3, &view, &bp3Sc);
			if (!canDraw) continue;
			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &bp4, &view, &bp4Sc);
			if (!canDraw) continue;
			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &tp1, &view, &tp1Sc);
			if (!canDraw) continue;
			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &tp2, &view, &tp2Sc);
			if (!canDraw) continue;
			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &tp3, &view, &tp3Sc);
			if (!canDraw) continue;
			canDraw = Utility::worldToScreen(Game::thePlayer->matrix, &tp4, &view, &tp4Sc);
			if (!canDraw) continue;
			Utility::worldToScreen(Game::thePlayer->matrix, &sightStartPos, &view, &sightStartScPos);
			bool canDrawSight = Utility::worldToScreen(Game::thePlayer->matrix, &sightEndPos, &view, &sightEndScPos);

			ImDrawList* dl = ImGui::GetForegroundDrawList();

			if (TeamCheck && Team::isSameTeam(p)) {

				// 3D Rect
				if (this->boxMode->isCurrentMode("Line")) {

					dl->AddLine(ImVec2(bp1Sc.x, bp1Sc.y), ImVec2(bp2Sc.x, bp2Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
					dl->AddLine(ImVec2(bp2Sc.x, bp2Sc.y), ImVec2(bp3Sc.x, bp3Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
					dl->AddLine(ImVec2(bp3Sc.x, bp3Sc.y), ImVec2(bp4Sc.x, bp4Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
					dl->AddLine(ImVec2(bp4Sc.x, bp4Sc.y), ImVec2(bp1Sc.x, bp1Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
					dl->AddLine(ImVec2(tp1Sc.x, tp1Sc.y), ImVec2(tp2Sc.x, tp2Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
					dl->AddLine(ImVec2(tp2Sc.x, tp2Sc.y), ImVec2(tp3Sc.x, tp3Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
					dl->AddLine(ImVec2(tp3Sc.x, tp3Sc.y), ImVec2(tp4Sc.x, tp4Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
					dl->AddLine(ImVec2(tp4Sc.x, tp4Sc.y), ImVec2(tp1Sc.x, tp1Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
					dl->AddLine(ImVec2(bp1Sc.x, bp1Sc.y), ImVec2(tp1Sc.x, tp1Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
					dl->AddLine(ImVec2(bp2Sc.x, bp2Sc.y), ImVec2(tp2Sc.x, tp2Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
					dl->AddLine(ImVec2(bp3Sc.x, bp3Sc.y), ImVec2(tp3Sc.x, tp3Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
					dl->AddLine(ImVec2(bp4Sc.x, bp4Sc.y), ImVec2(tp4Sc.x, tp4Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);

				}
				else if (this->boxMode->isCurrentMode("Surface")) {

					dl->AddQuadFilled(ImVec2(bp1Sc.x, bp1Sc.y), ImVec2(bp2Sc.x, bp2Sc.y), ImVec2(bp3Sc.x, bp3Sc.y), ImVec2(bp4Sc.x, bp4Sc.y), IM_COL32(18, 255, 18, 50));
					dl->AddQuadFilled(ImVec2(tp1Sc.x, tp1Sc.y), ImVec2(tp2Sc.x, tp2Sc.y), ImVec2(tp3Sc.x, tp3Sc.y), ImVec2(tp4Sc.x, tp4Sc.y), IM_COL32(18, 255, 18, 50));
					dl->AddQuadFilled(ImVec2(bp3Sc.x, bp3Sc.y), ImVec2(bp4Sc.x, bp4Sc.y), ImVec2(tp4Sc.x, tp4Sc.y), ImVec2(tp3Sc.x, tp3Sc.y), IM_COL32(18, 255, 18, 50));
					dl->AddQuadFilled(ImVec2(bp2Sc.x, bp2Sc.y), ImVec2(bp1Sc.x, bp1Sc.y), ImVec2(tp1Sc.x, tp1Sc.y), ImVec2(tp2Sc.x, tp2Sc.y), IM_COL32(18, 255, 18, 50));
					dl->AddQuadFilled(ImVec2(bp2Sc.x, bp2Sc.y), ImVec2(bp3Sc.x, bp3Sc.y), ImVec2(tp3Sc.x, tp3Sc.y), ImVec2(tp2Sc.x, tp2Sc.y), IM_COL32(18, 255, 18, 50));
					dl->AddQuadFilled(ImVec2(bp1Sc.x, bp1Sc.y), ImVec2(bp4Sc.x, bp4Sc.y), ImVec2(tp4Sc.x, tp4Sc.y), ImVec2(tp1Sc.x, tp1Sc.y), IM_COL32(18, 255, 18, 50));

				}

				// Sight Line
				if (this->sight->getValue() && canDrawSight) {
					dl->AddLine(ImVec2(sightStartScPos.x, sightStartScPos.y), ImVec2(sightEndScPos.x, sightEndScPos.y), IM_COL32(18, 255, 18, 245), 1.5f);
					dl->AddCircleFilled(ImVec2(sightStartScPos.x, sightStartScPos.y), 3, IM_COL32(18, 255, 18, 245));
					dl->AddCircleFilled(ImVec2(sightEndScPos.x, sightEndScPos.y), 3, IM_COL32(18, 255, 18, 245));
				}

			}
			else {

				// 3D Rect
				if (this->boxMode->isCurrentMode("Line")) {

					dl->AddLine(ImVec2(bp1Sc.x, bp1Sc.y), ImVec2(bp2Sc.x, bp2Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
					dl->AddLine(ImVec2(bp2Sc.x, bp2Sc.y), ImVec2(bp3Sc.x, bp3Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
					dl->AddLine(ImVec2(bp3Sc.x, bp3Sc.y), ImVec2(bp4Sc.x, bp4Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
					dl->AddLine(ImVec2(bp4Sc.x, bp4Sc.y), ImVec2(bp1Sc.x, bp1Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
					dl->AddLine(ImVec2(tp1Sc.x, tp1Sc.y), ImVec2(tp2Sc.x, tp2Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
					dl->AddLine(ImVec2(tp2Sc.x, tp2Sc.y), ImVec2(tp3Sc.x, tp3Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
					dl->AddLine(ImVec2(tp3Sc.x, tp3Sc.y), ImVec2(tp4Sc.x, tp4Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
					dl->AddLine(ImVec2(tp4Sc.x, tp4Sc.y), ImVec2(tp1Sc.x, tp1Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
					dl->AddLine(ImVec2(bp1Sc.x, bp1Sc.y), ImVec2(tp1Sc.x, tp1Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
					dl->AddLine(ImVec2(bp2Sc.x, bp2Sc.y), ImVec2(tp2Sc.x, tp2Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
					dl->AddLine(ImVec2(bp3Sc.x, bp3Sc.y), ImVec2(tp3Sc.x, tp3Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
					dl->AddLine(ImVec2(bp4Sc.x, bp4Sc.y), ImVec2(tp4Sc.x, tp4Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);

				}
				else if (this->boxMode->isCurrentMode("Surface")) {

					dl->AddQuadFilled(ImVec2(bp1Sc.x, bp1Sc.y), ImVec2(bp2Sc.x, bp2Sc.y), ImVec2(bp3Sc.x, bp3Sc.y), ImVec2(bp4Sc.x, bp4Sc.y), IM_COL32(255, 18, 18, 50));
					dl->AddQuadFilled(ImVec2(tp1Sc.x, tp1Sc.y), ImVec2(tp2Sc.x, tp2Sc.y), ImVec2(tp3Sc.x, tp3Sc.y), ImVec2(tp4Sc.x, tp4Sc.y), IM_COL32(255, 18, 18, 50));
					dl->AddQuadFilled(ImVec2(bp3Sc.x, bp3Sc.y), ImVec2(bp4Sc.x, bp4Sc.y), ImVec2(tp4Sc.x, tp4Sc.y), ImVec2(tp3Sc.x, tp3Sc.y), IM_COL32(255, 18, 18, 50));
					dl->AddQuadFilled(ImVec2(bp2Sc.x, bp2Sc.y), ImVec2(bp1Sc.x, bp1Sc.y), ImVec2(tp1Sc.x, tp1Sc.y), ImVec2(tp2Sc.x, tp2Sc.y), IM_COL32(255, 18, 18, 50));
					dl->AddQuadFilled(ImVec2(bp2Sc.x, bp2Sc.y), ImVec2(bp3Sc.x, bp3Sc.y), ImVec2(tp3Sc.x, tp3Sc.y), ImVec2(tp2Sc.x, tp2Sc.y), IM_COL32(255, 18, 18, 50));
					dl->AddQuadFilled(ImVec2(bp1Sc.x, bp1Sc.y), ImVec2(bp4Sc.x, bp4Sc.y), ImVec2(tp4Sc.x, tp4Sc.y), ImVec2(tp1Sc.x, tp1Sc.y), IM_COL32(255, 18, 18, 50));

				}

				// Sight Line
				if (this->sight->getValue() && canDrawSight) {
					dl->AddLine(ImVec2(sightStartScPos.x, sightStartScPos.y), ImVec2(sightEndScPos.x, sightEndScPos.y), IM_COL32(255, 18, 18, 245), 1.5f);
					dl->AddCircleFilled(ImVec2(sightStartScPos.x, sightStartScPos.y), 3, IM_COL32(255, 18, 18, 245));
					dl->AddCircleFilled(ImVec2(sightEndScPos.x, sightEndScPos.y), 2.7f, IM_COL32(255, 18, 18, 245));
				}

			}

		}

	}

}

Vec3 BoxESP::rotatePointYaw(Vec3 opc, float radius, float angle) {
		
	float rad = (3.14159f / 180) * angle;

	Vec3 res;
	res.x = opc.x + cosf(rad) * radius;
	res.y = opc.y;
	res.z = opc.z + sinf(rad) * radius;

	return res;
}

Vec3 BoxESP::rotatePointPitch(Vec3 opc, float radius, float angle) {

	float rad = (3.14159f / 180) * angle;

	Vec3 res;
	res.x = opc.x;
	res.y = opc.y + sinf(rad) * radius;
	res.z = opc.z;

	return res;
}
