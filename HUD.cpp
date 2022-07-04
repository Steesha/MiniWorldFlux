#include "HUD.h"

HUD::HUD() : AbstractModule("HUD", Category::Visual) {

	this->addValue(this->rainbow);
	this->addValue(this->alOffsetY);
	this->addValue(this->mode);

	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &HUD::onRenderOverlay));
}

HUD* HUD::getInstance() {
	static HUD* inst = new HUD();
	return inst;
}

void HUD::onEnabled() {

	this->enabledMods.clear();
}

void HUD::onDisabled() {

	this->enabledMods.clear();
}

void HUD::onRenderOverlay() {
	ToggleCheck;

	ImDrawList* dl = ImGui::GetForegroundDrawList();
	
	this->enabledMods.clear();
	ModuleManager::getInstance().getModule(true, &(this->enabledMods));
	std::sort(this->enabledMods.begin(), this->enabledMods.end(), EnabledListSorter());

	Block enabledListBlock;
	enabledListBlock.x = 20;
	enabledListBlock.y = 300 + this->alOffsetY->getValue();
	enabledListBlock.width = 0;
	enabledListBlock.height = 0;

	int i = 0;
	for (HMOD m : this->enabledMods) {
		AbstractModule* mod = ToBaseModule(m);
		++i;

		dl->AddText(Client::fluxFont, 23.5f, ImVec2(enabledListBlock.x + 2, enabledListBlock.y + enabledListBlock.height + 2), FluxColor::Gray, mod->getName().c_str());
		if (this->rainbow->getValue())
			dl->AddText(Client::fluxFont, 23.5f, ImVec2(enabledListBlock.x, enabledListBlock.y + enabledListBlock.height), Utility::rainbow(50, 100 * i), mod->getName().c_str());
		else	
			dl->AddText(Client::fluxFont, 23.5f, ImVec2(enabledListBlock.x, enabledListBlock.y + enabledListBlock.height), FluxColor::White, mod->getName().c_str());
		if (Utility::getStringLength(mod->getName().c_str(), 23.5f) > enabledListBlock.width) enabledListBlock.width = Utility::getStringLength(mod->getName().c_str(), 23.5f);
		enabledListBlock.height += 22;

	}
	if (ClickGui::getInstance()->showUIBB) Renderer::drawBlockBoundingBox(&enabledListBlock);

}

bool EnabledListSorter::operator()(HMOD m1, HMOD m2) {
	AbstractModule* mod1 = ToBaseModule(m1);
	AbstractModule* mod2 = ToBaseModule(m2);
	return strlen(mod1->getName().c_str()) > strlen(mod2->getName().c_str());
}
