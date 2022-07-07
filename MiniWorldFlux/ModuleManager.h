#pragma once
#include <iostream>
#include <vector>
#include "AbstractModule.h"
#include "Utility.h"

#define ToBaseModule(_Mod) reinterpret_cast<AbstractModule*>(_Mod)
#define ToDirectModule(_Impl, _Mod) reinterpret_cast<_Impl*>(_Mod)

typedef void* HMOD;

class ModuleManager {
	
public:

	static ModuleManager& getInstance();

	template<class MODCLASS>
	void addModule(MODCLASS* mod);

	template <class MODCLASS>
	MODCLASS* getModule(std::string modName);

	void getModule(bool enabled, std::vector<HMOD>* out_modules);
	void getModule(Category c, std::vector<HMOD>* out_modules);
	std::vector<HMOD> getModules();

	ModuleManager(ModuleManager&&) = delete;
	ModuleManager(const ModuleManager&) = delete;
	ModuleManager& operator=(const ModuleManager&) = delete;

private:

	std::vector<HMOD> modules;

	ModuleManager();
	~ModuleManager() = default;
};

template<class MODCLASS>
void ModuleManager::addModule(MODCLASS* mod) {
	AbstractModule* module = ToBaseModule(mod);
	this->modules.push_back(module);

	LOGGER << Logger::format(L"Module %hs Initialized.", L"ModuleManager.h", LogRank::DEBUG, module->getName().c_str());
}

template<class MODCLASS>
MODCLASS* ModuleManager::getModule(std::string modName) {

	for (auto iter = this->modules.cbegin(); iter < this->modules.cend(); iter++) {

		if (Utility::compareStringIgnoreCase(ToBaseModule(*iter)->getName(), modName))
			return ToDirectModule(MODCLASS, *iter);
	}
	
	return nullptr;
}


