#include "header.h"

namespace string_tables
{
	char* unit_desc_table[ 0x50 ]
	{
		"not used",
		"grail knights desc here",
		"Bretonnian knights desc is here",
		"Grudgebringer knights desc here",
		0
	};

	void Load()
	{
		memcpy( unit_desc_table, (void*)0x004E2780, 0x50 * sizeof( char* ) );
		*(DWORD*)0x00409E6) = (DWORD)unit_desc_table; 
		*(DWORD*)0x0040BDE0) = (DWORD)unit_desc_table;
	}
	
	void Unload(){
		*((DWORD*)0x00409E6) = 0x004E2780;
		*((DWORD*)0x0040BDE0) = 0x004E2780;
	}
}

