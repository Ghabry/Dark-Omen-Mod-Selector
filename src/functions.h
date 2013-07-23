#pragma once
typedef int (*eventFunc_t)(int arg1, int arg2, int arg3, int arg4);
typedef void (*addLabel_t)(void* scene, int x, int y, __int16 id, int unk, void* font, const char* text);
typedef void (*addLabelEventHandler_t)(void* scene, int x, int y, __int16 id_plus1, int unk_12288, int width, int height, int unk_val2, eventFunc_t onHover, eventFunc_t onClick, int unk2, int unk3, int id);
typedef void (*addListCtrl_t)(int a1, int a2, int a3, __int16 a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, int a12, int a13, int a14, int a15, int a16, int a17, const char* str, int a19);
typedef void (*setTooltip_t)(void* scene, __int16 id, const char* tooltip);
typedef void (*sub_487640_t)(void* scene, int id, void* font);
typedef void (*sub_41C320_t)(int a1, int a2, int a3);
typedef int (*getTextWidth_t)(void* font, const char* text);
typedef int (*getFontHeight_t)(void* font);
typedef int (*noarg_int_t)();
typedef int (*intarg_int_t)(int a);
typedef void* (*createScene_t)(char* picture, int x, int y);
typedef void* (*openSpriteFile_t)(char* file);
typedef char* (*replacePath_t)(char* path);
typedef void (*disableLabel_t)(void* scene, __int16 id);
typedef int (*getSelectedListIndex_t)(void* scene, __int16 id);
typedef void (*freeScene_t)(void* scene);
typedef HANDLE (WINAPI *createFile_t)(
	__in      LPCSTR lpFileName,
	__in      DWORD dwDesiredAccess,
	__in      DWORD dwShareMode,
	__in_opt  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	__in      DWORD dwCreationDisposition,
	__in      DWORD dwFlagsAndAttributes,
	__in_opt  HANDLE hTemplateFile
	);
typedef HANDLE (WINAPI *findFirstFile_t)(
	__in   LPCSTR lpFileName,
	__out  LPWIN32_FIND_DATA lpFindFileData
	);
typedef BOOL (WINAPI* deleteFile_t)(
	__in  LPCSTR lpFileName
	);

/** CreateFileA */
createFile_t createFile_orig = (createFile_t)CreateFileA;
findFirstFile_t findFirstFile_orig = (findFirstFile_t)FindFirstFileA;
deleteFile_t deleteFile_orig = (deleteFile_t)DeleteFileA;
/**	Adds a label to the Dark Omen Gui */
addLabel_t addLabel_orig = (addLabel_t)0x4855A0;
/** Assigns a label to a Dark Omen Gui Element */
setTooltip_t setTooltip_orig = (setTooltip_t)0x486300;
sub_487640_t sub_487640 = (sub_487640_t)0x487640;
sub_41C320_t sub_41C320 = (sub_41C320_t)0x41C320;
getTextWidth_t getTextWidth_orig = (getTextWidth_t)0x481930;
getFontHeight_t getFontHeight_orig = (getFontHeight_t)0x4819D0;
addLabelEventHandler_t addLabelEventHandler_orig = (addLabelEventHandler_t)0x484E60;
eventFunc_t menuMenuLabelHovered_orig = (eventFunc_t)0x42C750;
noarg_int_t optionMenu_orig = (noarg_int_t)0x4140D0;
createScene_t createScene_orig = (createScene_t)0x483A80;
openSpriteFile_t openSpriteFile_orig = (openSpriteFile_t)0x4821C0;
addListCtrl_t addListCtrl_orig = (addListCtrl_t)0x485CE0;
replacePath_t replacePath_orig = (replacePath_t)0x48A010;
disableLabel_t disableLabel_orig = (disableLabel_t)0x4878F0;
getSelectedListIndex_t getSelectedListIndex_orig = (getSelectedListIndex_t)0x4878A0;
freeScene_t freeScene_orig = (freeScene_t)0x483D40;

intarg_int_t sub_418020 = (intarg_int_t)0x418020;
noarg_int_t sub_4820A0 = (noarg_int_t)0x4820A0;

intarg_int_t sub_483FF0 = (intarg_int_t)0x483FF0;
intarg_int_t sub_484860 = (intarg_int_t)0x484860;
intarg_int_t sub_484C40 = (intarg_int_t)0x484C40;
