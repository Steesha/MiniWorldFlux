#include "pch.h"
#include "ClickGui.h"

ClickGui::ClickGui() : AbstractModule("ClickGui", Category::Visual) {

	EventManager::getInstance().reg(Events::EventRenderOverlay, MakeHandler(this, &ClickGui::onRenderOverlay));
	EventManager::getInstance().reg(Events::EventOpenClickGui, MakeHandler(this, &ClickGui::enable));
	EventManager::getInstance().reg(Events::EventCloseClickGui, MakeHandler(this, &ClickGui::disable));

	this->changelogItems.push_back("[Aplha v0.1.0]");
	this->changelogItems.push_back("由于刚发布的原因，需介绍的款项太多，请到Telegram频道查看详细使用说明");

	this->changelogItems.push_back("");

	this->changelogItems.push_back("[Alpha v0.1.1]");
	this->changelogItems.push_back("[Fix] 感谢Tubitu大佬提供的修复大部分人ui乱码的解决方案");
	this->changelogItems.push_back("[Fix] 修复了ClickGui拖动不流畅的问题");
	this->changelogItems.push_back("[Fix] 修复了ClickGui处于打开状态时部分按键仍会响应到游戏内的问题");
	this->changelogItems.push_back("[Fix] FakeMessager更名为FakeMessenger");
	this->changelogItems.push_back("[+] HUD Module增加了自定义ArrayList位置的选项");

	this->changelogItems.push_back("");

	this->changelogItems.push_back("[Alpha v0.1.2]");
	this->changelogItems.push_back("[Fix] 修复FakeMessenger不能重置回自己发言的状态的Bug");
	this->changelogItems.push_back("[Fix] 修复了窗口大小对IDProtection的影响");
	this->changelogItems.push_back("[Fix] 修复了自己创建房间时或者进入别人房间时会崩溃的Bug");
	this->changelogItems.push_back("[Fix] 修复了ESP Module总会漏掉一个人的Bug");

	this->changelogItems.push_back("");

	this->changelogItems.push_back("[Alpha v0.1.3]");
	this->changelogItems.push_back("[Feat] 增加Velocity Module，Memory模式是完全无击退，Force则仍会向后弹一段很小的距离");
	this->changelogItems.push_back("[Feat] 增加FakeHeight Module，允许您随意调整人物摄像机的高度而本身不受影响，可自行调整高度");
	this->changelogItems.push_back("[Modify] FasterSpeed更名为Speed，后续考虑加入BHop");
	this->changelogItems.push_back("[Feat] 增加NoCD Module, 技能无冷却");
	this->changelogItems.push_back("[Feat] 增加FastSkill Module, 无需蓄力即可使用技能");
	this->changelogItems.push_back("[Feat] 增加Flash Module , 右键可向前闪现");
	this->changelogItems.push_back("[Feat] 增加FreeMove Module, 游戏未开始也可以自由移动");

}

ClickGui* ClickGui::getInstance() {
	
	static ClickGui* instance = new ClickGui();
	return instance;
}

void ClickGui::onEnabled() {
	
}

void ClickGui::onDisabled() {

}

void ClickGui::onRenderOverlay() {

#ifdef _DEBUG
	static int xPos = 0;
	static int yPos = 0;
	static int zPos = 0;
	static int targetPtr = 0;

	ImGui::Begin("Calls");
	ImGui::InputInt("X", &xPos);
	ImGui::InputInt("Y", &yPos);
	ImGui::InputInt("Z", &zPos);
	ImGui::InputInt("Target", &targetPtr);
	if (ImGui::Button("Pos")) {
		int res = Game::thePlayer->getObject()->playerLocoMotion->setPosition(xPos, yPos, zPos);
		LOGGER << Logger::format(L"SetPosition Result: %d", L"Clickgui.cpp", LogRank::DEBUG, res);
	}
	if (ImGui::Button("Attack")) {
		Game::thePlayer->getObject()->attackEntity(targetPtr);
		LOGGER << Logger::format(L"Attack Entity called.", L"Clickgui.cpp", LogRank::DEBUG);
	}
	ImGui::End();
#endif
	
	this->renderInfoPanel();
	if (this->changelog)
		this->renderChangeLog();
	ToggleCheck;
	this->renderMainPanel();

}

