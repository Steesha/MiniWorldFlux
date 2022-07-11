#include "pch.h"
#include "IDProtection.h"

IDProtection::IDProtection() : AbstractModule("IDProtection", Category::Visual) {

	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &IDProtection::onRenderOverlay));
}

IDProtection* IDProtection::getInstance() {
	static IDProtection* inst = new IDProtection();
	return inst;
}

void IDProtection::onEnabled() {

}

void IDProtection::onDisabled() {

}

void IDProtection::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;

	/*
	static int targetPtr = 0;
	ImGui::Begin("Attack Entity");
	ImGui::InputInt("Target Address", &targetPtr);
	if (ImGui::Button("Call")) {
		if (targetPtr != 0) {
			Game::thePlayer->getObject()->attackEntity(targetPtr);
			LOG(L"IDProtection.cpp", L"Attack call called.", DEBUG);
		}
	}
	if (ImGui::Button("Jump")) {
		Game::thePlayer->getObject()->setJumping(true);
	}
	ImGui::End();
	*/
	
	constexpr float maskOffsetY = 17;

	Vec2 view = Game::getGameViewSize();
	Block idMaskBlock;
	idMaskBlock.x = 0;
	idMaskBlock.y = view.y - maskOffsetY;
	idMaskBlock.width = view.x;
	idMaskBlock.height = maskOffsetY;
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(0, idMaskBlock.y), ImVec2(idMaskBlock.width, idMaskBlock.y + idMaskBlock.height), FluxColor::Gray);
	if (ClickGui::getInstance()->showUIBB) Renderer::drawBlockBoundingBox(&idMaskBlock);
	
}


