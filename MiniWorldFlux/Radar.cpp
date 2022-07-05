#include "Radar.h"

Radar::Radar() : AbstractModule("Radar", Category::Visual) {

	this->addValue(center);
	this->addValue(showFOV);
	this->addValue(scale);

	this->scPos.x = 250;
	this->scPos.y = 225;
	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &Radar::onRenderOverlay));
}

Radar* Radar::getInstance() {
	static Radar* inst = new Radar();
	return inst;
}

void Radar::onEnabled() {

}

void Radar::onDisabled() {

}

void Radar::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;
	SinglePlayerCheck;

	ImDrawList* dl = ImGui::GetForegroundDrawList();

	Vec2 pos;
	if (this->center->getValue()) {
		
		pos = Game::getGameViewSize();
		pos.x *= 0.5f;
		pos.y *= 0.5f;
		pos.y -= 1;

	}
	else {
		
		pos.x = this->scPos.x;
		pos.y = this->scPos.y;

	}
	
	// Cross line
	float crossLength = 100;
	dl->AddLine(ImVec2(pos.x - crossLength, pos.y), ImVec2(pos.x + crossLength, pos.y), IM_COL32(18, 18, 18, 245), 1.3f);
	dl->AddLine(ImVec2(pos.x, pos.y - crossLength), ImVec2(pos.x, pos.y + crossLength), IM_COL32(18, 18, 18, 245), 1.3f);

	// FOV line
	if (this->showFOV->getValue()) {
		
		Vec2 fovLine;
		fovLine.x = crossLength * cosf(Game::thePlayer->getFOV() * 0.5f * 3.1415926f / 180);
		fovLine.y = crossLength * sinf(Game::thePlayer->getFOV() * 0.5f * 3.1415926f / 180);
		dl->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x + fovLine.x, pos.y - fovLine.y), IM_COL32(18, 18, 18, 245));
		dl->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x - fovLine.x, pos.y - fovLine.y), IM_COL32(18, 18, 18, 245));

	}

	Vec3 ePos;
	Vec2 transPos;

	for (SDK::ClientPlayer* p : Game::playerInWorld) {

		ePos.x = p->actorBody->entity->posX;
		ePos.y = p->actorBody->entity->posY;
		ePos.z = p->actorBody->entity->posZ;

		transPos = this->transformPos(Game::thePlayer->getPosition(), ePos, Game::thePlayer->getYaw(), this->scale->getValue());
		transPos.x += pos.x;
		transPos.y += pos.y;

		float distToCross = Utility::getDistance2D(transPos, pos);
		if (distToCross >= crossLength) continue;

		if (TeamCheck && Team::isSameTeam(p)) {
			dl->AddCircleFilled(ImVec2(transPos.x, transPos.y), 2.5f, IM_COL32(18, 255, 18, 245));
		}
		else {
			dl->AddCircleFilled(ImVec2(transPos.x, transPos.y), 2.5f, IM_COL32(255, 18, 18, 245));
		}
	}

}

Vec2 Radar::transformPos(Vec3 self, Vec3 target, float angle, float scale) {
	
	// 相对距离
	Vec2 relPos;
	relPos.x = target.x - self.x;
	relPos.y = target.z - self.z;

	float angleDiff = 0;
	float dis = sqrtf(relPos.x * relPos.x + relPos.y * relPos.y) * 0.01f;

	if (relPos.x >= 0 && relPos.y >= 0)
		angleDiff = atanf(relPos.x / relPos.y) * 180 / 3.1415926f - angle;
	if (relPos.x <= 0 && relPos.y >= 0)
		angleDiff = 360 - atanf(abs(relPos.x) / relPos.y) * 180 / 3.1415926f - angle;
	if (relPos.x <= 0 && relPos.y <= 0)
		angleDiff = 270 - atanf(abs(relPos.y) / abs(relPos.x)) * 180 / 3.1415926f - angle;
	if (relPos.x >= 0 && relPos.y <= 0)
		angleDiff = 180 - atanf(relPos.x / abs(relPos.y)) * 180 / 3.1415926f - angle;

	relPos.x = dis * sinf(angleDiff * 3.14f / 180);
	relPos.y = dis * cosf(angleDiff * 3.14f / 180);

	// 屏幕的坐标系是向下为Y轴正方向
	// 而雷达的坐标系则是向上为Y轴正方向
	// 所以结果的Y要乘-1，也就是旋转180°
	relPos.y *= (-1);
	relPos.x /= scale;
	relPos.y /= scale;

	return relPos;

}
