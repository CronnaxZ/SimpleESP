#pragma once
#include "IClientEntity.h"
#include "CHandle.h"

namespace SSDK {
	class IClientEntityList {
	public:
		IClientEntity* GetClientEntity(int entNum) {
			typedef IClientEntity*(__thiscall *OrigFn)(void*, int);
			return CallVFunction<OrigFn>(this, 3)(this, entNum);
		}

		IClientEntity* GetClientEntityFromHandle(CBaseHandle hEnt) {
			typedef IClientEntity*(__thiscall *OrigFn)(void*, CBaseHandle);
			return CallVFunction<OrigFn>(this, 4)(this, hEnt);
		}

		int GetHighestEntityIndex() {
			typedef int(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 6)(this);
		}
	};
}