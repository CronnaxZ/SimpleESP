#include "Hooks.h"

#include "SqchSDK\Interfaces.h"

namespace Hooks {
	std::unique_ptr<HookTable::VFTableHook> g_pClientHook = nullptr;
	std::unique_ptr<HookTable::VFTableHook> g_pStudioRenderHook = nullptr;
	std::unique_ptr<HookTable::VFTableHook> g_pModelRenderHook = nullptr;
	std::unique_ptr<HookTable::VFTableHook> g_pVGuiHook = nullptr;
	std::unique_ptr<HookTable::VFTableHook> g_pClientModeHook = nullptr;
	std::unique_ptr<HookTable::VFTableHook> g_pEngineHook = nullptr;
	std::unique_ptr<HookTable::VFTableHook> g_pViewRenderHook = nullptr;

	HookTable::VFTableHook *g_pEngineTraceHook = nullptr;

	void __declspec(naked) __stdcall HookedCreateMoveNaked(int sequence_number, float input_sample_frametime, bool active)
	{
		__asm
		{
			PUSH EBX				// push sendpacket from ebx
			PUSH ESP				// push address of sendpackt
			PUSH[ESP + 0x14]		// push active
			PUSH[ESP + 0x14]		// push input_sample_frametime
			PUSH[ESP + 0x14]		// push sequence_number
			POP EBX					// pop sendpacket to ebx
			RET 0x0C				// remove 3 agruments from stack and return
		}
	}

	typedef void(__thiscall* ClipRay)(void*, const SSDK::Ray_t &ray, unsigned int fMask, SSDK::IHandleEntity *pEnt, SSDK::CGameTrace *pTrace);
	ClipRay g_fnOriginalClipRay;
	void __fastcall Hooked_ClipRay(void* thisptr, void* edx, const SSDK::Ray_t &ray, unsigned int fMask, SSDK::IHandleEntity *pEnt, SSDK::CGameTrace *pTrace) {
		g_fnOriginalClipRay(thisptr, ray, fMask, pEnt, pTrace);
		pTrace->fraction = 1.f;
	}

	typedef void(__thiscall* TraceRay)(void*, const SSDK::Ray_t &ray, unsigned int fMask, SSDK::ITraceFilter *pTraceFilter, SSDK::CGameTrace *pTrace);
	TraceRay g_fnOriginalTraceRay;
	void __fastcall Hooked_TracRay(void* thisptr, void* edx, const SSDK::Ray_t &ray, unsigned int fMask, SSDK::ITraceFilter *pTraceFilter, SSDK::CGameTrace *pTrace) {
		g_fnOriginalTraceRay(thisptr, ray, fMask, pTraceFilter, pTrace);
		pTrace->fraction = 1.f;
	}

	typedef void(__thiscall* RayCollide)(void*, const SSDK::Ray_t &ray, unsigned int fMask, SSDK::ICollideable *pCollide, SSDK::CGameTrace *pTrace);
	RayCollide g_fnOriginalRayCollide;
	void __fastcall Hooked_RayCollide(void* thisptr, void* edx, const SSDK::Ray_t &ray, unsigned int fMask, SSDK::ICollideable *pCollide, SSDK::CGameTrace *pTrace) {
		g_fnOriginalRayCollide(thisptr, ray, fMask, pCollide, pTrace);
		pTrace->fraction = 1.f;
	}

	void Initialize() {
		//-----------------------------------------------------------------------------------------------

		NetvarManager::Instance()->CreateDatabase();

		DrawManager::InitializeFont(XorStr("Verdana"), 15);


		//-----------------------------------------------------------------------------------------------

		g_pClientHook = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)SSDK::I::Client(), true);
		g_pStudioRenderHook = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)SSDK::I::StudioRender(), true);
		g_pModelRenderHook = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)SSDK::I::ModelRender(), true);
		g_pVGuiHook = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)SSDK::I::VGUIPanel(), true);
		g_pClientModeHook = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)SSDK::I::ClientMode(), true);
		g_pEngineHook = std::make_unique<HookTable::VFTableHook>((HookTable::PPDWORD)SSDK::I::Engine(), true);

		//Drawing hooks
		PT::g_fnOriginalPaintTraverse = g_pVGuiHook->Hook(41, (PT::PaintTraverse_t)PT::Hooked_PaintTraverse);

		//------------------------------------------------------------------------------------------------
	}

	void RestoreAllTable() {
		g_pClientHook->RestoreTable();
		g_pModelRenderHook->RestoreTable();
		g_pVGuiHook->RestoreTable();
		g_pClientModeHook->RestoreTable();
		g_pEngineHook->RestoreTable();
	}
}