#pragma once

#include <windows.h>

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
extern createFile_t createFile_orig;
extern findFirstFile_t findFirstFile_orig;
extern deleteFile_t deleteFile_orig;
/**	Adds a label to the Dark Omen Gui */
extern addLabel_t addLabel_orig;
/** Assigns a label to a Dark Omen Gui Element */
extern setTooltip_t setTooltip_orig;
extern sub_487640_t sub_487640;
extern sub_41C320_t sub_41C320;
extern getTextWidth_t getTextWidth_orig;
extern getFontHeight_t getFontHeight_orig;
extern addLabelEventHandler_t addLabelEventHandler_orig;
extern eventFunc_t menuMenuLabelHovered_orig;
extern noarg_int_t optionMenu_orig;
extern createScene_t createScene_orig;
extern openSpriteFile_t openSpriteFile_orig;
extern addListCtrl_t addListCtrl_orig;
extern replacePath_t replacePath_orig;
extern disableLabel_t disableLabel_orig;
extern getSelectedListIndex_t getSelectedListIndex_orig;
extern freeScene_t freeScene_orig;

extern intarg_int_t sub_418020;
extern noarg_int_t sub_4820A0;

extern intarg_int_t sub_483FF0;
extern intarg_int_t sub_484860;
extern intarg_int_t sub_484C40;