void ClickGui::renderMainPanel() {

	ImDrawList* dl = ImGui::GetBackgroundDrawList();

#pragma region Background

	// 840*15
	struct Block dragableBlock;
	dragableBlock.x = this->clickguiX;
	dragableBlock.y = this->clickguiY;
	dragableBlock.width = 840;
	dragableBlock.height = 30;
	dl->AddRectFilled(ImVec2(dragableBlock.x, dragableBlock.y), ImVec2(dragableBlock.x + dragableBlock.width, dragableBlock.y + dragableBlock.height), FluxColor::Orange, 5);
	if (this->showUIBB) Renderer::drawBlockBoundingBox(&dragableBlock);

	// 处理拖动
	if (Renderer::isBlockHovered(&dragableBlock)) {
		if ((!this->dragging) && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
			this->dragging = true;
			this->dragOffsetX = Client::rendererIO->MousePos.x - dragableBlock.x;
			this->dragOffsetY = Client::rendererIO->MousePos.y - dragableBlock.y;
		}
	}

	if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
		this->dragging = false;
	}

	if (this->dragging && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
		this->clickguiX = Client::rendererIO->MousePos.x - this->dragOffsetX;
		this->clickguiY = Client::rendererIO->MousePos.y - this->dragOffsetY;
	}

	// 840*590
	struct Block panelBlock;
	panelBlock.x = dragableBlock.x;
	panelBlock.y = dragableBlock.y + dragableBlock.height * 0.3f;
	panelBlock.width = 840;
	panelBlock.height = 590;
	dl->AddRectFilled(ImVec2(panelBlock.x, panelBlock.y), ImVec2(panelBlock.x + panelBlock.width, panelBlock.y + panelBlock.height), FluxColor::MainPanelBackground);
	if (this->showUIBB) Renderer::drawBlockBoundingBox(&panelBlock);

#pragma endregion

