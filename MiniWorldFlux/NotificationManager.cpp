#include "pch.h"
#include "NotificationManager.h"

Notification::Notification(std::string text, NotiLevel level, float duration) : text(text), level(level), duration(duration) {

}

void Notification::reduceTime(float time) {
    this->duration -= time;
}

NotificationManager::NotificationManager() {
    EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &NotificationManager::onRenderOverlay));
}

NotificationManager& NotificationManager::getInstance() {
    static NotificationManager inst;
    return inst;
}

void NotificationManager::notify(std::string text, NotiLevel level, float duration) {
    Notification* noti = new Notification(text, level, duration);
    this->queue.push_back(noti);
}

void NotificationManager::onRenderOverlay() {
    if (this->queue.empty()) return;

    ImDrawList* dl = ImGui::GetForegroundDrawList();
    ImGuiIO& io = ImGui::GetIO();
    ImFont* fluxFont = io.Fonts->Fonts[0];
    ImFont* fluxIcon = io.Fonts->Fonts[1];
    
    this->curY = 0;
    for (auto iter = this->queue.begin(); iter < this->queue.end(); iter++) {
        Notification* noti = *iter;

        if (noti->duration < 0) {
            this->queue.erase(iter);
            if (noti != nullptr)
                delete noti;
            return;
        }

        const char* icon = nullptr;

        switch (noti->level) {

        case NotiLevel::INFO: {
            icon = FluxIcon::Info;
            break;
        }

        case NotiLevel::ERR: {
            icon = FluxIcon::Error;
            break;
        }

        case NotiLevel::WARN: {
            icon = FluxIcon::Warn;
            break;
        }

        }

        float curStartY = this->startY - this->curY;
        dl->AddRectFilled(ImVec2(this->startX, curStartY), ImVec2(this->startX + this->rectWidth, curStartY + this->rectHeight), FluxColor::NotificationBackground, 5);
        dl->AddText(fluxIcon, 30, ImVec2(this->startX + 10, curStartY + 10), FluxColor::NotificationContent, icon);
        dl->AddText(fluxFont, 22, ImVec2(this->startX + 50, curStartY + 13), FluxColor::NotificationContent, noti->text.c_str());
        noti->reduceTime(io.DeltaTime);

        this->curY += this->rectHeight + 15;
    }

}
