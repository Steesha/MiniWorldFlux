#include "FreeItems.h"

FreeItems::FreeItems() : AbstractModule("FreeItems", Category::Player) {

    EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &FreeItems::onRenderOverlay));
}

FreeItems* FreeItems::getInstance() {
	static FreeItems* inst = new FreeItems();
	return inst;
}

__declspec(naked) void callItemGetter(int itemId) {

    __asm {

        pushad
        push 1111
        push 64
        push itemId
        mov ecx, g_localPlayer
        mov ecx, [ecx]
        mov eax, g_freeItemsCallAddr
        call eax
        popad
        ret

    }
}

__declspec(naked) void callSingleItemGetter(int itemId) {

    __asm {

        pushad
        push 1111
        push 1
        push itemId
        mov ecx, g_localPlayer
        mov ecx, [ecx]
        mov eax, g_freeItemsCallAddr
        call eax
        popad
        ret

    }
}

void FreeItems::onEnabled() {
    intervalTimer.reset();
}

void FreeItems::onDisabled() {
    intervalTimer.reset();
}
void FreeItems::onRenderOverlay() {
    ToggleCheck;
    if (!Game::isPlaying()) {
        this->disable();
        return;
    }

    // 345*160
    ImGui::SetNextWindowSize(ImVec2(345, 160));
    ImGui::Begin("FreeItems", nullptr, ImGuiWindowFlags_NoResize);

    ImGui::InputInt("Item ID", &this->itemId);
    if (ImGui::Button("Call(1)")) {
        if (this->intervalTimer.elapsed(1000)) {
            if (this->itemId >= 0) {
                MakeDisposableThread(callSingleItemGetter, ToPointer(this->itemId, void));
                intervalTimer.reset();
            }
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Call(64)")) {
        if (this->intervalTimer.elapsed(1000)) {
            if (this->itemId >= 0) {
                MakeDisposableThread(callItemGetter, ToPointer(this->itemId, void));
                intervalTimer.reset();
            }
        }
    }

    ImGui::End();

}

