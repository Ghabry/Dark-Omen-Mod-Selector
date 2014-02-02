// double the number of slots availible for sprites entries
// new entries are read-in from "sprite_list.txt"
//
// should play nice with mixed_magic hooks

#include "header.h"

#define FUNC( name, address, ret_type, call_convention, args ) ret_type(call_convention * const name)args = (ret_type(call_convention *)args) address;
#define WRITE_JMP( dst, src ) *((BYTE*)src) = 0xE9; *((DWORD*)(((BYTE*)src) + 1)) = (((DWORD)dst) - ((DWORD)src) - 5); 

namespace sprite_table
{
	struct SPRITE_SLOT
	{
		DWORD ref_count; // things using this sprite ( units, unit leaders, etc. )
		char name[32]; // GRUXBW, ST_ZZNewPlyr3, etc.
		union{
			DWORD type_id; // ?? ( always 0x8 for units ) 
			DWORD banner_bkgrnd_id;
		};
		union{ // note for portaits the index is probably to yet another array...
			struct{	
				WORD loaded_index_sprites; // index in array originally pointed at by dword_526D24
				WORD loaded_index_banners; // index in array originally pointed at by dword_526D2C
			};
			DWORD loaded_index;
		};
	};

	FUNC( sub_004338D0, 0x004338D0, void, __cdecl, ( DWORD, DWORD, DWORD, DWORD, DWORD, DWORD ) );
	FUNC( sub_00435340, 0x00435340, void, __cdecl, ( DWORD dx_something, DWORD, void* loaded_ban_ptr, DWORD, DWORD, DWORD, DWORD, DWORD ) );
	FUNC( LoadSprite, 0x00448500, void, __cdecl, ( DWORD dx_something, DWORD unused, char* szPath, void* loaded_spr_ptr ) );
	FUNC( LoadBanner, 0x00434B80, void, __cdecl, ( DWORD, char* szPath, void* loaded_spr_ptr, DWORD, DWORD, DWORD ) );
	FUNC( GetGameDirStr, 0x0048A010, char*, __cdecl, ( char* szPath ) );

	const BYTE UT = 0; // unknown type
	const BYTE BT = 1; // banner or hud
	const BYTE ST = 2; // sprite
	const BYTE PT = 4; // portrait

	const DWORD nSlots = 512; // must be at least 257
	const DWORD Portrait_First = 96;
	const DWORD Portrait_Last = 178;
	const DWORD HUD = 255;
	const DWORD Expanded_First = 257;

	SPRITE_SLOT SpriteTable[ nSlots ]; // replaces table at 004CEB50
	WORD offset_table[ nSlots ]; // replaces the table at 004EBC88 
	void* Loaded_Sprite_Array[ nSlots ]; // replaces the dynamically allocated array pointed to by dword_526D24 
	void* Loaded_Banner_Array[ nSlots ]; // replaces the dynamically allocated array pointed to by ...

	BYTE SpriteType [ nSlots ] = {
		UT, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST,
		ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST,
		ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST,
		ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST,
		ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST,
		ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST, ST,
		PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT,
		PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT,
		PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT,
		PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT,
		PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, PT, 
		PT, PT, PT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT,
		BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT,
		BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT,
		BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT,
		BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, UT, UT, UT, UT,
		UT
	};

	DWORD __cdecl GetType( DWORD index ){ return SpriteTable[index].type_id; } // replaces sub_4184B0
	DWORD __cdecl AddRef( DWORD index ){ return SpriteTable[index].ref_count++; } // replaces sub_4184D0
	void __cdecl ZeroRef(){ for( int i = 0; i < _countof( SpriteTable ); i++ ) SpriteTable[i].ref_count = 0; } // replaces sub_418510
	DWORD __cdecl GetLoadedIndex( DWORD index ){ return SpriteTable[index].loaded_index; } // replaces sub_418540
	DWORD __cdecl Release( DWORD index ) // // replaces sub_4184F0
	{
		if( SpriteTable[index].ref_count != 0 ) SpriteTable[index].ref_count--;
		return SpriteTable[index].ref_count;
	}

