// repoint [armytmp] to a folder in the game directory
// somewhere that doesn't require admin rights to write to...
// folder is created if missing

#include "header.h"

namespace armytmp
{
	LONG __stdcall RegQueryValueExAWrap( HKEY hKey, LPTSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData )
	{
		if( !strcmp( lpValueName, "ARMYTMP" ) ){
			if( g_szArmyTmpDir[0] != '\0' ){
				if( ( GetFileAttributes( g_szArmyTmpDir ) != 0xFFFFFFFF ) || ( CreateDirectory( g_szArmyTmpDir, NULL ) != FALSE ) ){ 
					if( lpType != NULL ) *lpType = REG_SZ;
					if( lpcbData != NULL )
					{
						DWORD required_size = strlen( g_szArmyTmpDir ) + 1;
						DWORD buf_size = *lpcbData;
						*lpcbData = required_size;
						if( buf_size < required_size ) return (( lpData == NULL ) ? ERROR_SUCCESS : ERROR_MORE_DATA );
						memcpy( lpData, g_szArmyTmpDir, required_size );
					}
					return ERROR_SUCCESS;
				}
			}	  
		}
		return RegQueryValueExA( hKey, lpValueName, lpReserved, lpType, lpData, lpcbData );
	}
	// ".idata" section is writable by default... which is odd.
	void Load(){ *((DWORD*)0x0058644C) = (DWORD)&RegQueryValueExAWrap; }
	void Unload(){ *((DWORD*)0x0058644C) = (DWORD)&RegQueryValueExA; }
}