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
	
	static float maskOffsetX = 330;
	static float maskOffsetY = 15;
	static float maskWidth = 150;

	Block idMaskBlock;
	idMaskBlock.x = Utility::width() - maskOffsetX;
	idMaskBlock.y = Utility::height() - maskOffsetY;
	idMaskBlock.width = maskWidth;
	idMaskBlock.height = maskOffsetY;
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(idMaskBlock.x, idMaskBlock.y), ImVec2(idMaskBlock.x + idMaskBlock.width, idMaskBlock.y + idMaskBlock.height), FluxColor::Gray);
	if (ClickGui::getInstance()->showUIBB) Renderer::drawBlockBoundingBox(&idMaskBlock);
	
}


