#pragma once

#include <windows.h>

#define Log

extern char g_szInstallDir[ MAX_PATH ];
extern char g_szArmyTmpDir[ MAX_PATH ];

namespace armytmp			{ void Load(); void Unload(); }
namespace camera_elevation	{ void Load(); void Unload(); }
namespace heap_fix			{ void Load(); void Unload(); }
namespace mixed_magic		{ void Load(); void Unload(); }
namespace no_cd				{ void Load(); void Unload(); }
namespace portrait_bk		{ void Load(); void Unload(); }
namespace sp_mapbord		{ void Load(); void Unload(); }
namespace sprite_table		{ void Load(); void Unload(); }
namespace string_table		{ void Load(); void Unload(); }
namespace windowed			{ void Load(); void Unload(); }

// helpers.cpp
void SkipWhiteSpaceAndComments( char*& str );
DWORD ReadOutInteger( char* src, __out_opt DWORD* src_bytes_read );
DWORD ReadOutWord( char* dst, DWORD dst_size, char* src, __out_opt DWORD* src_bytes_read );
char* ReadInTextFile( const char* szFileName );