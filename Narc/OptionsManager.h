#pragma once

#include "EntityStructs.h"

class COptions {
public:
	bool bEspEnabled = false;
	int iEspKey = 0;

	const int KeysID[7] = {
		0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76
	};
};

extern COptions OptionsManager;