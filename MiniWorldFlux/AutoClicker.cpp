#include "pch.h"
#include "AutoClicker.h"

AutoClicker::AutoClicker() : AbstractModule("AutoClicker", Category::Combat) {

	this->addValue(this->cps);
	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &AutoClicker::onRenderOverlay));
}

AutoClicker* AutoClicker::getInstance() {
	static AutoClicker* inst = new AutoClicker();
	return inst;
}

void AutoClicker::onEnabled() {
	this->cpsTimer.reset();
}

void AutoClicker::onDisabled() {

}

void AutoClicker::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;
	if (ClickGui::getInstance()->getToggle()) return;
	if (GetForegroundWindow() != Client::wndGame) return;

	if (Client::rendererIO->MouseDownDuration[ImGuiMouseButton_Middle] > 0) {

		if (this->cpsTimer.elapsed(1000 / this->cps->getValueLong())) {
			Simulator::mlclick(20);
			this->cpsTimer.reset();
		}

	}

}
