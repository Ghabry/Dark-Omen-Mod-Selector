// allow the player viewpoint to move out ten times further from the ground

#include "header.h"

namespace camera_elevation
{
	void Load(){
		*((DWORD*)0x00430D26) = 0x44480000;
		*((DWORD*)0x00430E98) = 0x44480000;
		*((DWORD*)0x004310AC) = 0x44480000;
	}
	void Unload(){
		*((DWORD*)0x00430D26) = 0x428C0000;
		*((DWORD*)0x00430E98) = 0x428C0000;
		*((DWORD*)0x004310AC) = 0x42A00000;
	}
}
