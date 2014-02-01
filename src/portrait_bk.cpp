// put a bmp in the Graphics\Pictures folder called x34.bmp and be able to use that as background 34...

#include "header.h"

namespace portrait_bk
{
	struct PORTRAIT_BACKGROUND
	{
		unsigned long index;
		char* szFile; // no file extension
	};

	PORTRAIT_BACKGROUND PortraitBackgroundTable[] = {            
		{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0},
		{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0},
		{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0},
		{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0},
		{ 0x00, NULL  }, { 0x00, NULL  }, { 0x22, "x34" }, { 0x23, "x35" },
		{ 0x24, "x36" }, { 0x25, "x37" }, { 0x26, "x38" }, { 0x27, "x39" },
		{ 0x28, "x40" }, { 0x29, "x41" }, { 0x2A, "x42" }, { 0x2B, "x43" },
		{ 0x2C, "x44" }, { 0x2D, "x45" }, { 0x2E, "x46" }, { 0x2F, "x47" },
		{ 0x30, "x48" }, { 0x31, "x49" }, { 0x32, "x50" }, { 0x33, "x51" },
		{ 0x34, "x52" }, { 0x35, "x53" }, { 0x36, "x54" }, { 0x37, "x55" },
		{ 0x38, "x56" }, { 0x39, "x57" }, { 0x3A, "x58" }, { 0x3B, "x59" }, 
		{ 0x3C, "x60" }, { 0x3D, "x61" }, { 0x3E, "x62" }, { 0x3F, "x63" }
	};

	void Load()
	{
		memcpy( PortraitBackgroundTable, (void*)0x004C1A90, 34 * sizeof( PORTRAIT_BACKGROUND ) );
		*((PORTRAIT_BACKGROUND**)0x004018DA) = PortraitBackgroundTable; // sub_4018A0 ( PortraitsInit )
		*((PORTRAIT_BACKGROUND**)0x0041D2D4) = PortraitBackgroundTable; // sub_41D2A0 ( WHMTG_Speak ) 
	}
	
	void Unload(){
		*((DWORD*)0x004018DA) = 0x004C1A90; // PortraitBackgroundTable
		*((DWORD*)0x0041D2D4) = 0x004C1A90; // PortraitBackgroundTable
	}
}