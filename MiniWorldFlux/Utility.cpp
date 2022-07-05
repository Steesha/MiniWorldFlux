#include "Utility.h"

namespace Utility {

    static HWND wndGame = FindWindowA("RenderWindow_ClassName", nullptr);

    inline float PI() { return 3.1415926535f; }
	
    void openConsole() {

        AllocConsole();
        SetConsoleTitleW(L"Flux client is injected.(Author: °¢ÒðAyin)");
        freopen("CONOUT$", "w", stdout);
    }

    bool compareString(const char* _String1, const char* _String2) {
        return strcmp(_String1, _String2) == 0;
    }

    bool compareStringIgnoreCase(const char* _String1, const char* _String2) {
        return _stricmp(_String1, _String2) == 0;
    }

    bool compareString(std::string _String1, std::string _String2) {
        return Utility::compareString(_String1.c_str(), _String2.c_str());
    }

    bool compareStringIgnoreCase(std::string _String1, std::string _String2) {
        return Utility::compareStringIgnoreCase(_String1.c_str(), _String2.c_str());
    }

    void notice(const char* msg, Level lv) {
        
        if (lv == Level::INFO) {
            MessageBoxA(nullptr, msg, "Infomation from Hanabi:", MB_OK | MB_ICONINFORMATION);
            return;
        }

        if (lv == Level::ERR) {
            MessageBoxA(nullptr, msg, "Error from Hanabi:", MB_OK | MB_ICONERROR);
            return;
        }

        if (lv == Level::WARN) {
            MessageBoxA(nullptr, msg, "Warnning from Hanabi:", MB_OK | MB_ICONWARNING);
            return;
        }
    }

    bool isReadablePtr(void* pointer) {
        return (IsBadReadPtr(pointer, sizeof(pointer)) == 0);
    }

    bool isWriteablePtr(void* pointer) {
        return (IsBadWritePtr(pointer, sizeof(pointer)) == 0);
    }

    float getDistance2D(struct Vec2 from, struct Vec2 to) {

        Vec2 diff;
        diff.x = to.x - from.x;
        diff.y = to.y - from.y;

        return sqrt(diff.x * diff.x + diff.y * diff.y);

    }

    float getDistance3D(struct Vec3 from, struct Vec3 to) {

        Vec3 diff;
        diff.x = to.x - from.x;
        diff.y = to.y - from.y;
        diff.z = to.z - from.z;

        return sqrt(diff.x * diff.x + diff.y + diff.y + diff.z * diff.z);

    }

    bool worldToScreen(const float pvm[4][4], struct Vec3* target, struct Vec2* view, struct Vec2* screenPos) {

        float cameraZ = pvm[0][3] * target->x + pvm[1][3] * target->y + pvm[2][3] * target->z + pvm[3][3];
        if (cameraZ < 0.01f) return false;

        float scale = 1 / cameraZ;
        (*screenPos).x = view->x + (pvm[0][0] * target->x + pvm[1][0] * target->y + pvm[2][0] * target->z + pvm[3][0]) * scale * view->x;
        (*screenPos).y = view->y - (pvm[0][1] * target->x + pvm[1][1] * target->y + pvm[2][1] * target->z + pvm[3][1]) * scale * view->y;

        return true;
    }

    Vec2 calcAimAngle(struct Vec3* player, struct Vec3* target) {

        Vec2 result;
        Vec3 diff;
        diff.x = target->x - player->x;
        diff.y = target->z - player->z;
        diff.z = target->y - player->y;

        if (diff.x >= 0 && diff.y >= 0)
            result.x = atanf(diff.x / diff.y) / PI() * 180;
        if (diff.x <= 0 && diff.y >= 0)
            result.x = 270 + atanf(diff.y / abs(diff.x)) / PI() * 180;
        if (diff.x <= 0 && diff.y <= 0)
            result.x = 180 + atanf(abs(diff.x) / abs(diff.y)) / PI() * 180;
        if (diff.x >= 0 && diff.y <= 0)
            result.x = 90 + atanf(abs(diff.y) / diff.x) / PI() * 180;

        result.y = -atanf(diff.z / sqrt(diff.x * diff.x + diff.y * diff.y)) / PI() * 180;

        return result;
    }

