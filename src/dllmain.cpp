#include <Windows.h>

//#include "ctl.h"
#include "darkomen.h"
#include "detour.h"
#include "modmenu.h"

extern "C" __declspec(dllexport) void __cdecl Darkomen(void) {}

HMODULE WINAPI Detoured()
{
	return 0;
}

typedef int (*drawBitmap_t)(void* handle, int x, int y, int a4, int a5, char* bitmappath);
typedef int (*drawText_t) (void* handle, int x, int y, int a4, int a5, void* font, char* text);
typedef void* (*drawSprite_t)(void* handle, int x, int y, int a4, int a5, void* hMenu, int spriteNum);
typedef char* (*convertPathString_t)(char* input);
typedef int (*multiplayerMessage_t)(int a1, int a2, char* text);
typedef void (*noarg_t)();

/*drawBitmap_t drawBitmap_orig = (drawBitmap_t)0x485230;
drawText_t drawText_orig = (drawText_t)0x4855A0;
drawSprite_t drawSprite_orig = (drawSprite_t)0x485130;
setTooltip_t setTooltip_orig = (setTooltip_t)0x4863A0;*/
convertPathString_t convertPathString_orig = (convertPathString_t)0x48A010;
multiplayerMessage_t multiplayerMessage_orig = (multiplayerMessage_t)0x423020;
noarg_t testFunc_orig = (noarg_t)0x414C39;

char* convertPathString(char* input) {
	char* result = convertPathString_orig(input);
	OutputDebugString(result);
	return result;
}

void applyHooks()
{
	DWORD oldProt;
	VirtualProtect((void*)0x410000, 0x80000, PAGE_EXECUTE_READWRITE, &oldProt);
	// NoCD Patch
	*(WORD*) 0x48A5E0 = 0x01BA;
#ifdef _DEBUG
	*(DWORD *) 0x004BF0A8 = 0; // Broken window mode hack
#endif
	//darkomen::ctl::applyHooksCTL();
	darkomen::detour::init();
	darkomen::modmenu::applyHooks();

	VirtualProtect((void*)0x410000, 0x80000, oldProt, NULL);
}
#include <fstream>
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID
					 )
{
    //patchItemcosts();
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		applyHooks();

    return TRUE;
}
