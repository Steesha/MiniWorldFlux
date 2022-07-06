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
	
	constexpr float maskOffsetX = 330;
	constexpr float maskOffsetY = 15;
	constexpr float maskWidth = 150;

	Block idMaskBlock;
	
	Vec2 view = Game::getGameViewSize();
	idMaskBlock.x = view.x - maskOffsetX;
	idMaskBlock.y = view.y - maskOffsetY;
	idMaskBlock.width = maskWidth;
	idMaskBlock.height = maskOffsetY;
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(idMaskBlock.x, idMaskBlock.y), ImVec2(idMaskBlock.x + idMaskBlock.width, idMaskBlock.y + idMaskBlock.height), FluxColor::Gray);
	if (ClickGui::getInstance()->showUIBB) Renderer::drawBlockBoundingBox(&idMaskBlock);
	
}


