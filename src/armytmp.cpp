// repoint [armytmp] to somewhere that doesn't require admin rights to write to...

#include "header.h"

namespace armytmp
{
	LONG __stdcall RegQueryValueExAWrap( HKEY hKey, LPTSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData )
	{
		if( !strcmp( lpValueName, "ARMYTEMP" ) ){
			; // todo
		}
		return RegQueryValueExA( hKey, lpValueName, lpReserved, lpType, lpData, lpcbData );
	}
	// ".idata" section is writable by default... which is odd.
	void Load(){ *((DWORD*)0x0058644C) = (DWORD)&RegQueryValueExAWrap; }
	void Unload(){ *((DWORD*)0x0058644C) = (DWORD)&RegQueryValueExA; }
}

