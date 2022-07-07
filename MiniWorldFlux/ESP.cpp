#include "pch.h"
#include "ESP.h"

ESP::ESP() : AbstractModule("ESP", Category::Visual) {

	this->mode->addMode("Aimware");

	this->addValue(this->health);
	this->addValue(this->mode);
	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &ESP::onRenderOverlay));
}

ESP* ESP::getInstance() {
	static ESP* inst = new ESP();
	return inst;
}

void ESP::onEnabled() {

}

void ESP::onDisabled() {

}

void ESP::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;
	SinglePlayerCheck;

	Vec3 ePos;
	Vec2 view;
	Vec4 camera;

	constexpr float blackThickness = 2.1f;
	constexpr float whiteThickness = 1.3f;
	constexpr float healthBarGapThickness = 2;

	for (SDK::ClientPlayer* p : Game::playerInWorld) {
		
		ePos.x = p->actorBody->entity->posX;
		ePos.y = p->actorBody->entity->posY;
		ePos.z = p->actorBody->entity->posZ;

		view = Game::getGameViewSize();
		view.x *= 0.5f;
		view.y *= 0.5f;
		
		camera.w = Game::thePlayer->matrix[0][3] * p->actorBody->entity->posX + Game::thePlayer->matrix[1][3] * p->actorBody->entity->posY + Game::thePlayer->matrix[2][3] * p->actorBody->entity->posZ + Game::thePlayer->matrix[3][3];
		if (camera.w < 0.01f) continue;

		float scale = 1 / camera.w;
		camera.x = view.x + (Game::thePlayer->matrix[0][0] * p->actorBody->entity->posX + Game::thePlayer->matrix[1][0] * p->actorBody->entity->posY + Game::thePlayer->matrix[2][0] * p->actorBody->entity->posZ + Game::thePlayer->matrix[3][0]) * scale * view.x;
		camera.y = view.y - (Game::thePlayer->matrix[0][1] * p->actorBody->entity->posX + Game::thePlayer->matrix[1][1] * p->actorBody->entity->posY + Game::thePlayer->matrix[2][1] * p->actorBody->entity->posZ + Game::thePlayer->matrix[3][1]) * scale * view.y;
		camera.z = view.y - (Game::thePlayer->matrix[0][1] * p->actorBody->entity->posX + Game::thePlayer->matrix[1][1] * (p->actorBody->entity->posY + 200) + Game::thePlayer->matrix[2][1] * p->actorBody->entity->posZ + Game::thePlayer->matrix[3][1]) * scale * view.y;

		float rectHeight = camera.y - camera.z;
		float rectWidth = rectHeight * 0.6015625f;

		ImVec2 leftTop(camera.x - rectWidth / 2, camera.z + 6);
		ImVec2 rightBottom(leftTop.x + rectWidth, leftTop.y + rectHeight + 6);

		constexpr float lineLength = 8;

		ImVec2 rightTop(leftTop.x + rectWidth, leftTop.y);
		ImVec2 leftBottom(rightBottom.x - rectWidth, rightBottom.y);

		// Health rect
		float curHealth = p->playerAttribuLua->currentHealth;
		float maxHealth = p->playerAttribuLua->maxHealth;
		ImVec2 healthPos1(leftTop.x - 10, leftTop.y);
		ImVec2 healthPos2(leftTop.x - 5, leftTop.y + rectHeight);		
		float healthHeight = Utility::map(curHealth, 0, maxHealth, healthPos2.y, healthPos1.y);
		ImVec2 curHealthPos(healthPos1.x + 1, healthHeight + 1);

		// »æÖÆ
		ImDrawList* dl = ImGui::GetForegroundDrawList();
		ImU32 color = (TeamCheck && Team::isSameTeam(p) ? FluxColor::TeamSame : FluxColor::TeamDifferent);

		if (this->mode->isCurrentMode("Corners")) {
		
			// Left Top
			dl->AddLine(leftTop, ImVec2(leftTop.x + lineLength, leftTop.y), color, 1.8f);
			dl->AddLine(leftTop, ImVec2(leftTop.x, leftTop.y + lineLength), color, 1.8f);

			// Right Top
			dl->AddLine(rightTop, ImVec2(rightTop.x - lineLength, rightTop.y), color, 1.8f);
			dl->AddLine(rightTop, ImVec2(rightTop.x, rightTop.y + lineLength), color, 1.8f);

			// Left Bottom
			dl->AddLine(leftBottom, ImVec2(leftBottom.x + lineLength, leftBottom.y), color, 1.8f);
			dl->AddLine(leftBottom, ImVec2(leftBottom.x, leftBottom.y - lineLength), color, 1.8f);

			// Right Bottom
			dl->AddLine(rightBottom, ImVec2(rightBottom.x - lineLength, rightBottom.y), color, 1.8f);
			dl->AddLine(rightBottom, ImVec2(rightBottom.x, rightBottom.y - lineLength), color, 1.8f);

		}
		else if (this->mode->isCurrentMode("Aimware")) {
		
			constexpr float gap = 1.5f;
			dl->AddRect(ImVec2(leftTop.x - gap, leftTop.y - gap), ImVec2(rightBottom.x + gap * 2, rightBottom.y + gap * 2), FluxColor::Black, 0, 0, blackThickness);
			dl->AddRect(leftTop, rightBottom, FluxColor::White, 0, 0, whiteThickness);

		}
		
		// Health
		if (this->health->getValue()) {
		
			if (curHealth <= (maxHealth / 3)) {
				dl->AddRectFilled(curHealthPos, healthPos2, FluxColor::HealthDanger);
			}
			else if (curHealth <= (maxHealth / 2) && curHealth > (maxHealth / 3)) {
				dl->AddRectFilled(curHealthPos, healthPos2, FluxColor::HealthHalf);
			}
			else if (curHealth <= maxHealth && curHealth > (maxHealth / 2)) {
				dl->AddRectFilled(curHealthPos, healthPos2, FluxColor::HealthSafe);
			}

			constexpr float gap = 0.5f;
			dl->AddRect(ImVec2(healthPos1.x - gap, healthPos1.y - gap), ImVec2(healthPos2.x + gap * 2, healthPos2.y + gap * 2), FluxColor::Black, 0, 0, healthBarGapThickness);

			if (this->mode->isCurrentMode("Aimware")) {
				
				constexpr int healthSegments = 10;
				float healthBarWidth = healthPos2.x - healthPos1.x;
				float healthBarHeight = healthPos2.y - healthPos1.y;
				float perSegmentHeight = healthBarHeight / healthSegments;

				// Lines: Segments - 1
				for (int i = 1; i < healthSegments; i++) {
					
					float curY = healthPos1.y + perSegmentHeight * i;
					dl->AddLine(ImVec2(healthPos1.x, curY), ImVec2(healthPos1.x + healthBarWidth, curY), FluxColor::Black, healthBarGapThickness);

				}

			}

		}

	}

}
