#include "header.h"

// this really needs to be tested on a fresh/clean install...

// todo: copy over movie files
// todo: what is missing to get the tutorial working?

namespace no_cd
{
	void Load(){ *(WORD*) 0x0048A5F2 = 0xC340; }
	void Unload(){ *(WORD*) 0x0048A5F2 = 0x90C3; }
}