	void __cdecl LoadedSpriteArrayUnloaded( ){ // replaces sub_42B600
		for( int i = 0; i < nSlots; i++ ){
			if( SpriteType[i] != PT ){ // portraits have a hard-coded loaded_index... so skip them
				SpriteTable[i].loaded_index = 0;
			}
		}
	}

	void __cdecl LoadReferencedSprites() { // replaces sub_42B510
		memset( Loaded_Sprite_Array, 0, nSlots * sizeof( void* ) );
		int loaded_count = 0;
		for( int i = 0; i < nSlots; i++ ){
			if( ( SpriteType[i] == ST ) && ( SpriteTable[i].ref_count != 0 ) ){ // load sprite if used
				char szPath[MAX_PATH];
				wsprintfA( szPath, GetGameDirStr( "[SPRITES]\\%s.spr" ), SpriteTable[i].name );				
				LoadSprite( *((DWORD*)0x005014BC), 0, szPath, &(Loaded_Sprite_Array[loaded_count]) );
				if( Loaded_Sprite_Array[loaded_count] != 0 ){
					SpriteTable[i].loaded_index_sprites = (WORD) loaded_count;
					loaded_count++;
				}
			}
		}	
		*((DWORD*)0x00502AF4) = 0x0042B430; // as per original, set function pointer 
	}

	void __cdecl LoadReferencedBanners(){ // replaces sub_42B9E0
		char szPath[MAX_PATH];
		int loaded_count = 0;
		memset( Loaded_Banner_Array, 0, nSlots * sizeof( void* ) );
		sub_004338D0( *((DWORD*)0x005014BC), 0xA0, 0x004D6EC0, 8, 0x00526D20, (*((DWORD*)0x00501AAC) & 0x10) );
		for( int i = 0; i < nSlots; i++ ){
			if( ( SpriteType[i] == BT ) && ( SpriteTable[i].ref_count != 0 ) ){ // load banner if used
				wsprintfA( szPath, "[BANNERS]\\%s.spr", SpriteTable[i].name );
				LoadBanner( *((DWORD*)0x00526D20), szPath, &Loaded_Banner_Array[loaded_count], 1, 1, (*((DWORD*)0x00501AAC) & 0x10) );
				if( Loaded_Banner_Array[loaded_count] != 0 )
				{
					sub_00435340( *((DWORD*)0x005014BC), 4, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0, 0, 4, 0 );
					sub_00435340( *((DWORD*)0x005014BC), 0, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 1, 1, 4, 0 );
					SpriteTable[i].loaded_index_banners = (WORD)loaded_count;
					loaded_count++;
				}
			}
		}

		// load HUD
		wsprintfA( szPath, "[SPRITES]\\%s.spr", SpriteTable[HUD].name );
		*((DWORD*)0x00526D28) = loaded_count;
		LoadBanner( *((DWORD*)0x00526D20), szPath, &Loaded_Banner_Array[loaded_count], 1, 1, (*((DWORD*)0x00501AAC) & 0x10) );
		if( Loaded_Banner_Array[loaded_count] != 0 ){
			sub_00435340( *((DWORD*)0x005014BC), 4, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x00, 0x00, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 1, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x00, 0x01, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 1, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x31, 0x31, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 2, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x04, 0x23, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 6, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x2C, 0x2F, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 1, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x30, 0x30, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 3, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x50, 0x67, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 5, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x68, 0x71, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 7, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x32, 0x40, 4, 0 );
			SpriteTable[HUD].loaded_index_banners = (WORD)loaded_count;
		}
	}

