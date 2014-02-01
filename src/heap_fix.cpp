// suppress annoying heap block corruption warnings. 
// by rounding up allocated chunk sizes to a multiple of 16

#include "header.h"

namespace heap_fix
{
	HGLOBAL __stdcall GlobalAllocWrap( UINT uFlags, DWORD dwBytes ){
		return GlobalAlloc( uFlags, ( ( dwBytes + 0x0000000F ) & 0x7FFFFFF0 ) );
	}
	// ".idata" section is writable by default... which is odd.
	void Load(){ *((DWORD*)0x005864D8) = (DWORD)&GlobalAllocWrap; }
	void Unload(){ *((DWORD*)0x005864D8) = (DWORD)&GlobalAlloc; }
}
