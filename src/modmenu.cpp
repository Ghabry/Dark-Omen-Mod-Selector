#include "modmenu.h"
#include "detour.h"
#include "functions.h"
#include "util.h"
#include "import_script.h"

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

	// Path to the Dark Omen directory
	std::string darkomenPath = "";
	// Path to the Dark Omen exe
	std::string darkomenExePath = "";
	// Path to the Mods directory
	std::string darkomenModPath = "";
	// Name of the current mod directory
	std::string currentMod = "";

	int lastHover = -1;

	// Modified bytes via patched EngRel
	std::vector<undoStruct> undoData;
	// EngRel was patched using a modified Prg.exe
	bool engrelPatched = false;
	// WHMTG script was loaded from whmtg.txt
	bool whmtgPatched = false;

	int selectModClicked(int, int, int, int)
	{
		showModMenu = 1;
		*(DWORD*)0x4D6F98 = 3; // Option Menu
		sub_41C320(0, 7, 255);
		sub_418020(9);
		//fprintf(a, "selectModClicked\n");
		return 1;
	}

	// Adds the SELECT MOD item to the main menu
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
			patchEngRel();
			loadWHMTG();
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

	// Sets the font for SELECT MOD
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
		// Mod list data structure seems to be:
		// Every element has size 308
		// Metadata can be stored at elementpos + 53 (here: mod folder name)

		free(modList);
		modList = 0;
		WIN32_FIND_DATA findData;
		std::string searchPath(darkomenModPath);
		searchPath += "\\*";
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
					std::string modfile(darkomenModPath + "\\");
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

					if (!strcmp(findData.cFileName, currentMod.c_str()))
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

	// Event handler when any menu item is hovered in the Mod Menu
	// No idea how that works, but other scenes do it the same way ;)
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

	// Event handler when any menu item in the Mod Menu is clicked
	int modMenuClicked(int a1, int, int, int)
	{
		modMenuState = 2;
		// Unknown purpose, other scenes do it the same way :P
		sub_41C320(0, 7, 255);
		sub_418020(9);

		if (a1 == 3) // Load button
		{
			// Selected item in the mod menu
			int selectedIndex = getSelectedListIndex_orig(modMenuHandle, 10);
			std::string lastMod(darkomenPath);
			lastMod += "\\Mods\\lastmod.ini";
			FILE* f = openFile(lastMod, "w");
			// First one is a special case to roll back to the original game
			if (selectedIndex <= 0)
			{
				// File already truncated by "w"
				detour::trace("Switching to: Original game");
				currentMod = "";
			}
			else
			{
				detour::trace("Switching to: %s", (modList + selectedIndex * 308 + 53));
				// The list is some very strange data structure ;)
				char buffer[MAX_PATH + 1] = { 0 };
				strncpy(buffer, (modList + selectedIndex * 308 + 53), MAX_PATH);
				currentMod = buffer;
				fprintf(f, "%s", currentMod.c_str());
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
		std::string lastMod(darkomenModPath);
		lastMod += "\\lastmod.ini";
		std::ifstream file(lastMod.c_str());
		if (!file.fail())
		{
			char buffer[MAX_PATH + 1] = { 0 };
			file.getline(buffer, MAX_PATH);
			currentMod = buffer;
			lastMod = getCurrentModPath();
			if (lastMod.empty() || getFileAttributes_orig(lastMod.c_str()) == -1)
			{
				detour::trace("Mod was invalid, reverting to original game");
				currentMod = "";
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
		char fileName[MAX_PATH + 1];
		GetFullPathName(lpFileName, MAX_PATH + 1, fileName, NULL);

		if (modHookFailed || currentMod.empty())
		{
			// No mod loaded
			return createFile_orig(lpFileName, dwDesiredAccess, dwShareMode,
				lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes,
				hTemplateFile);
		}
		detour::trace("CreateFile: %s", fileName);

		std::string newPath = toModPath(fileName);

		if (newPath.empty())
		{
			// File not in dark omen path
			return createFile_orig(lpFileName, dwDesiredAccess, dwShareMode,
				lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes,
				hTemplateFile);
		}

		HANDLE handle = createFile_orig(newPath.c_str(), dwDesiredAccess, dwShareMode,
			lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes,
			hTemplateFile);
		if (handle == INVALID_HANDLE_VALUE)
		{
			// The file does not exist in the mod directory, open the original
			// file instead
			return createFile_orig(lpFileName, dwDesiredAccess, dwShareMode,
				lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes,
				hTemplateFile);
		}

		detour::trace("Redirected to: %s", newPath.c_str());
		return handle;
	}

	HANDLE WINAPI MyFindFirstFileA(
		__in   LPCSTR lpFileName,
		__out  LPWIN32_FIND_DATA lpFindFileData
		)
	{
		char fileName[MAX_PATH + 1];
		GetFullPathName(lpFileName, MAX_PATH + 1, fileName, NULL);

		if (modHookFailed || currentMod.empty())
		{
			// No mod loaded
			return findFirstFile_orig(lpFileName, lpFindFileData);
		}

		detour::trace("FindFirstFile: %s", fileName);

		std::string newPath = toModPath(fileName);
		if (newPath.empty())
		{
			// File not in dark omen path
			return findFirstFile_orig(lpFileName, lpFindFileData);
		}

		std::string originalPath = toLowerCase(fileName);

		// Savegame and 2parm are always redirected
		// This way only mod armies and mod savegames are displayed

		// This redirection is only done for FindFirstFile because this
		// is the API used to scan 2parm and Savegame

		std::string dopath_lc = toLowerCase(darkomenPath);
		// Redirect the Savegame path
		std::string savePath(dopath_lc);
		savePath += "\\savegame";

		if (startsWith(originalPath, savePath)) {
			std::string modsavePath(getCurrentModPath() + "\\SaveGame");

			// Create directory if missing
			if (getFileAttributes_orig(modsavePath.c_str()) == -1)
			{
				detour::trace("Creating save directory: %s", modsavePath.c_str());
				if (!CreateDirectoryA(modsavePath.c_str(), NULL)) {
					detour::trace("ERROR: Directory creation failed");
				}
			}

			detour::trace("Redirected to: %s", newPath.c_str());
			return findFirstFile_orig(newPath.c_str(), lpFindFileData);
		}

		// Redirect 2parm
		std::string _2parm(dopath_lc);
		std::string gamedata = _2parm + "\\gamedata";
		_2parm += "\\gamedata\\2parm";

		if (startsWith(originalPath, _2parm)) {
			std::string modgamedata(getCurrentModPath() + "\\GameData");
			std::string mod2parm(getCurrentModPath() + "\\GameData\\2parm");

			// Create directory if missing
			if (getFileAttributes_orig(mod2parm.c_str()) == -1)
			{
				if (getFileAttributes_orig(modgamedata.c_str()) == -1) {
					detour::trace("Creating GameData directory: %s", modgamedata.c_str());
					if (!CreateDirectoryA(modgamedata.c_str(), NULL)) {
						detour::trace("ERROR: Directory creation failed");
					}
				}
				detour::trace("Creating 2parm directory: %s", mod2parm.c_str());
				if (!CreateDirectoryA(mod2parm.c_str(), NULL)) {
					detour::trace("ERROR: Directory creation failed");
				}
			}

			detour::trace("Redirected to: %s", newPath.c_str());
			return findFirstFile_orig(newPath.c_str(), lpFindFileData);
		}

		if (GetFileAttributesA(newPath.c_str()) == -1)
		{
			return findFirstFile_orig(lpFileName, lpFindFileData);
		}

		detour::trace("Redirected to: %s", newPath.c_str());

		return findFirstFile_orig(newPath.c_str(), lpFindFileData);
	}

	BOOL WINAPI MyDeleteFileA(
		__in  LPCTSTR lpFileName
		)
	{
		char fileName[MAX_PATH + 1];
		GetFullPathName(lpFileName, MAX_PATH + 1, fileName, NULL);

		if (modHookFailed || currentMod.empty())
		{
			// No mod loaded
			return deleteFile_orig(lpFileName);
		}

		detour::trace("DeleteFile: %s", fileName);

		std::string newPath = toModPath(fileName);

		if (newPath.empty())
		{
			// File not in dark omen path
			return deleteFile_orig(lpFileName);
		}

		if (getFileAttributes_orig(newPath.c_str()) == -1)
		{
			// Redirected file does not exist, delete original file instead
			return deleteFile_orig(lpFileName);
		}

		// Delete redirected file
		detour::trace("Redirected to: %s", newPath.c_str());

		return deleteFile_orig(newPath.c_str());
	}

	BOOL WINAPI MyCopyFileA(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists)
	{
		char fileNameExisting[MAX_PATH + 1];
		char fileNameNew[MAX_PATH + 1];
		GetFullPathName(lpExistingFileName, MAX_PATH + 1, fileNameExisting, NULL);
		GetFullPathName(lpNewFileName, MAX_PATH + 1, fileNameNew, NULL);
		bool redirectExisting = true;
		bool redirectNew = true;

		if (modHookFailed || currentMod.empty())
		{
			// No mod loaded
			return copyFile_orig(lpExistingFileName, lpNewFileName, bFailIfExists);
		}

		detour::trace("CopyFile: %s to %s", fileNameExisting, fileNameNew);

		std::string newPathExisting = toModPath(fileNameExisting);
		std::string newPathNew = toModPath(fileNameNew);

		if (newPathExisting.empty() && newPathNew.empty())
		{
			// Source and target not in dark omen path
			return copyFile_orig(lpExistingFileName, lpNewFileName, bFailIfExists);
		}

		if (newPathExisting.empty()) {
			// Source file not in dark omen path
			redirectExisting = false;
			newPathExisting = fileNameExisting;
		}

		if (newPathNew.empty()) {
			// Target file not in dark omen path
			redirectNew = false;
			newPathNew = fileNameNew;
		}

		if (redirectExisting && getFileAttributes_orig(newPathExisting.c_str()) == -1) {
			// File being copied exists in dark omen path but not in mod path -> use non-redirected name
			newPathExisting = lpExistingFileName;
		}

		if (redirectNew) {
			// New file is in Dark omen directory and being redirected
			// Try creating target directory

			std::string newPathNewDirectory = getPathOfFile(newPathNew);
			if (getFileAttributes_orig(newPathNewDirectory.c_str()) == -1) {
				detour::trace("Creating directory: %s", newPathNewDirectory.c_str());
				if (!CreateDirectoryA(newPathNewDirectory.c_str(), NULL)) {
					detour::trace("ERROR: Directory creation failed");
				}
			}
		}

		// When the source file exists in the mod directory it will be copied, otherwise the original
		// When the target file should be copied to the Dark Omen directory it points now to the mod dir

		// Copy File
		detour::trace("Redirected to: %s -> %s", newPathExisting.c_str(), newPathNew.c_str());

		return copyFile_orig(newPathExisting.c_str(), newPathNew.c_str(), bFailIfExists);
	}

	BOOL WINAPI MySetFileAttributes(LPCTSTR lpFileName, DWORD dwFileAttributes)
	{
		char fileName[MAX_PATH + 1];
		GetFullPathName(lpFileName, MAX_PATH + 1, fileName, NULL);

		if (modHookFailed || currentMod.empty())
		{
			// No mod loaded
			return setFileAttributes_orig(lpFileName, dwFileAttributes);
		}

		detour::trace("SetFileAttributes: %s", fileName);

		std::string newPath = toModPath(fileName);

		if (newPath.empty())
		{
			// File not in dark omen path
			return setFileAttributes_orig(lpFileName, dwFileAttributes);
		}

		if (getFileAttributes_orig(newPath.c_str()) == -1)
		{
			// Redirected file does not exist, use original file
			return setFileAttributes_orig(lpFileName, dwFileAttributes);
		}

		// Delete redirected file
		detour::trace("Redirected to: %s", newPath.c_str());

		return setFileAttributes_orig(newPath.c_str(), dwFileAttributes);
	}

	DWORD WINAPI MyGetFileAttributes(LPCTSTR lpFileName)
	{
		char fileName[MAX_PATH + 1];
		GetFullPathName(lpFileName, MAX_PATH + 1, fileName, NULL);

		if (modHookFailed || currentMod.empty())
		{
			// No mod loaded
			return getFileAttributes_orig(lpFileName);
		}

		detour::trace("GetFileAttributes: %s", fileName);

		std::string newPath = toModPath(fileName);

		if (newPath.empty())
		{
			// File not in dark omen path
			return getFileAttributes_orig(lpFileName);
		}

		DWORD result = getFileAttributes_orig(newPath.c_str());
		if (result == -1)
		{
			// Redirected file does not exist, use original file
			return getFileAttributes_orig(lpFileName);
		}

		detour::trace("Redirected to: %s", newPath.c_str());

		return result;
	}

	void applyHooks()
	{
		//detour::hookFunc(hookOptionMenuInit, 0x414BD7);
		//detour::hookFunc(hookOptionMenuInit2, 0x414C96);
		//*(DWORD*)0x414BD2 = 480; // Exit Pos Option Menu
		detour::trace("Modifying Main Menu");
		// Rearrage menu items
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

		detour::trace("Hooking CopyFile");
		copyFile_orig = (copyFile_t)DetourFunction((PBYTE)CopyFileA, (PBYTE)MyCopyFileA);

		detour::trace("Hooking SetFileAttributes");
		setFileAttributes_orig = (setFileAttributes_t)DetourFunction((PBYTE)SetFileAttributesA, (PBYTE)MySetFileAttributes);

		detour::trace("Hooking GetFileAttributes");
		getFileAttributes_orig = (getFileAttributes_t)DetourFunction((PBYTE)GetFileAttributesA, (PBYTE)MyGetFileAttributes);

		char buffer[MAX_PATH + 1] = { 0 };
		GetModuleFileNameA(NULL, buffer, MAX_PATH);
		darkomenExePath = buffer;

		detour::trace("GetModuleFilename: %s", darkomenExePath.c_str());

		// Go up twice (first is in exe directory, next in DO directory)
		std::string doPath = getPathOfFile(getPathOfFile(darkomenExePath));
		if (doPath != "")
		{
			// Set up everything
			darkomenPath = doPath;
			detour::trace("Dark Omen path: %s", darkomenPath.c_str());
			darkomenPath = doPath;
			darkomenModPath = darkomenPath + "\\Mods";
			detour::trace("Mod folder path: %s", darkomenModPath.c_str());
			if (getFileAttributes_orig(darkomenModPath.c_str()) != -1)
			{
				// Yeah!
				detour::trace("Mods folder found");
				detour::trace("Initialization was successful");
				modHookFailed = false;
			}
			updateCurrentMod();
			patchEngRel();
			loadWHMTG();
		}
		if (modHookFailed)
		{
			detour::trace("ERROR: Mods folder not found!");
			detour::trace("Initialization was NOT successful");
		}
	}

	// Patches the data segment of EngRel based on a patched EngRel in Prg dir
	void patchEngRel()
	{
		if (modHookFailed || engrelPatched)
		{
			return;
		}

		std::string modEngRelPath = getCurrentModPath();
		if (modEngRelPath.empty())
		{
			return;
		}

		// Path to modded EngRel patches are applied from
		modEngRelPath += "\\Prg\\EngRel.exe";

		FILE* modIn = openFile(modEngRelPath, "r");
		if (!modIn)
		{
			detour::trace("No EngRel found at %s. No patches applied.", modEngRelPath.c_str());
			return;
		}

		FILE* realIn = openFile(darkomenExePath, "r");
		if (!realIn)
		{
			detour::trace("ERROR: Couldn't access EngRel at %s. PLEASE REPORT THIS!", darkomenExePath.c_str());
			return;
		}

		detour::trace("Found EngRel at %s", modEngRelPath.c_str());

		// Read the data segment
		// BD000 -> 4BF000
		// FF3FF -> 5013FF
		fseek(modIn, 0xbd000, SEEK_SET);
		fseek(realIn, 0xbd000, SEEK_SET);

		const int dataseg_size = 271359;
		char modData[dataseg_size];
		char origData[dataseg_size];

		fread(modData, 1, dataseg_size, modIn);
		fread(origData, 1, dataseg_size, realIn);

		fclose(modIn);
		fclose(realIn);

		undoStruct undoStr;
		for (int i = 0; i < dataseg_size; ++i)
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

	// Revert EngRel changes
	void undoChanges()
	{
		if (whmtgPatched) {
			detour::trace("WHMTG: Unloading script");
			UnloadScript();
			whmtgPatched = false;
		}

		if (!engrelPatched) {
			return;
		}

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

	void loadWHMTG() {
		if (whmtgPatched) {
			return;
		}

		if (currentMod.empty()) {
			return;
		}

		std::string whmtg = getCurrentModPath() + "\\whmtg.txt";

		if (getFileAttributes_orig(whmtg.c_str()) == -1)
		{
			detour::trace("No whmtg.txt found at %s. No script loaded.", whmtg.c_str());
			return;
		}

		if (ImportScript(whmtg.c_str())) {
			whmtgPatched = true;
			detour::trace("WHMTG script loaded.");
		}
		else {
			detour::trace("ERROR: WHMTG script loading failed.");
		}
	}

	// Get path of currently enabled mod
	std::string getCurrentModPath()
	{
		if (currentMod.empty())
		{
			detour::trace("Current Mod: None (Original Game)");
			return "";
		}

		std::string modPath = darkomenModPath;
		modPath += "\\" + currentMod;

		detour::trace("Current Mod: %s", currentMod.c_str());
		detour::trace("Current Mod Path: %s", modPath.c_str());

		return modPath;
	}

	bool isInDarkOmenPath(const std::string& path) {
		std::string p = toLowerCase(path);
		std::string dopath = toLowerCase(darkomenPath);
		return startsWith(p, dopath);
	}

	std::string toModPath(const std::string& path) {
		if (!isInDarkOmenPath(path)) {
			return "";
		}

		size_t dopath_size = darkomenPath.size();

		std::string subdir = path.substr(dopath_size);

		return getCurrentModPath() + subdir;
	}
}
}
