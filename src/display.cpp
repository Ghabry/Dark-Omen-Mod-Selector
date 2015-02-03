/*
restore [HKLM\SOFTWARE\Electronic Arts\Dark Omen\1.0\Options\3DDebug] options
abillity to programmically set [HKLM\SOFTWARE\Electronic Arts\Dark Omen\1.0\Patch\Advanced] options for internal debug purposes

---- notes: -----
HAL seems to have stop working before XP ? 
1. The screen flickers - every other frame is black(ish)?
2. Some cards have an issue where most of the screen is covered with black.
which portions are covered change seemingly at random as the view is moved around the map.

ForceDirectDrawEmulation & RAMP seems to work up thru win7
on Win8 HEL also has screen flicker... only it seems every other frame is the wrong color-depth

the "MMX Device" doesn't seem to work. (unsupported troubleshoot option)
the "MMX Device" hacked to be the "RGB Device" doesn't seem to work either.

The screen flicker can be fix by forcing the game into its (disabled) windowed mode via hex-edit
which is obnoxious cause the game then requires the desktop to be 16bpp

Why does Windowed mode work? ( AFAIK... No DDraw->Flip ?? )

note: movies don't show with ForceDirectDrawEmulation??

the game seems to use:
IDirect3DRM
IDirect3D2
IDirectDraw2
IDirect3DTexture
IDirect3DDevice
and DirectInput

the in-game options:
"cpu" = RAMP (or MMX, if EnabledMMX=1)
"3D" = HAL

don't enable "color cursors" ...  game won't start next time... 
*.cur files can be colored in newish versions of Windows so this isn't a huge problem.
*/
#include "header.h"


namespace display
{
//DATA( Selected,			DWORD, 0x00537D20 ) // { 1=RAMP ( or MMX if EnableMMX=1 ), 2=MMX, 4=Hardware }

	// Patches //
	DATA( patchpermedia1,			DWORD, 0x00502A88 );
	DATA( patchpermedia2,			DWORD, 0x00502A84 );
	DATA( patchrage2,				DWORD, 0x00502AA0 );
//	DATA( nopassthru,				DWORD, 0x004BF0A0 ); // ?? ( just use tshoot.exe to enable this instead )
	DATA( EnableMMX,				DWORD, 0x00502A80 ); // use "MMX Device" instead of RAMP when software (aka. cpu) is "Selected"                 
	DATA( DontLockPrimary,			DWORD, 0x00502A8C );                
	DATA( NoRGB16,					DWORD, 0x00502A90 );                        
	DATA( No8Bit,					DWORD, 0x00502A94 );                         
	DATA( NoRGBA4444,				DWORD, 0x00502A98 );                     
	DATA( No4Bit,					DWORD, 0x00502A9C );                        
	DATA( NoUploadsDuringScene,		DWORD, 0x00502AA4 );          
	DATA( EnableS3,					DWORD, 0x00502AA8 );                   
	DATA( AlignToTile,				DWORD, 0x00502AAC );                 
	DATA( No3DfxFixes,				DWORD, 0x00502AB4 );                      
	DATA( novideoplayhw,			DWORD, 0x00502ABC ); // hard coded to 1 ( VA: 0x0042ECB5 ) 
	DATA( Force3DSupport,			DWORD, 0x00502AC0 );              
	DATA( NoRGBA1555,				DWORD, 0x00502AC8 );                  
	DATA( SingleScene,				DWORD, 0x00502ACC );                 
	DATA( PatchColourKey,			DWORD, 0x00502AD0 );              
	DATA( patchverite1000,			DWORD, 0x00502ADC );             
	DATA( NoPVRFixes,				DWORD, 0x00502AE0 ); 
	
