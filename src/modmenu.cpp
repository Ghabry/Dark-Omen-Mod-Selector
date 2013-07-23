#include "modmenu.h"
#include "detour.h"
#include "functions.h"


namespace darkomen {
namespace modmenu {
	struct undoStruct {
		int addr;
		char value;
	};

	bool showModMenu = false;

	DWORD* hookMainMenuInitRet = (DWORD*)0x42C434;

	bool modHookFailed = true;

	DWORD* hookMainMenuInitRet2 = (DWORD*)0x42C5B2;
	DWORD* hookMainMenuInitVar2 = (DWORD*)0x4D6FA4;

	int modMenuState = 0;
	void* modMenuHandle = 0;
	char* modList = 0;

	char darkomenPath[MAX_PATH + 1] = {0};
	char darkomenFullPath[MAX_PATH + 1] = {0};
	char currentMod[MAX_PATH + 1] = {0};

	int lastHover = -1;

	std::vector<undoStruct> undoData;
	bool engrelPatched = false;

	int selectModClicked(int, int, int, int)
	{
		showModMenu = 1;
		*(DWORD*)0x4D6F98 = 3; // Option Menu
		sub_41C320(0, 7, 255);
		sub_418020(9);
		//fprintf(a, "selectModClicked\n");
		return 1;
	}

	void hookMainMenuInitImpl() {
		//fprintf(a, "testHook MainMenu geth\n");
		int* scene = *(int**)0x5022A0;
		int* font = *(int**)0x526E3C;
		int width = getTextWidth_orig(font, "SELECT MOD");
		int height = getFontHeight_orig(font);
		detour::trace("Main Menu: Adding Select Mod item");
		addLabel_orig(scene, 320 - width / 2, 385, 12, 0, font, "SELECT MOD");
		if (modHookFailed)
		{
			detour::trace("Main Menu: Not properly initialized, disabling item");
			disableLabel_orig(scene, 12);
		}
		else
		{
			addLabelEventHandler_orig(scene, 320 - width / 2, 390 - height, 13, 12288, width, height, 2, menuMenuLabelHovered_orig, selectModClicked, 0, 0, 12);
			if (!engrelPatched)
			{
				patchEngRel();
			}
		}
	}

	__declspec(naked) void hookMainMenuInit()
	{
		__asm
		{
			call getTextWidth_orig;
			pushad;
			pushfd;
		}

		hookMainMenuInitImpl();

		__asm
		{
			popfd;
			popad;
			jmp hookMainMenuInitRet;
		}
	}

	void hookMainMenuInitImpl2() {
		//fprintf(a, "testHook MainMenu2 geth\n");
		int* scene = *(int**)0x5022A0;
		int* font = *(int**)0x526E3C;
		sub_487640(scene, 12, font);
	}

	__declspec(naked) void hookMainMenuInit2()
	{
		__asm
		{
			mov hookMainMenuInitVar2, 0;
			pushad;
			pushfd;
		}


		hookMainMenuInitImpl2();

		__asm
		{
			popfd;
			popad;
			jmp hookMainMenuInitRet2;
		}
	}

