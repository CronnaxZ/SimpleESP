#pragma once

#include "SqchSDK\Interfaces.h"
#include "EntityStructs.h"
#include "Utilities.h"

class DrawManager {
public:
	static SSDK::HFont hFont;
	static SSDK::HFont hFont2;

	static void InitializeFont(const char* fontName, int size);
	static void DrawString(SSDK::Color cColor, SSDK::HFont font, const char* chString, int x, int y);
	static void DrawStringValue(SSDK::Color cColor, int x, int y, SSDK::HFont font, const char* chString, ...);
	static void DrawOutlinedRect(SSDK::Color cColor, float x0, float y0, float x1, float y1);
	static void DrawBox(CBaseEntity * pEntity, float x0, float y0, float x1, float y1);
};