#pragma region CategoryPanel

	// 840*20
	struct Block categoryPanelBlock;
	categoryPanelBlock.x = panelBlock.x;
	categoryPanelBlock.y = panelBlock.y;
	categoryPanelBlock.width = 840;
	categoryPanelBlock.height = 90;
	if (this->showUIBB) Renderer::drawBlockBoundingBox(&categoryPanelBlock);

	// Logo
	struct Block logoBlock;
	logoBlock.x = categoryPanelBlock.x;
	logoBlock.y = categoryPanelBlock.y;
	logoBlock.width = 190;
	logoBlock.height = categoryPanelBlock.height;
	dl->AddText(Client::fluxIcon, 35, ImVec2(logoBlock.x + 45, logoBlock.y + 30), FluxColor::Logo, FluxIcon::Logo);
	dl->AddText(Client::fluxFont, 25, ImVec2(categoryPanelBlock.x + 95, categoryPanelBlock.y + 35), FluxColor::Logo, "Flux");
	if (Renderer::isBlockClicked(&logoBlock)) {
		this->disable();
		this->changelog = true;
	}
	if (this->showUIBB) Renderer::drawBlockBoundingBox(&logoBlock);

	struct Block categoriesBlock;
	categoriesBlock.x = logoBlock.x + logoBlock.width;
	categoriesBlock.y = logoBlock.y;
	categoriesBlock.width = categoryPanelBlock.width - logoBlock.width;
	categoriesBlock.height = categoryPanelBlock.height;
	if (this->showUIBB) Renderer::drawBlockBoundingBox(&categoriesBlock);

	float categoryIconSize = 18;
	float categoryTextSize = 20;

	struct Block combatBlock;
	combatBlock.x = categoriesBlock.x;
	combatBlock.y = categoriesBlock.y;
	combatBlock.width = 125;
	combatBlock.height = categoriesBlock.height;
	if (this->curCategory == Category::Combat) {
		dl->AddText(Client::fluxIcon, categoryIconSize, ImVec2(combatBlock.x + 25, combatBlock.y + 40), FluxColor::ItemSelected, FluxIcon::Combat);
		dl->AddText(Client::fluxFont, categoryTextSize, ImVec2(combatBlock.x + 52, combatBlock.y + 40), FluxColor::ItemSelected, "Combat");
	}
	else {
		dl->AddText(Client::fluxIcon, categoryIconSize, ImVec2(combatBlock.x + 25, combatBlock.y + 40), FluxColor::ItemNonSelected, FluxIcon::Combat);
		dl->AddText(Client::fluxFont, categoryTextSize, ImVec2(combatBlock.x + 52, combatBlock.y + 40), FluxColor::ItemNonSelected, "Combat");
	}
	if (this->showUIBB) Renderer::drawBlockBoundingBox(&combatBlock);
	if (Renderer::isBlockClicked(&combatBlock)) this->selectCategory(Category::Combat);

	struct Block movementBlock;
	movementBlock.x = combatBlock.x + combatBlock.width;
	movementBlock.y = combatBlock.y;
	movementBlock.width = 110;
	movementBlock.height = categoriesBlock.height;
	if (this->curCategory == Category::Movement) {
		dl->AddText(Client::fluxIcon, categoryIconSize, ImVec2(movementBlock.x + 5, movementBlock.y + 40), FluxColor::ItemSelected, FluxIcon::Movement);
		dl->AddText(Client::fluxFont, categoryTextSize, ImVec2(movementBlock.x + 30, movementBlock.y + 40), FluxColor::ItemSelected, "Movement");
	}
	else {
		dl->AddText(Client::fluxIcon, categoryIconSize, ImVec2(movementBlock.x + 5, movementBlock.y + 40), FluxColor::ItemNonSelected, FluxIcon::Movement);
		dl->AddText(Client::fluxFont, categoryTextSize, ImVec2(movementBlock.x + 30, movementBlock.y + 40), FluxColor::ItemNonSelected, "Movement");
	}
	if (this->showUIBB) Renderer::drawBlockBoundingBox(&movementBlock);
	if (Renderer::isBlockClicked(&movementBlock)) this->selectCategory(Category::Movement);

	struct Block visualBlock;
	visualBlock.x = movementBlock.x + movementBlock.width;
	visualBlock.y = movementBlock.y;
	visualBlock.width = 85;
	visualBlock.height = categoriesBlock.height;
	if (this->curCategory == Category::Visual) {
		dl->AddText(Client::fluxIcon, categoryIconSize, ImVec2(visualBlock.x + 10, visualBlock.y + 40), FluxColor::ItemSelected, FluxIcon::Visual);
		dl->AddText(Client::fluxFont, categoryTextSize, ImVec2(visualBlock.x + 35, visualBlock.y + 40), FluxColor::ItemSelected, "Visual");
	}
	else {
		dl->AddText(Client::fluxIcon, categoryIconSize, ImVec2(visualBlock.x + 10, visualBlock.y + 40), FluxColor::ItemNonSelected, FluxIcon::Visual);
		dl->AddText(Client::fluxFont, categoryTextSize, ImVec2(visualBlock.x + 35, visualBlock.y + 40), FluxColor::ItemNonSelected, "Visual");
	}
	if (this->showUIBB) Renderer::drawBlockBoundingBox(&visualBlock);
	if (Renderer::isBlockClicked(&visualBlock)) this->selectCategory(Category::Visual);

	struct Block playerBlock;
	playerBlock.x = visualBlock.x + visualBlock.width;
	playerBlock.y = visualBlock.y;
	playerBlock.width = 80;
	playerBlock.height = categoriesBlock.height;
	if (this->curCategory == Category::Player) {
		dl->AddText(Client::fluxIcon, categoryIconSize, ImVec2(playerBlock.x + 10, playerBlock.y + 40), FluxColor::ItemSelected, FluxIcon::Player);
		dl->AddText(Client::fluxFont, categoryTextSize, ImVec2(playerBlock.x + 35, playerBlock.y + 40), FluxColor::ItemSelected, "Player");
	}
	else {
		dl->AddText(Client::fluxIcon, categoryIconSize, ImVec2(playerBlock.x + 10, playerBlock.y + 40), FluxColor::ItemNonSelected, FluxIcon::Player);
		dl->AddText(Client::fluxFont, categoryTextSize, ImVec2(playerBlock.x + 35, playerBlock.y + 40), FluxColor::ItemNonSelected, "Player");
	}
	if (this->showUIBB) Renderer::drawBlockBoundingBox(&playerBlock);
	if (Renderer::isBlockClicked(&playerBlock)) this->selectCategory(Category::Player);

	struct Block worldBlock;
	worldBlock.x = playerBlock.x + playerBlock.width;
	worldBlock.y = playerBlock.y;
	worldBlock.width = 100;
	worldBlock.height = categoriesBlock.height;
	if (this->curCategory == Category::World) {
		dl->AddText(Client::fluxIcon, categoryIconSize, ImVec2(worldBlock.x + 15, worldBlock.y + 40), FluxColor::ItemSelected, FluxIcon::World);
		dl->AddText(Client::fluxFont, categoryTextSize, ImVec2(worldBlock.x + 40, worldBlock.y + 40), FluxColor::ItemSelected, "World");
	}
	else {
		dl->AddText(Client::fluxIcon, categoryIconSize, ImVec2(worldBlock.x + 15, worldBlock.y + 40), FluxColor::ItemNonSelected, FluxIcon::World);
		dl->AddText(Client::fluxFont, categoryTextSize, ImVec2(worldBlock.x + 40, worldBlock.y + 40), FluxColor::ItemNonSelected, "World");
	}
	if (this->showUIBB) Renderer::drawBlockBoundingBox(&worldBlock);
	if (Renderer::isBlockClicked(&worldBlock)) this->selectCategory(Category::World);

	// Seperator
	dl->AddLine(ImVec2(categoryPanelBlock.x, categoryPanelBlock.y + categoryPanelBlock.height), ImVec2(categoryPanelBlock.x + categoryPanelBlock.width - 2, categoryPanelBlock.y + categoryPanelBlock.height), FluxColor::Gray, 2.5f);