    float getStringLength(const char* _String, float _StringScale) {

        return strlen(_String) * _StringScale;
    }

    float map(float in, float inMin, float inMax, float outMin, float outMax) {
        return (in - inMin) / (inMax - inMin) * (outMax - outMin) + outMin;
    }

    time_t currentTimeMillis() {

        struct timeb time;
        ftime(&time);
        return time.time * 1000 + time.millitm;
    }

    ColorHSV RGB2HSV(ColorRGB in) {

        ColorHSV         out;
        double      min, max, delta;

        min = in.r < in.g ? in.r : in.g;
        min = min < in.b ? min : in.b;

        max = in.r > in.g ? in.r : in.g;
        max = max > in.b ? max : in.b;

        out.v = max;                                // v
        delta = max - min;
        if (delta < 0.00001)
        {
            out.s = 0;
            out.h = 0; // undefined, maybe nan?
            return out;
        }
        if (max > 0.0) { // NOTE: if Max is == 0, this divide would cause a crash
            out.s = (delta / max);                  // s
        }
        else {
            // if max is 0, then r = g = b = 0              
            // s = 0, h is undefined
            out.s = 0.0;
            out.h = NAN;                            // its now undefined
            return out;
        }
        if (in.r >= max)                           // > is bogus, just keeps compilor happy
            out.h = (in.g - in.b) / delta;        // between yellow & magenta
        else
            if (in.g >= max)
                out.h = 2.0 + (in.b - in.r) / delta;  // between cyan & yellow
            else
                out.h = 4.0 + (in.r - in.g) / delta;  // between magenta & cyan

        out.h *= 60.0;                              // degrees

        if (out.h < 0.0)
            out.h += 360.0;

        return out;
    }

    ColorRGB HSV2RGB(ColorHSV in) {

        double      hh, p, q, t, ff;
        long        i;
        ColorRGB    out;

        if (in.s <= 0.0) {       // < is bogus, just shuts up warnings
            out.r = in.v;
            out.g = in.v;
            out.b = in.v;
            return out;
        }
        hh = in.h;
        if (hh >= 360.0) hh = 0.0;
        hh /= 60.0;
        i = (long)hh;
        ff = hh - i;
        p = in.v * (1.0 - in.s);
        q = in.v * (1.0 - (in.s * ff));
        t = in.v * (1.0 - (in.s * (1.0 - ff)));

        switch (i) {
        case 0:
            out.r = in.v;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = in.v;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = in.v;
            out.b = t;
            break;

        case 3:
            out.r = p;
            out.g = q;
            out.b = in.v;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = in.v;
            break;
        case 5:
        default:
            out.r = in.v;
            out.g = p;
            out.b = q;
            break;
        }
        return out;
    }

    int rainbow(int delay, long timeOffset) {

        double rainbow = ceil((Utility::currentTimeMillis() + timeOffset) / 8 + delay / 20.0);

        ColorHSV rainbowHSV{};
        rainbowHSV.h = fmod(rainbow, 360.0);
        rainbowHSV.s = 1;
        rainbowHSV.v = 1;

        ColorRGB rainbowRGB{};
        rainbowRGB = Utility::HSV2RGB(rainbowHSV);
        rainbowRGB.r *= 255;
        rainbowRGB.g *= 255;
        rainbowRGB.b *= 255;

        return (0xFF << 24) | (static_cast<int>(rainbowRGB.r) << 16) | (static_cast<int>(rainbowRGB.g) << 8) | static_cast<int>(rainbowRGB.b);
    }


}
