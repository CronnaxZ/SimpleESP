#include "PT.h"

namespace PT {
	PaintTraverse_t g_fnOriginalPaintTraverse;
	void __fastcall Hooked_PaintTraverse(void* thisptr, void* edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce) {
		g_fnOriginalPaintTraverse(thisptr, vguiPanel, forceRepaint, allowForce);

		static unsigned int iSelectedPanelMat = 0;

		if (!iSelectedPanelMat) {
			if (strstr(SSDK::I::VGUIPanel()->GetName(vguiPanel), XorStr("FocusOverlayPanel")))
				iSelectedPanelMat = vguiPanel;
		}
		else if (vguiPanel == iSelectedPanelMat) {
			int iScreenWidth, iScreenHeight;
			SSDK::I::Engine()->GetScreenSize(iScreenWidth, iScreenHeight);

			DrawManager::DrawString(SSDK::Color(0, 255, 0), DrawManager::hFont2, XorStr("ESP:"), 20, 300);

			if (OptionsManager.bEspEnabled)
				DrawManager::DrawString(SSDK::Color(0, 255, 0), DrawManager::hFont2, XorStr("ON"), 50, 300);
			else if (!OptionsManager.bEspEnabled)
				DrawManager::DrawString(SSDK::Color(255, 0, 0), DrawManager::hFont2, XorStr("OFF"), 50, 300);

			if (SSDK::I::Engine()->isInGame()) {

				if (GetAsyncKeyState(OptionsManager.iEspKey[OptionsManager.KeysID]) & 0x1)
					OptionsManager.bEspEnabled = !OptionsManager.bEspEnabled;

				for (int i = 0; i < SSDK::I::EntityList()->GetHighestEntityIndex(); ++i) {

					CBaseEntity *pEntity = (CBaseEntity*)SSDK::I::EntityList()->GetClientEntity(i);
					CBaseEntity *pLocalPlayer = CBaseEntity::GetLocalPlayer();
					SSDK::CGlowObjectManager::GlowObjectDefinition_t* glowEntity = (SSDK::CGlowObjectManager::GlowObjectDefinition_t*)SSDK::I::EntityList()->GetClientEntity(i);

					if (!pEntity)
						continue;

					if (OptionsManager.bEspEnabled && pEntity->isValidPlayer()) {

						//ESP
						SSDK::Vector vecHeadHitBox = pEntity->GetEntityHitbox(0), vecOrigin = *pEntity->GetOrigin();
						SSDK::Vector vecHeadHitBox2D, vecOrigin2D;

						vecHeadHitBox.z += 10.f;

						if (Utilities::W2S(vecHeadHitBox, vecHeadHitBox2D) &&
							Utilities::W2S(vecOrigin, vecOrigin2D)) {
							float height = vecOrigin2D.y - vecHeadHitBox2D.y;
							float width = height * 0.45f;

							if (OptionsManager.bEspEnabled)
								DrawManager::DrawBox(pEntity, vecHeadHitBox2D.x, vecHeadHitBox2D.y, width / 1.5, height);
						}
					}
				}
			}
		}
	}
}