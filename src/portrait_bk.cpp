
namespace portrait_bk
{
	struct PORTRAIT_BACKGROUND
	{
		unsigned long index;
		char* szFile; // no file extension
	};

	PORTRAIT_BACKGROUND PortraitBackgroundTable[] = {            
		{ 0x00, "MB_Emp" },
		{ 0x01, "MB_Empn" },
		{ 0x02, "MB_ImpCt" },
		{ 0x03, "MB_Hel" },
		{ 0x04, "MB_Hel" },
		{ 0x05, "MB_Kis" },
		{ 0x06, "MB_KisCt" },
		{ 0x07, "MB_Ice" },
		{ 0x08, "MB_For" },
		{ 0x09, "MB_Forn" },
		{ 0x0A, "MB_Lor" },
		{ 0x0B, "MB_Lorn" },
		{ 0x0C, "MB_Mnt" },
		{ 0x0D, "MB_Mntn" },
		{ 0x0E, "MB_Moun" },
		{ 0x0F, "MB_ParCt" },
		{ 0x10, "MB_Desn" },
		{ 0x11, "MB_Twn" },
		{ 0x12, "MB_Twnn" },
		{ 0x13, "MB_Syln" },
		{ 0x14, "BB_Desn" },
		{ 0x15, "BB_Emp" },
		{ 0x16, "BB_Empn" },
		{ 0x17, "BB_Hel" },
		{ 0x18, "BB_Ice" },
		{ 0x19, "BB_Kis" },
		{ 0x1A, "BB_Lor" },
		{ 0x1B, "BB_Lorn" },
		{ 0x1C, "BB_Mnt" },
		{ 0x1D, "BB_Mntn" },
		{ 0x1E, "BB_Moun" },
		{ 0x1F, "BB_Syln" },
		{ 0x20, "BB_Twnn" },
		{ 0x21, "BB_Cav" }
	};

	void InstallHooks()
	{
		*((PORTRAIT_BACKGROUND**)0x004018DA) = PortraitBackgroundTable; // sub_4018A0 ( PortraitsInit )
		*((PORTRAIT_BACKGROUND**)0x0041D2D4) = PortraitBackgroundTable; // sub_41D2A0 ( WHMTG_Speak ) 
	}
}