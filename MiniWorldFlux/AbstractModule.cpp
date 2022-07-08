#include "pch.h"
#include "AbstractModule.h"
AbstractModule::AbstractModule(std::string modName, Category modCategory) : name(modName), category(modCategory), i_toggle(false), key(Simulator::KEY_NONE) {

}

AbstractModule::AbstractModule(std::string modName, Category modCategory, unsigned char keyCode) : name(modName), category(modCategory), i_toggle(false), key(keyCode) {

}

std::string AbstractModule::getName() {
	return this->name;
}

bool AbstractModule::getToggle() {
	return this->i_toggle;
}

void AbstractModule::setToggle(bool _New) {

	if (_New == this->i_toggle) return;
	this->i_toggle = _New;
	this->onToggled();
}

void AbstractModule::enable() {
	this->setToggle(true);
}

void AbstractModule::disable() {
	this->setToggle(false);
}

Category AbstractModule::getCategory() {
	return this->category;
}

void AbstractModule::toggle() {
	this->i_toggle = !this->i_toggle;
	this->onToggled();
}

void AbstractModule::onToggled() {

	char buffer[128] = { 0 };
	RtlZeroMemory(buffer, 128);

	if (this->i_toggle) {
		this->onEnabled();
		sprintf(buffer, "%s Enabled.", this->getName().c_str());
		if (this->getName() != "ClickGui")
			NotificationManager::getInstance().notify(std::string(buffer), NotiLevel::INFO, 3);
	}
	else {
		this->onDisabled();
		sprintf(buffer, "%s Disabled.", this->getName().c_str());
		if (this->getName() != "ClickGui")
			NotificationManager::getInstance().notify(std::string(buffer), NotiLevel::INFO, 3);
	}
}

Value* AbstractModule::getValue(std::string name) {
	for (Value* v : this->values) {
		if (stricmp(v->getName().c_str(), name.c_str()) == 0)
			return v;
	}
	return nullptr;
}

std::vector<Value*> AbstractModule::getValues() {
	return this->values;
}

void AbstractModule::addValue(Value* v) {
	this->values.push_back(v);
}

unsigned char AbstractModule::getKey() {
	return this->key;
}

void AbstractModule::setKey(unsigned char newKey) {
	if (newKey == VK_RETURN)
		this->key = Simulator::KEY_NONE;
	else
		this->key = newKey;
}
