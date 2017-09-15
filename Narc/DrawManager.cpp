#include "DrawManager.h"

SSDK::HFont DrawManager::hFont = 0;
SSDK::HFont DrawManager::hFont2 = 0;

void DrawManager::InitializeFont(const char* fontName, int size) {
	hFont = SSDK::I::MatSurface()->CreateFont();
	SSDK::I::MatSurface()->SetFontGlyphSet(hFont, fontName, size, size * 10, 0, 0, (int)SSDK::FontFlags::FONTFLAG_ANTIALIAS);

	hFont2 = SSDK::I::MatSurface()->CreateFont();
	SSDK::I::MatSurface()->SetFontGlyphSet(hFont2, fontName, size - 2, (size - 2) * 10, 0, 0, (int)SSDK::FontFlags::FONTFLAG_OUTLINE);
}

void DrawManager::DrawString(SSDK::Color cColor, SSDK::HFont font, const char* chString, int x, int y) {
	wchar_t formated[128] = { '\0' };
	wsprintfW(formated, L"%S", chString);
	SSDK::I::MatSurface()->DrawSetTextPos(x, y);
	SSDK::I::MatSurface()->DrawSetTextColor(cColor);
	SSDK::I::MatSurface()->DrawSetTextFont(font);
	SSDK::I::MatSurface()->DrawPrintText(formated, wcslen(formated));
}

void DrawManager::DrawStringValue(SSDK::Color cColor, int x, int y, SSDK::HFont font, const char* chString, ...) {
	char buffer[128];
	va_list list;
	va_start(list, chString);
	vsprintf_s(buffer, chString, list);
	va_end(list);
	wchar_t formated[128] = { '\0' };
	wsprintfW(formated, L"%S", buffer);
	SSDK::I::MatSurface()->DrawSetTextPos(x, y);
	SSDK::I::MatSurface()->DrawSetTextColor(cColor);
	SSDK::I::MatSurface()->DrawSetTextFont(font);
	SSDK::I::MatSurface()->DrawPrintText(formated, wcslen(formated));
}

void DrawManager::DrawOutlinedRect(SSDK::Color cColor, float x0, float y0, float x1, float y1) {
	SSDK::I::MatSurface()->DrawSetColor(cColor);
	SSDK::I::MatSurface()->DrawOutlinedRect(x0, y0, x1, y1);
}

void DrawManager::DrawBox(CBaseEntity *pEntity, float x0, float y0, float x1, float y1) {
	switch (*pEntity->GetTeamNum()) {
	case 2:
		SSDK::I::MatSurface()->DrawSetColor(SSDK::Color(0, 0, 0, 255));
		SSDK::I::MatSurface()->DrawOutlinedRect(x0 - x1, y0, x0 + x1, y0 + y1);
		break;
	case 3:
		SSDK::I::MatSurface()->DrawSetColor(SSDK::Color(0, 0, 255, 255));
		SSDK::I::MatSurface()->DrawOutlinedRect(x0 - x1, y0, x0 + x1, y0 + y1);
		break;
	default:
		break;
	}
}