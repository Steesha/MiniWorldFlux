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
	
	constexpr float maskOffsetY = 17;
	constexpr float yPercent = 0.025f;

	Vec2 view = Game::getGameViewSize();
	Block idMaskBlock;
	idMaskBlock.x = 0;
	idMaskBlock.y = view.y - view.y * yPercent;
	idMaskBlock.width = view.x;
	idMaskBlock.height = view.y * yPercent;
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(0, idMaskBlock.y), ImVec2(idMaskBlock.width, idMaskBlock.y + idMaskBlock.height), FluxColor::Gray);
	if (ClickGui::getInstance()->showUIBB) Renderer::drawBlockBoundingBox(&idMaskBlock);
	
}


