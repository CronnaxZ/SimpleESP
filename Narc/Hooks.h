#pragma once
#include "NetvarManager.h"
#include "VTHooksManager.h"
#include "DrawManager.h"

#include "SqchSDK\Interfaces.h"
#include "SqchSDK\Offsets.h"

#include "PT.h"

namespace Hooks {
	void Initialize();
	void RestoreAllTable();
}