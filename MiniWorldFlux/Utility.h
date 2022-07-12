#pragma once
#include "pch.h"
#include "Structs.h"

typedef long long time_t;

namespace Utility {

	void openConsole();

	bool compareString(const char* _String1, const char* _String2);

	bool compareStringIgnoreCase(const char* _String1, const char* _String2);

	bool compareString(std::string _String1, std::string _String2);

	bool compareStringIgnoreCase(std::string _String1, std::string _String2);

	bool isReadablePtr(void* pointer, uint32_t size = 0);

	bool isWriteablePtr(void* pointer);

	float getDistance2D(struct Vec2 from, struct Vec2 to);

	float getDistance3D(struct Vec3 from, struct Vec3 to);

	bool worldToScreen(const float pvm[4][4], Vec3* target, struct Vec2* view, struct Vec2* screenPos);

	struct Vec2 calcAimAngle(struct Vec3* player, struct Vec3* target);

	float getStringLength(const char* _String, float _StringScale);

	float map(float in, float inMin, float inMax, float outMin, float outMax);

	ColorHSV RGB2HSV(ColorRGB in);

	ColorRGB HSV2RGB(ColorHSV in);

	time_t currentTimeMillis();

	int rainbow(int delay, long timeOffset);

	char* toUtf8(char* target);

}