	// 3DDebug //
	DATA( DebugMessages,			DWORD, 0x00502F48 ); // game seems to ignore, so we use it to 'OutputDegubString' everything that goes to sprintf
	DATA( FullScreen,				DWORD, 0x004BF0A8 ); // { 1=FullScreen, 0=Windowed(unsupported) }
	DATA( MapGrab,					DWORD, 0x004BF0F8 ); // 1 = no overlays, start battle viewing battlemap, multiplayer style battlemap, others? 
	DATA( Prelighting,				DWORD, 0x004BF0DC );
	DATA( TextureFilter,			DWORD, 0x004BF0A4 );
	DATA( GouraudShading,			DWORD, 0x004BF0AC ); // 0 = shadows aren't blended just shown as triangles 
	DATA( RenderArea,				DWORD, 0x004BF104 ); // { 0=640x480, 1=600x450, 2=576x432, 3=512x384, 4=448x336 }
	DATA( DisplayOverlays,			DWORD, 0x004BF0F0 ); // 0 = no clutter		
	DATA( EnableSound,				DWORD, 0x004D1E08 );
	DATA( EnableMusic,				DWORD, 0x004D1E0C ); 
	DATA( LightEdit,				DWORD, 0x004BF0F4 ); // crashes
	DATA( RequestBattle,			DWORD, 0x004BF100 ); // ??? DirectPlay related?
	DATA( PerspectiveCorrection,	DWORD, 0x004BF0B0 ); //	gets rid of fisheye when panning view over hills, etc.

	// these seem to have no effect?
	DATA( RenderParticles,			DWORD, 0x004BF0E0 );
	DATA( RenderBattlefield,		DWORD, 0x004BF0E4 );
	DATA( RenderSprites,			DWORD, 0x004BF0E8 );
	DATA( RenderPortrait,			DWORD, 0x004BF0EC );

	// new opt, overrides part of "pixel resolution" option
	// because that setting lumps too much stuff together ( sprites, portraits, textures )
	// and some like the ltextures better when using HEL
	DATA( LTEXTURE,					DWORD, 0x004BF0FC ); // { 0=ltextures, 1=textures }           


	void GetOptionFromReg_Helper( HKEY hKey, char* name, DWORD& va ){
		DWORD dwBufSize = 63;
		char szBuf[64];
		DWORD dwType;

		if(! RegQueryValueEx( hKey, name, NULL, &dwType, (LPBYTE) szBuf, &dwBufSize ) )
		{
			if( dwType != REG_SZ ) return;
			szBuf[63] = '\0';

			// atoi
			unsigned int acc = 0;
			char* p = szBuf;
			char c = *p++;
			unsigned int d;
			if( ( c < '0' ) || ( c > '9' ) ) return; // not a number...
			for(;;){
				if( ( c >= '0' ) && ( c <= '9' ) ) d = (DWORD)((unsigned char)(c - '0'));
				else break; // bad digit
				if( acc > 0x19999999 ) return; // range error
				acc = ( acc * 10 ) + d;
				if( acc < d ) return; // range error
				c = *p++;
			}
			if( c != '\0' ) return; // bad character found in "number" string

			// write value to game memory
			va = acc;
		}
	}


	#ifndef _FILE_DEFINED
	struct _iobuf {
			char *_ptr;
			int   _cnt;
			char *_base;
			int   _flag;
			int   _file;
			int   _charbuf;
			int   _bufsiz;
			char *_tmpfname;
			};
	typedef struct _iobuf FILE;
	#define _FILE_DEFINED
	#endif

	// Debug logging - if enabled print all strings that get sent to sprintf
	int __cdecl sprintf_hookproc( char *buf, char *fmt, ... )
	{
		FUNC( __output, 0x004B1610, int, __cdecl, ( FILE*, char*, va_list ) );
		FUNC( __flsbuf, 0x004B14C0, int, __cdecl, ( int, FILE* ) );

		va_list args;
		int r;
		FILE f;

		f._cnt = 0x7FFFFFFF;
		f._base = buf;
		f._ptr = buf;
		f._flag = 0x42;

		va_start( args, fmt );
		r = __output( &f, fmt, args );  
		va_end( args );

		if( --(f._cnt) > 0 ){
			*f._ptr++ = '\0';

			// my stuff
			if( DebugMessages ) OutputDebugString( buf );
			//
		}
		else __flsbuf( 0, &f );

		return r;	
	}