	int updateModList()
	{
		free(modList);
		modList = 0;
		WIN32_FIND_DATA findData;
		std::string modPath(darkomenPath);
		modPath += "\\Mods\\";
		std::string searchPath(modPath);
		searchPath += "*";
		HANDLE handle = findFirstFile_orig(searchPath.c_str(), &findData);
		int dircount = 0;
		bool first = true;
		if (handle != INVALID_HANDLE_VALUE)
		{
			while (first || FindNextFile(handle, &findData))
			{
				first = false;
				if (findData.cFileName[0] != '.' && (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					++dircount;
				}
			}
			FindClose(handle);
		}

		detour::trace("Mod Menu: %d mod folders found", dircount);

		if (dircount == 0)
		{
			modList = (char*)calloc(2, 308);
			strcpy(modList, "Original Game");
			strcpy(modList + 308, "END OF LIST");
			return 0;
		}

		modList = (char*)calloc(dircount + 2, 308);
		strcpy(modList, "Original Game");

		handle = findFirstFile_orig(searchPath.c_str(), &findData);
		int i = 1;
		int index = 0;
		first = true;
		if (handle != INVALID_HANDLE_VALUE)
		{
			while (first || FindNextFile(handle, &findData))
			{
				first = false;
				if (findData.cFileName[0] != '.' && (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					std::string modfile(modPath);
					modfile += findData.cFileName;
					detour::trace("Checking Mod: %s", findData.cFileName);
					modfile += "\\Mod.ini";
					std::ifstream file(modfile);
					if (file.fail())
					{
						detour::trace("ERROR: Can't access %s", modfile.c_str());
						continue;
					}

					file.getline(modList + i * 308, 51);
					if ((modList + i * 308) == NULL)
					{
						detour::trace("ERROR: First line of %s is empty", modfile.c_str());
						continue;
					}

					if (!strcmp(findData.cFileName, currentMod))
					{
						index = i;
					}

					detour::trace("Mod is valid");
					strncpy(modList + i * 308 + 53, findData.cFileName, 252);
					file.close();
					++i;
				}
			}
			FindClose(handle);
		}
		strcpy(modList + i * 308, "END OF LIST");
		return index;
	}

	int modMenuHovered(int, int, int, int id)
	{
		int* font = *(int**)0x526D70;
		sub_487640(modMenuHandle, id, font);
		if (id != lastHover)
		{
			lastHover = id;
			sub_41C320(0, 5, 128);
		}
		return 1;
	}

	int modMenuClicked(int a1, int, int, int)
	{
		modMenuState = 2;
		sub_41C320(0, 7, 255);
		sub_418020(9);

		if (a1 == 3) // Load
		{

			int selectedIndex = getSelectedListIndex_orig(modMenuHandle, 10);
			std::string lastMod(darkomenPath);
			lastMod += "\\Mods\\lastmod.ini";
			FILE* f = fopen(lastMod.c_str(), "w");
			if (selectedIndex <= 0)
			{
				detour::trace("Switching to: Original game");
				currentMod[0] = '\0';
			}
			else
			{
				detour::trace("Switching to: %s", (modList + selectedIndex * 308 + 53));
				strncpy(currentMod, (modList + selectedIndex * 308 + 53), MAX_PATH);
				fprintf(f, "%s", currentMod);
			}
			fclose(f);
			undoChanges();
		}

		return 1;
	}

	int modMenu()
	{
		if (showModMenu)
		{
			if (modMenuState == 0)
			{
				detour::trace("Loading Mod Menu");
				int* font = *(int**)0x526E3C;
				int* font_booksw = *(int**)0x526E28;
				int* font_books = *(int**)0x526D7C;
				//*(int*)0x4F87C0 = (int)openSpriteFile_orig("[BOOKS]\\bookbut.spr");
				*(int*)0x527288 = (int)openSpriteFile_orig("[BOOKS]\\Menubut.spr");
				*(int*)0x527238 = (int)openSpriteFile_orig("[BOOKS]\\hilight.spr");
				//*(int*)0x539D98 = (int)openSpriteFile_orig("[BOOKS]\\scroll.spr");
				void* menubut_spr = *(int**)0x527288;
				void* hilight_spr = *(int**)0x527238;
				modMenuHandle = createScene_orig("[PICTURES]\\LOADGAME.BMP",0,0);
				int width = getTextWidth_orig(font, "SELECT MOD");
				int height = getFontHeight_orig(font);
				addLabel_orig(modMenuHandle, 320 - width / 2, 43, 0, 0, font, "SELECT MOD");
				int loadWidth = getTextWidth_orig(font, "LOAD");
				int exitWidth = getTextWidth_orig(font, "EXIT");
				int loadPos = (-40 - exitWidth - loadWidth) / 2 + 320;
				addLabel_orig(modMenuHandle, loadPos,
					455, 2, 0, font, "LOAD");
				addLabel_orig(modMenuHandle, loadWidth + loadPos + 40, 455, 4, 0, font, "EXIT");
				addLabelEventHandler_orig(modMenuHandle, loadPos, 455-height, 3, 12288,
					loadWidth, height, 2, modMenuHovered, modMenuClicked, 0, 0, 2);
				addLabelEventHandler_orig(modMenuHandle, loadWidth + loadPos + 40, 455-height, 5, 12288,
					exitWidth, height, 2, modMenuHovered, modMenuClicked, 0, 0, 4);
				addListCtrl_orig((int)modMenuHandle, 174, 83, 10, 2304, 293, 270, (int)menubut_spr,
					0, 473, 86, 473, 328, (int)hilight_spr, 0, (int)font_booksw, (int)font_books,
					(const char*)modList, updateModList());

				modMenuState = 1;
				sub_418020(0);
				sub_4820A0();
			}
			else if (modMenuState == 1)
			{
				int* font = *(int**)0x526E3C;
				sub_483FF0((int)modMenuHandle);
				sub_484860((int)modMenuHandle);
				sub_484C40((int)modMenuHandle);
				sub_487640(modMenuHandle, 2, font);
				sub_487640(modMenuHandle, 4, font);
			}
			else
			{
				modMenuState = 0;
				showModMenu = false;
				freeScene_orig(modMenuHandle);
				modMenuHandle = 0;
				lastHover = -1;
				detour::trace("Unloading Mod Menu (returning to Main Menu)");
				return 8;
			}
			//showModMenu = 0;
			return -1;
		}
		else
		{
			return optionMenu_orig();
		}
	}

	void updateCurrentMod()
	{
		std::string lastMod(darkomenPath);
		lastMod += "\\Mods\\lastmod.ini";
		std::ifstream file(lastMod.c_str());
		if (!file.fail())
		{
			file.getline(currentMod, MAX_PATH);
			lastMod = getCurrentModPath();
			if (!strcmp(lastMod.c_str(), "") || GetFileAttributesA(lastMod.c_str()) == -1)
			{
				detour::trace("Mod was invalid, reverting to original game");
				currentMod[0] = '\0';
			}
			file.close();
		}
	}

	HANDLE WINAPI MyCreateFileA(
		__in      LPCSTR lpFileName,
		__in      DWORD dwDesiredAccess,
		__in      DWORD dwShareMode,
		__in_opt  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		__in      DWORD dwCreationDisposition,
		__in      DWORD dwFlagsAndAttributes,
		__in_opt  HANDLE hTemplateFile
		)
	{
		char _path[MAX_PATH + 1];
		GetFullPathName(lpFileName, MAX_PATH + 1, _path, NULL);

		if (modHookFailed || currentMod[0] == '\0')
		{
			return createFile_orig(_path, dwDesiredAccess, dwShareMode,
				lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes,
				hTemplateFile);
		}
		detour::trace("CreateFile: %s", _path);

		std::string basePath(darkomenPath);
		std::transform(basePath.begin(), basePath.end(), basePath.begin(), ::tolower);
		std::string newPath(_path);
		std::transform(newPath.begin(), newPath.end(), newPath.begin(), ::tolower);

		unsigned int pos = newPath.find(basePath);
		if (pos == std::string::npos)
		{
			return createFile_orig(_path, dwDesiredAccess, dwShareMode,
				lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes,
				hTemplateFile);
		}

		pos += strlen(basePath.c_str());

		newPath = getCurrentModPath(false);

		const char* secondPart = _path + pos;

		newPath += secondPart;

		const char* _newPath = newPath.c_str();

		HANDLE handle = createFile_orig(_newPath, dwDesiredAccess, dwShareMode,
			lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes,
			hTemplateFile);
		if (handle == INVALID_HANDLE_VALUE)
		{
			return createFile_orig(_path, dwDesiredAccess, dwShareMode,
				lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes,
				hTemplateFile);
		}
		detour::trace("Redirected to: %s", _newPath);
		return handle;
	}

	HANDLE WINAPI MyFindFirstFileA(
		__in   LPCSTR lpFileName,
		__out  LPWIN32_FIND_DATA lpFindFileData
		)
	{
		char* _path = (char*)lpFileName;

		if (modHookFailed || currentMod[0] == '\0')
		{
			return findFirstFile_orig(lpFileName, lpFindFileData);
		}

		detour::trace("FindFirstFile: %s", _path);

		// Replace the Savegame path
		std::string savePath(darkomenPath);
		savePath += "\\SaveGame";
		std::transform(savePath.begin(), savePath.end(), savePath.begin(), ::tolower);

		// Replace 2parm
		std::string _2parm(darkomenPath);
		_2parm += "\\gamedata\\2parm";
		std::transform(_2parm.begin(), _2parm.end(), _2parm.begin(), ::tolower);

		std::string newPath(_path);
		std::transform(newPath.begin(), newPath.end(), newPath.begin(), ::tolower);

		unsigned int pos = newPath.find(savePath);
		unsigned int pos2 = newPath.find(_2parm);
		if (pos != std::string::npos)
		{
			static bool firstTime = true;
			if (firstTime)
			{
				firstTime = false;
				return findFirstFile_orig(lpFileName, lpFindFileData);
			}
			pos += strlen(savePath.c_str());

			std::string newPath = getCurrentModPath(false);
			newPath += "\\Savegame";

			char* secondPart = _path + pos;

			newPath += secondPart;

			const char* _newPath = newPath.c_str();

			detour::trace("Redirected to: %s", _newPath);

			return findFirstFile_orig(_newPath, lpFindFileData);
		}
		else if (pos2 != std::string::npos)
		{
			static bool firstTime = true;
			if (firstTime)
			{
				firstTime = false;
				return findFirstFile_orig(lpFileName, lpFindFileData);
			}
			pos2 += strlen(_2parm.c_str());

			std::string newPath = getCurrentModPath(false);
			newPath += "\\GameData\\2parm";

			char* secondPart = _path + pos2;

			newPath += secondPart;

			const char* _newPath = newPath.c_str();

			detour::trace("Redirected to: %s", _newPath);

			return findFirstFile_orig(_newPath, lpFindFileData);
		}

		return findFirstFile_orig(lpFileName, lpFindFileData);
	}

	BOOL WINAPI MyDeleteFileA(
		__in  LPCTSTR lpFileName
		)
	{
		char _path[MAX_PATH + 1];
		GetFullPathName(lpFileName, MAX_PATH + 1, _path, NULL);

		if (modHookFailed || currentMod[0] == '\0')
		{
			return deleteFile_orig(lpFileName);
		}

		detour::trace("DeleteFile: %s", _path);

		std::string basePath(darkomenPath);
		std::transform(basePath.begin(), basePath.end(), basePath.begin(), ::tolower);
		std::string newPath(_path);
		std::transform(newPath.begin(), newPath.end(), newPath.begin(), ::tolower);

		unsigned int pos = newPath.find(basePath);
		if (pos == std::string::npos)
		{
			return deleteFile_orig(lpFileName);
		}
		pos += strlen(basePath.c_str());

		newPath = getCurrentModPath(false);

		const char* secondPart = _path + pos;

		newPath += secondPart;

		const char* _newPath = newPath.c_str();

		if (GetFileAttributesA(_newPath) == -1)
		{
			return deleteFile_orig(lpFileName);
		}
		detour::trace("Redirected to: %s", _newPath);
		return deleteFile_orig(_newPath);
	}

	void applyHooks()
	{
		//detour::hookFunc(hookOptionMenuInit, 0x414BD7);
		//detour::hookFunc(hookOptionMenuInit2, 0x414C96);
		//*(DWORD*)0x414BD2 = 480; // Exit Pos Option Menu
		detour::trace("Modifying Main Menu");
		*(DWORD*)0x42C1E9 = 250-25; // New Campaign
		*(DWORD*)0x42C208 = 250-25;

		*(DWORD*)0x42C25D = 290-25; // Load
		*(DWORD*)0x42C289 = 290-25;

		*(DWORD*)0x42C2F1 = 330-25; // Multiplayer
		*(DWORD*)0x42C30E = 330-25;

		*(DWORD*)0x42C368 = 370-25; // Tutorial
		*(DWORD*)0x42C385 = 370-25;

		*(DWORD*)0x42C3DF = 410+15; // Options
		*(DWORD*)0x42C3FC = 410+15;

		*(DWORD*)0x42C455 = 450+15; // Quit
		*(DWORD*)0x42C472 = 450+15;

		detour::hookFunc(hookMainMenuInit, 0x42C42F);
		detour::hookFunc(hookMainMenuInit2, 0x42C5A8);

		// Hook Option Menu and show Mod Menu instead
		detour::trace("Hooking Option Menu");
		optionMenu_orig = (noarg_int_t)DetourFunction((PBYTE)optionMenu_orig, (PBYTE)modMenu);

		//replacePath_orig = (replacePath_t)DetourFunction((PBYTE)replacePath_orig, (PBYTE)replacePath);

		detour::trace("Hooking CreateFile");
		createFile_orig = (createFile_t)DetourFunction((PBYTE)CreateFileA, (PBYTE)MyCreateFileA);

		detour::trace("Hooking FindFirstFile");
		findFirstFile_orig = (findFirstFile_t)DetourFunction((PBYTE)FindFirstFileA, (PBYTE)MyFindFirstFileA);

		detour::trace("Hooking DeleteFile");
		deleteFile_orig = (deleteFile_t)DetourFunction((PBYTE)DeleteFileA, (PBYTE)MyDeleteFileA);

		GetModuleFileNameA(NULL, darkomenPath, MAX_PATH);
		GetModuleFileNameA(NULL, darkomenFullPath, MAX_PATH);
		detour::trace("GetModuleFilename: %s", darkomenPath);
		if (strrchr(darkomenPath, '\\') != NULL)
		{
			strrchr(darkomenPath, '\\')[0] = '\0';
			if (strrchr(darkomenPath, '\\') != NULL)
			{
				strrchr(darkomenPath, '\\')[0] = '\0';
				detour::trace("Dark Omen path: %s", darkomenPath);
				std::string lastMod(darkomenPath);
				lastMod += "\\Mods";
				detour::trace("Mod folder path: %s", lastMod.c_str());
				if (GetFileAttributes(lastMod.c_str()) != -1)
				{
					detour::trace("Mods folder found");
					detour::trace("Initialization was successful");
					modHookFailed = false;
				}
				updateCurrentMod();
				patchEngRel();
			}
		}
		if (modHookFailed)
		{
			detour::trace("ERROR: Mods folder not found!");
			detour::trace("Initialization was NOT successful");
		}
	}

	void patchEngRel()
	{
		if (modHookFailed || engrelPatched)
		{
			return;
		}

		std::string modPath = getCurrentModPath();
		if (!strcmp(modPath.c_str(), ""))
		{
			return;
		}
		modPath += "\\Prg\\EngRel.exe";

		std::ifstream modIn(modPath.c_str(), std::ios::in | std::ios::binary);
		if (modIn.fail())
		{
			detour::trace("No EngRel found at %s", modPath.c_str());
			return;
		}
		std::ifstream realIn(darkomenFullPath, std::ios::in | std::ios::binary);
		if (realIn.fail())
		{
			detour::trace("ERROR: Couldn't access EngRel at %s. PLEASE REPORT THIS!", darkomenFullPath);
			return;
		}

		detour::trace("Found EngRel at %s", modPath.c_str());

		// BD000 -> 4BF000
		// FF3FF -> 5013FF
		modIn.seekg(0xbd000, std::ios::beg);
		realIn.seekg(0xbd000, std::ios::beg);

		char modData[271359];
		char origData[271359];

		modIn.read(modData, 271359);
		realIn.read(origData, 271359);

		modIn.close();
		realIn.close();

		undoStruct undoStr;
		for (int i = 0; i < 271359; ++i)
		{
			if (modData[i] != origData[i])
			{
				undoStr.addr = i;
				undoStr.value = origData[i];
				undoData.push_back(undoStr);
				char* data = (char*)(0x4BF000 + i);
				*data = modData[i];
			}
		}

		detour::trace("EngRel has been patched (%d changes applied)", undoData.size());

		engrelPatched = true;
	}

	void undoChanges()
	{
		detour::trace("Reverting EngRel to original version");

		for (size_t i = 0; i < undoData.size(); ++i)
		{
			char* addr = (char*)(0x4BF000 + undoData[i].addr);
			char val = undoData[i].value;
			*addr = val;
		}

		detour::trace("%d changes have been reverted", undoData.size());

		undoData.clear();
		engrelPatched = false;
	}

	std::string getCurrentModPath(bool trace)
	{
		if (currentMod[0] == '\0')
		{
			if (trace)
				detour::trace("Current Mod: None (Original Game)");
			return "";
		}
		std::string modPath = darkomenPath;
		modPath += "\\Mods\\";
		modPath += currentMod;
		if (trace)
		{
			detour::trace("Current Mod: %s", currentMod);
			detour::trace("Current Mod Path: %s", modPath.c_str());
		}
		return modPath;
	}
}
}