#pragma endregion

#pragma region ModulePanel

	struct Block modulePanelBlock;
	modulePanelBlock.x = categoryPanelBlock.x;
	modulePanelBlock.y = categoryPanelBlock.y + categoryPanelBlock.height + 2;
	modulePanelBlock.width = 200;
	modulePanelBlock.height = panelBlock.height - categoryPanelBlock.height;

	float wheel = Client::rendererIO->MouseWheel;
	if (wheel != 0 && Renderer::isBlockHovered(&modulePanelBlock))
		modulePanelScrollY += wheel * 25;
	
	std::vector<HMOD> curCategoryModules;
	ModuleManager::getInstance().getModule(this->curCategory, &curCategoryModules);
	if (curCategoryModules.empty()) return;
	if (this->curModule >= curCategoryModules.size() || this->curModule < 0) this->curModule = 0;
	
	int count = -1;
	for (auto iter = curCategoryModules.cbegin(); iter < curCategoryModules.cend(); iter++) {
		
		++count;

		// Module
		AbstractModule* curMod = ToBaseModule(*iter);

		struct Block moduleBlock;
		moduleBlock.width = modulePanelBlock.width;
		moduleBlock.height = 40;
		moduleBlock.x = modulePanelBlock.x;
		moduleBlock.y = modulePanelBlock.y + count * moduleBlock.height + modulePanelScrollY;
		if (this->showUIBB) Renderer::drawBlockBoundingBox(&moduleBlock);
		if (!Renderer::isBlockInAnotherBlock(&moduleBlock, &modulePanelBlock)) continue;
		if (curMod->getToggle()) {
			dl->AddText(Client::fluxFont, 25, ImVec2(moduleBlock.x + 45, moduleBlock.y + 5), FluxColor::ItemSelected, curMod->getName().c_str());
		}
		else {
			dl->AddText(Client::fluxFont, 25, ImVec2(moduleBlock.x + 45, moduleBlock.y + 5), FluxColor::ItemNonSelected, curMod->getName().c_str());
		}
		if (curMod->getKey() != Simulator::KEY_NONE) {

			// Background
			ImVec2 lt(moduleBlock.x + moduleBlock.width - 35, moduleBlock.y + 7);
			dl->AddRectFilled(ImVec2(lt.x, lt.y), ImVec2(lt.x + 25, lt.y + 25), FluxColor::ValueBooleanBackground, 3);

			// Key text
			char buffer[4];
			RtlZeroMemory(buffer, 4);
			sprintf(buffer, "%C", curMod->getKey());
			dl->AddText(Client::fluxFont, 21, ImVec2(moduleBlock.x + moduleBlock.width - 28, moduleBlock.y + 8), FluxColor::ValueBooleanSelected, buffer);

		}
		if (Renderer::isBlockClicked(&moduleBlock)) curMod->toggle();
		if (Renderer::isBlockRightClicked(&moduleBlock)) this->selectModule(count);
		if (!this->bindingKey && Renderer::isBlockMiddleClicked(&moduleBlock)) {
			this->startBindKey(curMod);
		}

		if (this->bindingKey) {
			
			dl = ImGui::GetForegroundDrawList();

			struct Block bindKeyBlock;
			
			bindKeyBlock.x = Game::getGameViewSize().x * 0.5f - 100;
			bindKeyBlock.y = Game::getGameViewSize().y * 0.5f - 35;
			bindKeyBlock.width = 200;
			bindKeyBlock.height = 70;
			dl->AddRectFilled(ImVec2(bindKeyBlock.x, bindKeyBlock.y), ImVec2(bindKeyBlock.x + bindKeyBlock.width, bindKeyBlock.y + bindKeyBlock.height), FluxColor::ValueModeBackground, 5);

			dl->AddText(Client::fluxFont, 30, ImVec2(bindKeyBlock.x + 35, bindKeyBlock.y + 18), FluxColor::White, "Press a key...");

			dl = ImGui::GetBackgroundDrawList();

		}

	}

	// Seperator
	dl->AddLine(ImVec2(modulePanelBlock.x + modulePanelBlock.width, modulePanelBlock.y), ImVec2(modulePanelBlock.x + modulePanelBlock.width, modulePanelBlock.y + modulePanelBlock.height - 2), FluxColor::Gray, 2.5f);

	if (this->showUIBB) Renderer::drawBlockBoundingBox(&modulePanelBlock);

