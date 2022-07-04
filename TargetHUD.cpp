#include "TargetHUD.h"

TargetHUD::TargetHUD() : AbstractModule("TargetHUD", Category::Visual) {

	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &TargetHUD::onRenderOverlay));
}

TargetHUD* TargetHUD::getInstance() {
	static TargetHUD* inst = new TargetHUD();
	return inst;
}

void TargetHUD::onEnabled() {

}

void TargetHUD::onDisabled() {

}

void TargetHUD::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;
	SinglePlayerCheck;
	if (ClickGui::getInstance()->getToggle()) return;

	static float panelOffsetX = 100;
	static float panelOffsetY = 30;
	static float contentOffsetX = 75;
	static float contentOffsetY = 5;
	static float contentInterval = 20;
	static float fontSize = 14;

/*
#ifdef _DEBUG
	ImGui::Begin("TargetHUD");

	ImGui::SliderFloat("Panel Offset X", &panelOffsetX, 0, 500);
	ImGui::SliderFloat("Panel Offset Y", &panelOffsetY, 0, 500);
	ImGui::SliderFloat("Content Offset X", &contentOffsetX, 0, 260);
	ImGui::SliderFloat("Content Offset Y", &contentOffsetY, 0, 150);
	ImGui::SliderFloat("Content Interval", &contentInterval, 0, 30);
	ImGui::SliderFloat("Font Size", &fontSize, 0, 30);

	ImGui::End();
#endif
*/
	
	this->target = Aimbot::getInstance()->getTarget();
	if (target == nullptr) return;

	ImDrawList* dl = ImGui::GetForegroundDrawList();
	Vec2 view = Game::getGameViewSize();
	view.x *= 0.5f;
	view.y *= 0.5f;

	// Background
	struct Block panelBlock;
	panelBlock.x = view.x + panelOffsetX;
	panelBlock.y = view.y + panelOffsetY;
	panelBlock.width = 250;
	panelBlock.height = 64;
	dl->AddRectFilled(ImVec2(panelBlock.x, panelBlock.y), ImVec2(panelBlock.x + panelBlock.width, panelBlock.y + panelBlock.height), FluxColor::ValueModeBackground, 8);

	// Content
	auto info = Game::playerInfo.find(target->uid);
	if (info == Game::playerInfo.end()) return;

	float curY = 5;
	SDK::PlayerInfo* targetInfo = info->second;
	dl->AddRectFilled(ImVec2(panelBlock.x + 5, panelBlock.y + 5), ImVec2(panelBlock.x + 60, panelBlock.y + 60), FluxColor::ValueModeForeground, 8);

	float curHealth = this->target->playerAttribuLua->currentHealth;
	float maxHealth = this->target->playerAttribuLua->maxHealth;

	char buffer[128];
	RtlZeroMemory(buffer, 128);
	int precent = (curHealth <= 1 && curHealth > 0 ? 1 : static_cast<int>(curHealth / maxHealth * 100));
	sprintf(buffer, "%s HP: %d%%", targetInfo->name, precent);
	dl->AddText(Client::chinese, fontSize, ImVec2(panelBlock.x + contentOffsetX, panelBlock.y + contentOffsetY + curY), FluxColor::White, buffer);
	curY += contentInterval;

	float progressWidth = panelBlock.width - contentOffsetX - 5;

	float healthWidth = Utility::map(curHealth, 0, maxHealth, 0, progressWidth);
	dl->AddRectFilled(ImVec2(panelBlock.x + contentOffsetX, panelBlock.y + contentOffsetY + curY), ImVec2(panelBlock.x + contentOffsetX + healthWidth, panelBlock.y + contentOffsetY + curY + 8), FluxColor::TargetHUDHealth, 8);
	curY += contentInterval;

	float curHunger = this->target->playerAttribuLua->currentHunger;
	float maxHunger = this->target->playerAttribuLua->maxHunger;
	float hungerWidth = Utility::map(curHunger, 0, maxHunger, 0, progressWidth);
	dl->AddRectFilled(ImVec2(panelBlock.x + contentOffsetX, panelBlock.y + contentOffsetY + curY), ImVec2(panelBlock.x + contentOffsetX + progressWidth, panelBlock.y + contentOffsetY + curY + 8), FluxColor::TargetHUDHunger, 8);

	if (ClickGui::getInstance()->showUIBB) Renderer::drawBlockBoundingBox(&panelBlock);

}
