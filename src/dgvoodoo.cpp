// contains patches that ensure Dark Omen works nicely with dgvoodoo

#include "header.h"
#include <stdint.h>

namespace dgvoodoo
{
	void Load() {
		// Fix endless SetCursor loop when high resolution is forced
		memcpy((void*)0x41805A, "\x90\x90", 2);

		// Pass 3D render test
		memcpy((void*)0x44158C, "\xBE\xFF\xFF", 3);
	}

	void Unload() {

	}
}