#pragma endregion

#pragma region ValuePanel

	struct Block valuePanelBlock;
	valuePanelBlock.x = modulePanelBlock.x + modulePanelBlock.width;
	valuePanelBlock.y = modulePanelBlock.y;
	valuePanelBlock.width = categoryPanelBlock.width - modulePanelBlock.width;
	valuePanelBlock.height = modulePanelBlock.height;

	AbstractModule* curMod = ToBaseModule(curCategoryModules[this->curModule]);

	if (curMod->getValues().empty()) {
		
		char buffer[512];
		RtlZeroMemory(buffer, 512);
		sprintf(buffer, "%s has no setting", curMod->getName().c_str());
		dl->AddText(Client::fluxFont, 21, ImVec2(valuePanelBlock.x + 30, valuePanelBlock.y + 20), FluxColor::White, buffer);

	}
	else {

		float currentY = 0;
		std::vector<Value*> curModVals = curMod->getValues();
		for (Value* v : curModVals) {
			
			switch (v->getType()) {
			
			case ValueType::Boolean: {
				
				BooleanValue* val = ToDirectValue(v, BooleanValue);
				struct Block booleanValueBlock;
				booleanValueBlock.x = valuePanelBlock.x + 50;
				booleanValueBlock.y = valuePanelBlock.y + 15 + currentY;
				booleanValueBlock.width = valuePanelBlock.width - 100;
				booleanValueBlock.height = 17;

				dl->AddRectFilled(ImVec2(booleanValueBlock.x + 2, booleanValueBlock.y), ImVec2(booleanValueBlock.x + 19, booleanValueBlock.y + 17), FluxColor::ValueBooleanBackground, 3);
				if (val->getValue()) dl->AddText(Client::fluxIcon, 11.5f, ImVec2(booleanValueBlock.x + 5, booleanValueBlock.y + 3), FluxColor::ValueBooleanSelected, FluxIcon::Yes);
				dl->AddText(Client::fluxFont, 21, ImVec2(booleanValueBlock.x + 27, booleanValueBlock.y - 3), FluxColor::White, val->getName().c_str());	

				if (Renderer::isBlockClicked(&booleanValueBlock)) val->toggle();
				if (this->showUIBB) Renderer::drawBlockBoundingBox(&booleanValueBlock);
				currentY += booleanValueBlock.height + 10;
				break;

			}

			case ValueType::Float: {

				FloatValue* val = ToDirectValue(v, FloatValue);
				struct Block floatValueBlock;
				floatValueBlock.x = valuePanelBlock.x + 50;
				floatValueBlock.y = valuePanelBlock.y + 15 + currentY;
				floatValueBlock.width = valuePanelBlock.width - 100;
				floatValueBlock.height = 50;

				// Background and title
				dl->AddText(Client::fluxFont, 21, ImVec2(floatValueBlock.x + 5, floatValueBlock.y + 2), FluxColor::White, val->getName().c_str());
				dl->AddRectFilled(ImVec2(floatValueBlock.x, floatValueBlock.y + 30), ImVec2(floatValueBlock.x + floatValueBlock.width, floatValueBlock.y + 42), FluxColor::ValueFloatBackground, 8);
				
				// Progress
				float progressX = Utility::map(val->getValue(), val->getMin(), val->getMax(), 0, floatValueBlock.width);
				dl->AddRectFilled(ImVec2(floatValueBlock.x, floatValueBlock.y + 30), ImVec2(floatValueBlock.x + progressX, floatValueBlock.y + 42), FluxColor::Orange, 8);

				struct Block sliderBlock;
				sliderBlock.x = floatValueBlock.x + progressX - 5;
				sliderBlock.y = floatValueBlock.y + 26;
				sliderBlock.width = 10;
				sliderBlock.height = 20;
				dl->AddRectFilled(ImVec2(sliderBlock.x, sliderBlock.y), ImVec2(sliderBlock.x + sliderBlock.width, sliderBlock.y + sliderBlock.height), FluxColor::White, 10);
				
				// Handle Sliding
				if (Renderer::isBlockHovered(&floatValueBlock) && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
					
					float offsetToStart = Client::rendererIO->MousePos.x - floatValueBlock.x;
					float mapValue = Utility::map(offsetToStart, 0, floatValueBlock.width, val->getMin(), val->getMax());
					if (val->isIntegerValue())
						val->setValueLong(mapValue);
					else
						val->setValue(mapValue);
				}

				// Show Current Value
				if (Renderer::isBlockHovered(&floatValueBlock)) {
					
					struct Block curValBlock {};
					curValBlock.x = sliderBlock.x;
					curValBlock.y = sliderBlock.y - sliderBlock.height - 5;
					curValBlock.width = 35;
					curValBlock.height = 20;
					dl->AddRectFilled(ImVec2(curValBlock.x, curValBlock.y), ImVec2(curValBlock.x + curValBlock.width, curValBlock.y + curValBlock.height), FluxColor::ValueModeBackground, 3);
					char buf[10];
					RtlZeroMemory(buf, 10);
					if (val->isIntegerValue())
						sprintf(buf, "%d", val->getValueLong());
					else
						sprintf(buf, "%.1f", val->getValue());
					dl->AddText(Client::fluxFont, 20, ImVec2(curValBlock.x + 5, curValBlock.y), FluxColor::White, buf);

					if (this->showUIBB) Renderer::drawBlockBoundingBox(&curValBlock);

				}
				
				if (this->showUIBB) Renderer::drawBlockBoundingBox(&sliderBlock);
				if (this->showUIBB) Renderer::drawBlockBoundingBox(&floatValueBlock);

				currentY += floatValueBlock.height + 10;
				break;
			}

			case ValueType::Mode: {

				ModeValue* val = ToDirectValue(v, ModeValue);
				struct Block modeValueBlock;
				modeValueBlock.x = valuePanelBlock.x + 50;
				modeValueBlock.y = valuePanelBlock.y + 15 + currentY;
				modeValueBlock.width = valuePanelBlock.width - 100;
				modeValueBlock.height = 60;

				// Title
				dl->AddText(Client::fluxFont, 21, ImVec2(modeValueBlock.x + 5, modeValueBlock.y + 3), FluxColor::White, val->getName().c_str());

				// Handle selecting
				if (Renderer::isBlockClicked(&modeValueBlock)) {
					val->toggleUnfold();
				}

				if (val->isUnfold()) {

					constexpr int subModeBlockHeight = 30;
					float subModeHeight = val->getModes().size() * subModeBlockHeight;

					dl = ImGui::GetForegroundDrawList();
				
					// Background
					dl->AddRectFilled(ImVec2(modeValueBlock.x, modeValueBlock.y + 27), ImVec2(modeValueBlock.x + modeValueBlock.width, modeValueBlock.y + modeValueBlock.height + subModeHeight), FluxColor::ValueModeBackground, 3);

					// Foreground
					dl->AddRectFilled(ImVec2(modeValueBlock.x + 2, modeValueBlock.y + 29), ImVec2(modeValueBlock.x + modeValueBlock.width - 2, modeValueBlock.y + modeValueBlock.height + subModeHeight - 2), FluxColor::ValueModeForeground, 3);

					// Active rect
					dl->AddRect(ImVec2(modeValueBlock.x, modeValueBlock.y + 27), ImVec2(modeValueBlock.x + modeValueBlock.width, modeValueBlock.y + modeValueBlock.height), FluxColor::Orange, 3, 0, 2);

					// Render sub-mode
					float curY = 0;
					for (std::string subMode : val->getModes()) {
						
						struct Block subModeBlock;
						subModeBlock.x = modeValueBlock.x;
						subModeBlock.y = modeValueBlock.y + modeValueBlock.height + curY;
						subModeBlock.width = modeValueBlock.width;
						subModeBlock.height = subModeBlockHeight;

						float subModeX = (Renderer::isBlockHovered(&subModeBlock) ? (subModeBlock.x + 10) : (subModeBlock.x + 7));
						ImU32 subModeCol = (val->isCurrentMode(subMode) ? FluxColor::Orange : FluxColor::White);
						dl->AddText(Client::fluxFont, 24, ImVec2(subModeX, subModeBlock.y + 3.5f), subModeCol, subMode.c_str());
						if (Renderer::isBlockClicked(&subModeBlock)) {
							val->setValue(subMode);
							val->setUnfold(false);
						}

						if (this->showUIBB) Renderer::drawBlockBoundingBox(&subModeBlock);
						curY += subModeBlockHeight;
					}

					constexpr int topYOffset = 12;
					constexpr int bottomYOffset = 17;
					ImVec2 p1(modeValueBlock.x + modeValueBlock.width - 23, modeValueBlock.y + 29 + bottomYOffset);
					ImVec2 p2(modeValueBlock.x + modeValueBlock.width - 13, modeValueBlock.y + 29 + bottomYOffset);
					ImVec2 p3((p2.x - p1.x) * 0.5f + p1.x, modeValueBlock.y + 29 + topYOffset);
					dl->AddTriangleFilled(p1, p2, p3, FluxColor::Orange);

					dl = ImGui::GetBackgroundDrawList();

				}
				else {
					
					// Background
					dl->AddRectFilled(ImVec2(modeValueBlock.x, modeValueBlock.y + 27), ImVec2(modeValueBlock.x + modeValueBlock.width, modeValueBlock.y + modeValueBlock.height), FluxColor::ValueModeBackground, 3);

					// Foreground
					dl->AddRectFilled(ImVec2(modeValueBlock.x + 2, modeValueBlock.y + 29), ImVec2(modeValueBlock.x + modeValueBlock.width - 2, modeValueBlock.y + modeValueBlock.height - 2), FluxColor::ValueModeForeground, 3);

					constexpr int topYOffset = 12;
					constexpr int bottomYOffset = 17;
					ImVec2 p1(modeValueBlock.x + modeValueBlock.width - 23, modeValueBlock.y + 29 + topYOffset);
					ImVec2 p2(modeValueBlock.x + modeValueBlock.width - 13, modeValueBlock.y + 29 + topYOffset);
					ImVec2 p3((p2.x - p1.x) * 0.5f + p1.x, modeValueBlock.y + 29 + bottomYOffset);
					dl->AddTriangleFilled(p1, p2, p3, FluxColor::White);

				}
				
				// Current Value
				ImGui::GetForegroundDrawList()->AddText(Client::fluxFont, 24, ImVec2(modeValueBlock.x + 10, modeValueBlock.y + 30.5f), FluxColor::White, val->getValue().c_str());

				if (this->showUIBB) Renderer::drawBlockBoundingBox(&modeValueBlock);
				currentY += modeValueBlock.height + 10;
				break;
			}
			
			}

		}

	}

	if (this->showUIBB) Renderer::drawBlockBoundingBox(&valuePanelBlock);

