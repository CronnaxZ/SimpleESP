#pragma once

#include "Vector.h"

namespace SSDK {
	class IVDebugOverlay {
	public:
		int ScreenPosition(const Vector& vIn, Vector& vOut)
		{
			typedef int(__thiscall* OrigFn)(void*, const Vector&, Vector&);
			return CallVFunction<OrigFn>(this, 13)(this, vIn, vOut);
		}
	};
}