	void Load()
	{
		Log( "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" );
		const char path[] = { "sprite_list.txt" };

		if( 0xFFFFFFFF == GetFileAttributes( path ) ) return;
		char* readbuf = ReadInTextFile( path );
		if( readbuf == NULL ) return;
		
		char* text = readbuf;

		// initialize tables by copying original data in from the game executable
		memcpy( SpriteTable, (void*)0x004CEB50, 257 * sizeof( SPRITE_SLOT ) );
		memcpy( offset_table, (void*)0x004EBC88, 96 * sizeof( WORD ) );
		
		// install hooks
		WRITE_JMP( GetType, 0x004184B0 );
		WRITE_JMP( AddRef, 0x004184D0 );
		WRITE_JMP( Release, 0x004184F0 );
		WRITE_JMP( ZeroRef, 0x00418510 );
		WRITE_JMP( GetLoadedIndex, 0x00418540 );
		WRITE_JMP( LoadReferencedSprites, 0x0042B510 );
		WRITE_JMP( LoadedSpriteArrayUnloaded, 0x0042B600 );
		WRITE_JMP( LoadReferencedBanners, 0x0042B9E0 );
		*((SPRITE_SLOT**)0x004018DF) = &SpriteTable[ Portrait_First ]; // sub_4018A0 ( PortraitsInit )
		*((SPRITE_SLOT**)0x00401910) = &SpriteTable[ Portrait_Last ]; // sub_4018A0 ( PortraitsInit )
		*((DWORD**)0x0041D3A5) = &(SpriteTable[0].loaded_index); // sub_41D360 ( WHMTG_SpeakNoWait )
		*((DWORD**)0x0042459C) = &(SpriteTable[0].loaded_index); // sub_424530 ( ?? )
		*((DWORD**)0x0042BD81) = &(SpriteTable[0].loaded_index); // sub_42BCC0 ( ?? )
		*((DWORD**)0x0042BEDD) = &(SpriteTable[0].loaded_index); // sub_42BCC0 ( ?? )
		*((DWORD**)0x0042E238) = &(SpriteTable[0].loaded_index); // sub_42E1E0 ( ?? )
		*((DWORD**)0x0042B705) = &(SpriteTable[0].loaded_index); // sub_42B6A0 ( ?? )
		*((WORD**) 0x0047FE01) = offset_table; // sub_47FDF0 ( get sprite type info by id...? )
		*((DWORD*)0x00526D24) = (DWORD)&Loaded_Sprite_Array; 	
		*((DWORD*)0x00526D2C) = (DWORD)&Loaded_Banner_Array;


		// parse text file
		int line = 1;
		while( *text != '\0' )
		{	
			DWORD id; // sprite index
			char sprite_name[ sizeof(((SPRITE_SLOT*)0)->name) ];
			DWORD v; // banner_shape or troop_sprite_info_offset
			BYTE type;
			DWORD len; // temp
			DWORD required_len; // temp
			
			SkipWhiteSpaceAndComments( text );

			if( *text == '\r' ) text++;
			if( *text == '\n' ){ text++; line++; continue; }

			// get slot_id
			id = ReadOutInteger( text, &len );
			text += len;
			if( len == 0 ){		
				Log( "sprlst: Error expected sprite_slot_id ( line %d )", line );
				goto the_end;
			}
			if( id >= nSlots ){
				Log( "sprlst: Error sprite_slot_id exceeds max of %d ( line %d )", nSlots - 1, line );
				goto the_end;
			}
			
			// get ST or BT
			SkipWhiteSpaceAndComments( text );
			if( ( text[0] == 'B' || text[0] == 'b' ) && ( text[1] == 'T' || text[1] == 't' ) && ( text[2] == 0x20 || text[2] == 0x09 ) ) type = BT;
			else if ( ( text[0] == 'S' || text[0] == 's' ) && ( text[1] == 'T' || text[1] == 't' ) && ( text[2] == 0x20 || text[2] == 0x09 ) ) type = ST;
			else{
				if( *text == '\r' || *text == '\n' || *text == '\0' ) continue; // if slot has blank entry 
				else{
					Log( "sprlst: Error expected 'BT' or 'ST' for arg2 ( line %d )", line );
					goto the_end;
				}
			}
			if( id < Expanded_First ){
				if( type != SpriteType[id] ){
					Log( "sprlst: Error can not change type of slots with an id less then %d ( line %d )", Expanded_First, line );
					goto the_end;
				}
			}
			text += 3;

			// get sprite_name
			SkipWhiteSpaceAndComments( text );
			required_len = ReadOutWord( sprite_name, sizeof(sprite_name), text, &len );
			text += len;
			if( required_len > sizeof(sprite_name) ){
				Log( "sprlst: Error sprite_name too long ( line %d )", line );
				goto the_end;
			}
			if( required_len == 0 ){
				Log( "sprlst: Error missing sprite_name ( line %d )", line );
				goto the_end;
			}

			// troop_sprite_info_offset or banner_background_id
			SkipWhiteSpaceAndComments( text );
			v = ReadOutInteger( text, &len );
			text += len;
			if( len == 0 ){	
				Log( "sprlst: Error missing arg4 ( line %d )", line );
				goto the_end;
			}
			
			// write this entry to sprite table
			if( type == BT ){			
				SpriteTable[id].banner_bkgrnd_id = v;
			}
			if( type == ST ){	
				if( ( v > 0x0000023E ) || ( ( v % 0x000000E ) != 0 ) ){
					Log( "sprlst: Error invalid value (0x%08X) for arg4 ( line %d )", v, line );
					goto the_end;
				}
				SpriteTable[id].type_id = 8; // troop sprite
				offset_table[id] = (WORD) v;
			}
			strcpy( SpriteTable[id].name, sprite_name );
		} // while

	the_end:
		VirtualFree( readbuf, 0, MEM_RELEASE );
		return;
	} 

