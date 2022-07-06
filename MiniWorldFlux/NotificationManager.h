#pragma once
#include "pch.h"
#include "imgui.h"
#include "Icon.h"
#include "Colors.h"
#include "EventManager.h"

enum class NotiLevel : unsigned long {
    INFO = 0U,
    ERR,
    WARN
};

class Notification {

public:
    friend class NotificationManager;

private:
    Notification(std::string text, NotiLevel level, float duration);

    std::string text;
    NotiLevel level;
    float duration;

    void reduceTime(float time);

};

typedef std::vector<Notification*> NotificationQueue;

class NotificationManager {

public:
    static NotificationManager& getInstance();
    void notify(std::string text, NotiLevel level, float duration);
    void onRenderOverlay();

    NotificationManager(const NotificationManager&) = delete;
    NotificationManager(NotificationManager&&) = delete;
    void operator=(const NotificationManager&) = delete;

private:

    float startX = 10;
    float startY = 600;
    float curY = 0;
    float rectWidth = 230;
    float rectHeight = 50;

    NotificationQueue queue;

    NotificationManager();
    ~NotificationManager() = default;

};

