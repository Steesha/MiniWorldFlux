#include "pch.h"
#include "ESP.h"

ESP::ESP() : AbstractModule("ESP", Category::Visual) {

	this->addValue(this->health);

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

		ImVec2 rectPos1 = { camera.x - rectWidth / 2, camera.z + 6 };
		ImVec2 rectPos2 = { rectPos1.x + rectWidth, rectPos1.y + rectHeight + 6 };

		float lineLength = 8;

		ImVec2 rightTop(rectPos1.x + rectWidth, rectPos1.y);
		ImVec2 leftBottom(rectPos2.x - rectWidth, rectPos2.y);

		// Health rect
		float curHealth = p->playerAttribuLua->currentHealth;
		float maxHealth = p->playerAttribuLua->maxHealth;
		ImVec2 healthPos1(rectPos1.x - 10, rectPos1.y);
		ImVec2 healthPos2(rectPos1.x - 5, rectPos1.y + rectHeight);		
		float healthHeight = Utility::map(curHealth, 0, maxHealth, healthPos2.y, healthPos1.y);
		ImVec2 curHealthPos(healthPos1.x + 1, healthHeight + 1);

		// »æÖÆ
		ImDrawList* dl = ImGui::GetForegroundDrawList();
		if (TeamCheck && Team::isSameTeam(p)) {
			
			// Left Top
			dl->AddLine(rectPos1, ImVec2(rectPos1.x + lineLength, rectPos1.y), IM_COL32(18, 255, 18, 245), 1.8f);
			dl->AddLine(rectPos1, ImVec2(rectPos1.x, rectPos1.y + lineLength), IM_COL32(18, 255, 18, 245), 1.8f);

			// Right Top
			dl->AddLine(rightTop, ImVec2(rightTop.x - lineLength, rightTop.y), IM_COL32(18, 255, 18, 245), 1.8f);
			dl->AddLine(rightTop, ImVec2(rightTop.x, rightTop.y + lineLength), IM_COL32(18, 255, 18, 245), 1.8f);

			// Left Bottom
			dl->AddLine(leftBottom, ImVec2(leftBottom.x + lineLength, leftBottom.y), IM_COL32(18, 255, 18, 245), 1.8f);
			dl->AddLine(leftBottom, ImVec2(leftBottom.x, leftBottom.y - lineLength), IM_COL32(18, 255, 18, 245), 1.8f);

			// Right Bottom
			dl->AddLine(rectPos2, ImVec2(rectPos2.x - lineLength, rectPos2.y), IM_COL32(18, 255, 18, 245), 1.8f);
			dl->AddLine(rectPos2, ImVec2(rectPos2.x, rectPos2.y - lineLength), IM_COL32(18, 255, 18, 245), 1.8f);	

		}
		else {

			// Left Top
			dl->AddLine(rectPos1, ImVec2(rectPos1.x + lineLength, rectPos1.y), IM_COL32(255, 18, 18, 245), 1.8f);
			dl->AddLine(rectPos1, ImVec2(rectPos1.x, rectPos1.y + lineLength), IM_COL32(255, 18, 18, 245), 1.8f);

			// Right Top
			dl->AddLine(rightTop, ImVec2(rightTop.x - lineLength, rightTop.y), IM_COL32(255, 18, 18, 245), 1.8f);
			dl->AddLine(rightTop, ImVec2(rightTop.x, rightTop.y + lineLength), IM_COL32(255, 18, 18, 245), 1.8f);

			// Left Bottom
			dl->AddLine(leftBottom, ImVec2(leftBottom.x + lineLength, leftBottom.y), IM_COL32(255, 18, 18, 245), 1.8f);
			dl->AddLine(leftBottom, ImVec2(leftBottom.x, leftBottom.y - lineLength), IM_COL32(255, 18, 18, 245), 1.8f);

			// Right Bottom
			dl->AddLine(rectPos2, ImVec2(rectPos2.x - lineLength, rectPos2.y), IM_COL32(255, 18, 18, 245), 1.8f);
			dl->AddLine(rectPos2, ImVec2(rectPos2.x, rectPos2.y - lineLength), IM_COL32(255, 18, 18, 245), 1.8f);

		}
		
		// Health
		if (this->health->getValue()) {
		
			if (curHealth <= (maxHealth / 3)) {
				dl->AddRectFilled(curHealthPos, healthPos2, IM_COL32(255, 10, 10, 245));
				dl->AddRect(healthPos1, healthPos2, IM_COL32(10, 10, 10, 255));
			}
			else if (curHealth <= (maxHealth / 2) && curHealth > (maxHealth / 3)) {
				dl->AddRectFilled(curHealthPos, healthPos2, IM_COL32(255, 255, 10, 245));
				dl->AddRect(healthPos1, healthPos2, IM_COL32(10, 10, 10, 255));
			}
			else if (curHealth <= maxHealth && curHealth > (maxHealth / 2)) {
				dl->AddRectFilled(curHealthPos, healthPos2, IM_COL32(10, 255, 10, 245));
				dl->AddRect(healthPos1, healthPos2, IM_COL32(10, 10, 10, 255));
			}

		}

	}

}