#pragma endregion

}

void ClickGui::renderInfoPanel() {

	static float fontSize = 24;
	
	// 300*30 in (10,10)
	ImDrawList* dl = ImGui::GetForegroundDrawList();

	struct Block infoPanelBlock;
	infoPanelBlock.x = 20;
	infoPanelBlock.y = 65;
	infoPanelBlock.width = 335;
	infoPanelBlock.height = 30;
	if (this->showUIBB) Renderer::drawBlockBoundingBox(&infoPanelBlock);

	// 暗色背景
	dl->AddRectFilled(ImVec2(infoPanelBlock.x, infoPanelBlock.y), ImVec2(infoPanelBlock.x + infoPanelBlock.width, infoPanelBlock.y + infoPanelBlock.height), FluxColor::InfoPanelBackground);

	// 橙黄色条条
	dl->AddLine(ImVec2(infoPanelBlock.x, infoPanelBlock.y), ImVec2(infoPanelBlock.x + infoPanelBlock.width, infoPanelBlock.y), FluxColor::Orange, 2.5f);

	// 分割线长度
	float seperatorLength = 17;

	// 信息
	float clientNameX = infoPanelBlock.x + 5;
	float clientNameY = infoPanelBlock.y + 2;
	float seperatorY = clientNameY + 5;
	float seperatorThickness = 1.5f;
	dl->AddText(Client::fluxFont, fontSize, ImVec2(clientNameX, clientNameY), FluxColor::InfoPanelText, "Flux");
	dl->AddLine(ImVec2(clientNameX + 38, seperatorY), ImVec2(clientNameX + 38, seperatorY + seperatorLength), FluxColor::InfoPanelSeperator, seperatorThickness);

	float usernameX = clientNameX + 45;
	float usernameY = clientNameY;

#ifdef _DEBUG
	dl->AddText(Client::fluxFont, fontSize, ImVec2(usernameX, usernameY), FluxColor::InfoPanelText, "Dev");
#else
	dl->AddText(Client::fluxFont, fontSize, ImVec2(usernameX, usernameY), FluxColor::InfoPanelText, "Alpha");
#endif
	
	dl->AddLine(ImVec2(clientNameX + 102, seperatorY), ImVec2(clientNameX + 102, seperatorY + seperatorLength), FluxColor::InfoPanelSeperator, seperatorThickness);

	float fpsX = usernameX + 63;
	float fpsY = clientNameY;
	char text[64];
	RtlZeroMemory(text, 64);
	sprintf(text, "%dfps", static_cast<int>(SDK::getIngameFPS()));
	dl->AddText(Client::fluxFont, fontSize, ImVec2(fpsX, fpsY), FluxColor::InfoPanelText, text);
	dl->AddLine(ImVec2(clientNameX + 170, seperatorY), ImVec2(clientNameX + 170, seperatorY + seperatorLength), FluxColor::InfoPanelSeperator, seperatorThickness);

	float pingX = fpsX + 70;
	float pingY = clientNameY;
	RtlZeroMemory(text, 64);
	sprintf(text, "%dms", SDK::getIngamePing());
	dl->AddText(Client::fluxFont, fontSize, ImVec2(pingX, pingY), FluxColor::InfoPanelText, text);
	dl->AddLine(ImVec2(clientNameX + 240, seperatorY), ImVec2(clientNameX + 240, seperatorY + seperatorLength), FluxColor::InfoPanelSeperator, seperatorThickness);

	// Game Version
	float gvX = pingX + 72;
	float gvY = clientNameY;
	RtlZeroMemory(text, 64);
	sprintf(text, "%s", Client::gameVersion.c_str());
	dl->AddText(Client::fluxFont, fontSize, ImVec2(gvX, gvY), FluxColor::InfoPanelText, text);

}

