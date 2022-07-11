#pragma once
#include "pch.h"
#include "AbstractModule.h"
#include "ImGuiHeader.h"
#include "EventManager.h"
#include "Client.h"
#include "Colors.h"
#include "Icon.h"

class ClickGui : public AbstractModule {

public:

	// Show UI Bounding Box
	bool showUIBB = true;

	// Key Binding
	bool bindingKey = false;
	AbstractModule* bindingModule = nullptr;

	static ClickGui* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

	void renderInfoPanel();
	void renderMainPanel();
	void renderChangeLog();

	void startBindKey(AbstractModule* target);
	void endBindKey();

private:

	bool changelog = false;
	std::vector<std::string> changelogItems;

	float modulePanelScrollY = 0;
	Category curCategory = Category::Combat;
	int curModule = 0;

	bool dragging = false;
	float clickguiX = 300;
	float clickguiY = 120;
	float dragOffsetX = 0;
	float dragOffsetY = 0;

	void selectCategory(Category category);
	void selectModule(int mod);

	ClickGui();
	~ClickGui() = default;
	ClickGui(ClickGui&&) = delete;
	ClickGui(const ClickGui&) = delete;
	ClickGui& operator=(const ClickGui&) = delete;
};

