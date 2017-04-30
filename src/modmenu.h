#pragma once

#include <windows.h>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <vector>
#include "detours.h"

namespace darkomen {
namespace modmenu {

	/**
	 * The mod menu hooks the option menu.
	 * When this flag is set the mod menu is loaded instead of the option
	 * menu.
	 */
	extern bool showModMenu;

	//FILE* a = fopen("!blub.txt", "w");

	extern DWORD* hookMainMenuInitRet;

	extern bool modHookFailed;
	
	extern DWORD* hookMainMenuInitRet2;
	extern DWORD* hookMainMenuInitVar2;

	extern int modMenuState;
	extern void* modMenuHandle;
	extern char* modList;

	extern std::string darkomenPath;
	extern std::string darkomenExePath;
	extern std::string darkomenModPath;
	extern std::string currentMod;

	extern int lastHover;

	struct undoStruct;
	extern std::vector<undoStruct> undoData;
	extern bool engrelPatched;
	extern bool whmtgPatched;

	int selectModClicked(int, int, int, int);

	void hookMainMenuInitImpl();

	void hookMainMenuInit();

	void hookMainMenuInitImpl2();

	void hookMainMenuInit2();

	/**
	 * Fills the List Control of the Mod Menu Scene with items
	 */
	int updateModList();

	/**
	 * Event handler for button hovering in the Mod Menu Scene
	 */
	int modMenuHovered(int a1, int a2, int a3, int id);

	/**
	 * Event handler for the buttons in the Mod Menu Scene
	 */
	int modMenuClicked(int a1, int a2, int a3, int a4);

	/**
	 * Implements the Mod Menu Scene
	 */
	int modMenu();

	/**
	 * Reads lastmod.ini and sets currentMod to the name of the mod if the
	 * last mod entry is valid.
	 */
	void updateCurrentMod();

	HANDLE WINAPI MyCreateFileA(
		__in      LPCSTR lpFileName,
		__in      DWORD dwDesiredAccess,
		__in      DWORD dwShareMode,
		__in_opt  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		__in      DWORD dwCreationDisposition,
		__in      DWORD dwFlagsAndAttributes,
		__in_opt  HANDLE hTemplateFile
		);

	HANDLE WINAPI MyFindFirstFileA(
		__in   LPCSTR lpFileName,
		__out  LPWIN32_FIND_DATA lpFindFileData
	);

	BOOL WINAPI MyDeleteFileA(
		__in  LPCTSTR lpFileName
	);

	BOOL WINAPI MyCopyFileA(
		_In_ LPCTSTR lpExistingFileName,
		_In_ LPCTSTR lpNewFileName,
		_In_ BOOL    bFailIfExists
	);

	BOOL WINAPI MySetFileAttributes(
		_In_ LPCTSTR lpFileName,
		_In_ DWORD   dwFileAttributes
	);

	DWORD WINAPI MyGetFileAttributes(
		_In_ LPCTSTR lpFileName
	);

	BOOL WINAPI MySetCurrentDirectory(
		_In_ LPCTSTR lpPathName
		);

	LRESULT CALLBACK MyWindowProc(
		_In_ HWND   hwnd,
		_In_ UINT   uMsg,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam
	);

	/**
	 * Hooked version of replacePath.
	 * The original converts stuff like [2PARM] to the path equivalent.
	 * The hook modifies the path for savegames and 2parm.
	 */
	//char* replacePath(char* path);

	/** 
	 * Applies all hooks to Dark Omen
	 */
	void applyHooks();

	void patchEngRel();

	void undoChanges();

	void loadWHMTG();

	void loadXSlots();

	std::string getCurrentModPath();

	bool isInDarkOmenPath(const std::string& path);
	std::string toModPath(const std::string& path);
}
}
