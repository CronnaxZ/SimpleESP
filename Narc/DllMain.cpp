#include <Windows.h>

#include "Hooks.h"

void MainThread() {
	Hooks::Initialize();
}

void UnHookThread(HINSTANCE hinstDLL) {
	while (true) {
		if (GetAsyncKeyState(VK_END) & 0x1) { //Press END to detach DLL
			FreeLibraryAndExitThread(hinstDLL, 0); //FreeLibAndStopThread
		}
		Sleep(50);
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hinstDLL);

		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UnHookThread, hinstDLL, 0, 0);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hinstDLL, 0, 0);
		break;

	case DLL_PROCESS_DETACH:
		Hooks::RestoreAllTable();
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}