	void Unload(){
		memcpy( (void*)0x004184B0, "\x8B\x44\x24\x04\x8D", 5 );
		memcpy( (void*)0x004184D0, "\x8B\x44\x24\x04\x8D", 5 );
		memcpy( (void*)0x004184F0, "\x8B\x44\x24\x04\x8D", 5 );
		memcpy( (void*)0x00418510, "\x56\x57\x66\x33\xF6", 5 ); 
		memcpy( (void*)0x00418540, "\x8B\x44\x24\x04\x8D", 5 );
		memcpy( (void*)0x0042B510, "\x81\xEC\x00\x01\x00", 5 ); 
		memcpy( (void*)0x0042B600, "\xB8\x78\xEB\x4C\x00", 5 ); 
		memcpy( (void*)0x0042B9E0, "\x81\xEC\x00\x01\x00", 5 ); 
		*((DWORD*)0x004018DF) = 0x004CFBD0; // Portrait_First
		*((DWORD*)0x00401910) = 0x004D09E8; // Portrait_Last
		*((DWORD*)0x0041D3A5) = 0x004CEB78; // &(SpriteTable[0].loaded_index)
		*((DWORD*)0x0042459C) = 0x004CEB78; // &(SpriteTable[0].loaded_index)
		*((DWORD*)0x0042BD81) = 0x004CEB78; // &(SpriteTable[0].loaded_index)
		*((DWORD*)0x0042BEDD) = 0x004CEB78; // &(SpriteTable[0].loaded_index)
		*((DWORD*)0x0042E238) = 0x004CEB78; // &(SpriteTable[0].loaded_index)
		*((DWORD*)0x0042B705) = 0x004CEB78; // &(SpriteTable[0].loaded_index)
		*((DWORD*)0x0047FE01) = 0x004EBC88; // offset_table
		*((DWORD*)0x00526D24) = 0; // Loaded_Sprite_Array 	
		*((DWORD*)0x00526D2C) = 0; // Loaded_Banner_Array
	}
}
