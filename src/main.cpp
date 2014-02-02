#include "header.h"



BOOL __stdcall DllEntryPoint_DDraw( HINSTANCE hDll, DWORD dwReason, LPVOID lpvReserved ); // ddraw_proxy.cpp

char g_szInstallDir[ MAX_PATH ];
char g_szArmyTmpDir[ MAX_PATH ];


void InitPaths()
{
	HKEY hkRead;
	DWORD cbData = MAX_PATH;
	if( RegOpenKeyEx( HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\Dark Omen", 0, KEY_READ, &hkRead ) == ERROR_SUCCESS ){
		if( RegQueryValueEx( hkRead, "InstallDir", 0, NULL, (LPBYTE) g_szInstallDir, &cbData ) == ERROR_SUCCESS ){
			if( 0xFFFFFFFF != GetFileAttributes( g_szInstallDir ) ){
				if( MAX_PATH >= ( ( cbData - 1 ) + sizeof( "\\armytmp" ) ) ){
					memcpy( g_szArmyTmpDir, g_szInstallDir, cbData - 1 );
					memcpy( &g_szArmyTmpDir[ cbData - 1 ], "\\armytmp", sizeof( "\\armytmp" ) );
				}
			}
		}
		RegCloseKey( hkRead );
	}
}


BOOL __stdcall DllEntryPoint( HINSTANCE hDll, DWORD dwReason, LPVOID lpvReserved )
{
	DllEntryPoint_DDraw( hDll, dwReason, lpvReserved ); 

	if( dwReason == DLL_PROCESS_ATTACH )
	{
		InitPaths();

		DWORD dwPrevProtect;	
		if( VirtualProtect( (void*)0x00401000, 0x000BC000, PAGE_EXECUTE_READWRITE, &dwPrevProtect ) ){
			armytmp::Load();
			camera_elevation::Load();
			heap_fix::Load();
			mixed_magic::Load();
			no_cd::Load();
			portrait_bk::Load();
			sp_mapbord::Load();
			sprite_table::Load();
			string_table::Load();
			windowed::Load();
			VirtualProtect( (void*)0x00401000, 0x000BC000, dwPrevProtect, &dwPrevProtect );
		}
	}
		
	return TRUE;
}

#pragma comment(linker, "/NODEFAULTLIB") // specifically no C runtime lib (for no real reason)
#pragma comment( lib, "kernel32" )  
#pragma comment( lib, "user32" )  
#pragma comment(linker, "/ENTRY:\"DllEntryPoint\"") // define entry point cause no C Lib
