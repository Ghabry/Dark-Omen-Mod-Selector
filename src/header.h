#include <windows.h>

#define HOOK_CALL( dst, src ) *((DWORD*)(((BYTE*)src) + 1)) = (((DWORD)dst) - ((DWORD)src) - 5); 
#define WRITE_JMP( dst, src ) *((BYTE*)src) = 0xE9; *((DWORD*)(((BYTE*)src) + 1)) = (((DWORD)dst) - ((DWORD)src) - 5); 
#define FUNC( name, address, ret_type, call_convention, args ) ret_type(call_convention * const name)args = (ret_type(call_convention *)args) address;
#define PFNC( name, address, ret_type, call_convention, args ) static ret_type (call_convention *& name)args = *( (ret_type(call_convention **)args)address);
#define DATA( name, type, address ) static type& name = (*((type*)address));

BOOL __stdcall DllEntryPoint_DDraw( HINSTANCE hDll, DWORD dwReason, LPVOID lpvReserved );

void* __cdecl memcpy( void *to, const void *from, size_t count );


extern char g_szInstallDir[ MAX_PATH ];
extern char g_szArmyTmpDir[ MAX_PATH ];

namespace armytmp			{ void Load(); void Unload(); }
namespace camera_elevation	{ void Load(); void Unload(); }
namespace heap_fix			{ void Load(); void Unload(); }
namespace mapboard			{ void Load(); void Unload(); }
namespace mixed_magic		{ void Load(); void Unload(); }
namespace no_cd				{ void Load(); void Unload(); }
namespace display			{ void Load(); void Unload(); }
namespace xslots			{ void Load(); void Unload(); }


// helpers.cpp
char* ReadInFile( const char* szFileName );
DWORD ReadOutWord( char* dst, DWORD dst_size, char* src, __out_opt DWORD* src_bytes_read );
DWORD ReadOutInteger( char* src, __out_opt DWORD* src_bytes_read );
void SkipWhiteSpaceAndComments( char*& str );
void __cdecl Log( char* fmt, ... );
