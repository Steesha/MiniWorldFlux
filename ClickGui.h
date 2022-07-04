#pragma once
#include "AbstractModule.h"
#include "ImGuiHeader.h"
#include "EventManager.h"
#include "Client.h"
#include "Colors.h"
#include "Icon.h"

class ClickGui : public AbstractModule {

public:

	// Show UI Bounding Box
	bool showUIBB = false;

	// Key Binding
	bool bindingKey = false;
	AbstractModule* bindingModule = nullptr;

	static ClickGui* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

	void renderInfoPanel();
	void renderMainPanel();

	void startBindKey(AbstractModule* target);
	void endBindKey();

private:

	float modulePanelScrollY = 0;

	Category curCategory = Category::Combat;
	int curModule = 0;

	void selectCategory(Category category);
	void selectModule(int mod);

	ClickGui();
	~ClickGui() = default;
	ClickGui(ClickGui&&) = delete;
	ClickGui(const ClickGui&) = delete;
	ClickGui& operator=(const ClickGui&) = delete;
};

