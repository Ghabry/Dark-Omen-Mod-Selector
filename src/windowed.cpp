// set fullscreen to false
// Run in window mode (debug mode)

#include "header.h"

namespace windowed
{
	void Load(){ *((DWORD*)0x004BF0A8) = 0; }
	void Unload(){ *((DWORD*)0x004BF0A8) = 1; }
}