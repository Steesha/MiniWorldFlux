#include "pch.h"
#include "ModuleManager.h"

ModuleManager::ModuleManager() {
	
}

ModuleManager& ModuleManager::getInstance() {
	static ModuleManager instance;
	return instance;
}

void ModuleManager::getModule(Category c, std::vector<HMOD>* out_modules) {
	
	out_modules->clear();
	for (auto iter = this->modules.cbegin(); iter < this->modules.cend(); iter++) {
		if (ToBaseModule(*iter)->getCategory() == c)
			out_modules->push_back(*iter);
	}
}

void ModuleManager::getModule(bool enabled, std::vector<HMOD>* out_modules) {

	out_modules->clear();
	for (auto iter = this->modules.cbegin(); iter < this->modules.cend(); iter++) {
		if (ToBaseModule(*iter)->getToggle() == enabled)
			out_modules->push_back(*iter);
	}
}

std::vector<HMOD> ModuleManager::getModules() {
	return this->modules;
}