void ClickGui::renderChangeLog() {

	ImDrawList* dl = ImGui::GetForegroundDrawList();
	Vec2 view = Game::getGameViewSize();
	view.x *= 0.5f;
	view.y *= 0.5f;

	// Background
	struct Block panelBlock;
	panelBlock.width = 840;
	panelBlock.height = 590;
	panelBlock.x = view.x - panelBlock.width * 0.5f;
	panelBlock.y = view.y - panelBlock.height * 0.5f;
	dl->AddRectFilled(ImVec2(panelBlock.x, panelBlock.y), ImVec2(panelBlock.x + panelBlock.width, panelBlock.y + panelBlock.height), FluxColor::MainPanelBackground, 5);
	if (this->showUIBB) Renderer::drawBlockBoundingBox(&panelBlock);

	float wheel = Client::rendererIO->MouseWheel;
	if (wheel != 0 && Renderer::isBlockHovered(&panelBlock))
		changelogPanelScrollY += wheel * 25;

	// Title
	dl->AddText(Client::fluxIcon, 35, ImVec2(panelBlock.x + 20, panelBlock.y + 20), FluxColor::White, FluxIcon::Logo);
	dl->AddText(Client::fluxFont, 35, ImVec2(panelBlock.x + 70, panelBlock.y + 20), FluxColor::White, "Changelog");

	// Seperator
	dl->AddLine(ImVec2(panelBlock.x, panelBlock.y + 75), ImVec2(panelBlock.x + panelBlock.width, panelBlock.y + 75), FluxColor::Gray, 2.5f);

	// Content
	struct Block contentBlock;
	contentBlock.x = panelBlock.x;
	contentBlock.y = panelBlock.y + 90;
	contentBlock.width = panelBlock.width;
	contentBlock.height = panelBlock.height - 90;
	if (this->showUIBB) Renderer::drawBlockBoundingBox(&panelBlock);
	float curY = 5;
	for (std::string& item : this->changelogItems) {

		struct Block itemBlock;
		itemBlock.x = contentBlock.x;
		itemBlock.y = contentBlock.y + curY + changelogPanelScrollY;
		itemBlock.width = contentBlock.width;
		itemBlock.height = 20;
		if (this->showUIBB) Renderer::drawBlockBoundingBox(&itemBlock);

		if (Renderer::isBlockInAnotherBlock(&itemBlock, &contentBlock))
			dl->AddText(Client::chinese, 20, ImVec2(itemBlock.x + 40, itemBlock.y), FluxColor::White, Utility::toUtf8(const_cast<char*>(item.c_str())));

		curY += 30;

	}

	// Close Button
	struct Block closeBlock;
	closeBlock.width = 70;
	closeBlock.height = 40;
	closeBlock.x = panelBlock.x + panelBlock.width - closeBlock.width;
	closeBlock.y = panelBlock.y + panelBlock.height - closeBlock.height;
	if (Renderer::isBlockHovered(&closeBlock))
		dl->AddText(Client::fluxFont, 25, ImVec2(closeBlock.x + 10, closeBlock.y + 5), FluxColor::ItemSelected, "Close");
	else	
		dl->AddText(Client::fluxFont, 25, ImVec2(closeBlock.x + 10, closeBlock.y + 5), FluxColor::ItemNonSelected, "Close");
	if (this->showUIBB) Renderer::drawBlockBoundingBox(&closeBlock);
	if (Renderer::isBlockClicked(&closeBlock)) this->changelog = false;

}

void ClickGui::selectCategory(Category category) {
	if (category != this->curCategory)
		this->curCategory = category;
}

void ClickGui::selectModule(int mod) {
	this->curModule = mod;
}

void ClickGui::startBindKey(AbstractModule* target) {
	this->bindingModule = target;
	this->bindingKey = true;
}

void ClickGui::endBindKey() {
	this->bindingKey = false;
	this->bindingModule = nullptr;
}