	// note: the patch_xxx options may also have specialized fixes elsewhere 
	void DisplayPatchesCommon(){
		// original sub_440630
		if( patchrage2 ){
			No4Bit = 1;
			No8Bit = 1;
			novideoplayhw = 1;
		}
		if( patchpermedia1 ){
			No4Bit = 1;
		}
		if( patchverite1000 ){
			No8Bit = 1;
		}
		if( patchpermedia2 ){
			No4Bit = 1;
		}

		// set any "Patches" you want here...
		/*
		EnableMMX = 1;
		DontLockPrimary = 1;
		No8Bit = 1;		                    
		NoRGBA4444 = 1;	                
		No4Bit		= 1;
		//NoRGBA1555 = 1;	
		*/
	}

	void Config_3DDebug_Startup(){
		HKEY hKey;
		if(! RegOpenKeyEx( HKEY_LOCAL_MACHINE, 
			"SOFTWARE\\Electronic Arts\\Dark Omen\\1.0\\Options\\3DDebug",
			0, STANDARD_RIGHTS_READ | KEY_QUERY_VALUE, &hKey ) )
		{
			GetOptionFromReg_Helper( hKey, "FullScreen",	FullScreen ); 
			GetOptionFromReg_Helper( hKey, "MapGrab",		MapGrab ); 
			GetOptionFromReg_Helper( hKey, "DebugMessages",	DebugMessages );
			GetOptionFromReg_Helper( hKey, "Prelighting",	Prelighting );
			GetOptionFromReg_Helper( hKey, "TextureFilter",	TextureFilter );
			RegCloseKey(hKey);
		}
	}

	void Config_3DDebug_hookproc(){
		FUNC( Config_3DDebug, 0x00413F50, void, __cdecl, ( ) );
		Config_3DDebug(); // call original function
		
		HKEY hKey;
		if(! RegOpenKeyEx( HKEY_LOCAL_MACHINE, 
			"SOFTWARE\\Electronic Arts\\Dark Omen\\1.0\\Options\\3DDebug",
			0, KEY_READ, &hKey ) )
		{
			GetOptionFromReg_Helper( hKey, "GouraudShading",	GouraudShading ); 
			GetOptionFromReg_Helper( hKey, "RenderArea",		RenderArea ); 
			GetOptionFromReg_Helper( hKey, "DisplayOverlays",	DisplayOverlays );
			GetOptionFromReg_Helper( hKey, "LTEXTURE",			LTEXTURE );             
			GetOptionFromReg_Helper( hKey, "RequestBattle",		RequestBattle );  
			GetOptionFromReg_Helper( hKey, "EnableSound",		EnableSound );
			GetOptionFromReg_Helper( hKey, "EnableMusic",		EnableMusic ); 
			GetOptionFromReg_Helper( hKey, "RenderParticles",	RenderParticles );
			GetOptionFromReg_Helper( hKey, "RenderBattlefield",	RenderBattlefield );
			GetOptionFromReg_Helper( hKey, "RenderSprites",		RenderSprites );
			GetOptionFromReg_Helper( hKey, "RenderPortrait",	RenderPortrait );
			GetOptionFromReg_Helper( hKey, "LightEdit",			LightEdit );

			// it would be confusing/pointless to override the in-game PerspectiveCorrection setting
			//GetOptionFromReg_Helper( hKey, "PerspectiveCorrection",	PerspectiveCorrection );

			RegCloseKey(hKey);
		}
	}

	void Load(){
		Config_3DDebug_Startup();
		HOOK_CALL( &Config_3DDebug_hookproc, 0x00422A90 );
		HOOK_CALL( &DisplayPatchesCommon, 0x0042EC86 );
		
		WRITE_JMP( sprintf_hookproc, 0x004AE940 );

	}
	void Unload(){ 
		// todo:
	}
}
