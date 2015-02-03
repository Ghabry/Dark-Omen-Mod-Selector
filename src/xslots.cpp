// allow new units to be added without overwriting existing ones by creating
// bigger tables for sprites, banners, portraits, army book, names, etc.
//
// hooks should play nice with mixed_magic hooks
#include "header.h"

namespace xslots
{
	struct SPRITE_SLOT
	{
		DWORD ref_count; // things using this sprite ( units, unit leaders, etc. )
		char name[32]; // GRUXBW, ST_ZZNewPlyr3, etc.
		union{
			DWORD type_id; // ?? ( always 0x8 for units ) 
			DWORD banner_bkgrnd_id;
		};
		union{ // note for portaits the loaded_index points to a HEAD struct in the file heads.db
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
	FUNC( Portraits_MakeList, 0x004018A0, void, __cdecl, ( DWORD* ) );
	FUNC( memset, 0x004B07C0, void*, __cdecl, ( void* buffer, int ch, size_t count ) );
	FUNC( memcpy, 0x004AFCB0, void*, __cdecl, ( void *to, const void *from, size_t count ) );



	const DWORD SPRITE_FIRST =		1; // ST
	const DWORD SPRITE_LAST =		95; // ST
	const DWORD PORTRAIT_FIRST =	96; // PT
	const DWORD PORTRAIT_LAST =		178; // PT
	const DWORD BANNER_FIRST =		179; // BT
	const DWORD BANNER_LAST =		251; // BT
	const DWORD HUD =				255;
	//const DWORD Expanded_First =	257;
	const DWORD X_SPRITE_FIRST =	260; // ST
	const DWORD X_SPRITE_LAST =		459; // ST
	const DWORD X_BANNER_FIRST =	460; // BT
	const DWORD X_BANNER_LAST =		559; // BT
	const DWORD X_PORTRAIT_FIRST =	560; // PT
	const DWORD X_PORTRAIT_LAST =	659; // PT
	SPRITE_SLOT SpriteTable[ 660 ]; // replaces table at 004CEB50
	WORD offset_table[ 460 ]; // replaces the table at 004EBC88 
	void* Loaded_Sprite_Array[ 660 ]; // replaces the dynamically allocated array pointed to by dword_526D24 
	void* Loaded_Banner_Array[ 660 ]; // replaces the dynamically allocated array pointed to by ...
	WORD Loaded_Portrait_Array[ 128 ]; // replaces the dynamically allocated array pointed to by dword_00533B54
	void* heads_db;

	const DWORD X_NAME_FIRST = 80;
	const DWORD X_NAME_LAST = 179;
	char* unit_name[ 180 ]; // replaces table at 0x004E2640
	char x_names[100][64];

	const DWORD X_BOOK_FIRST = 80;
	const DWORD X_BOOK_LAST	= 179;
	char* troop_book_unit_pic[ 180 ]; // replaces table at 0x004C0940
	char* troop_book_leader_pic[ 180 ]; // replaces table at 0x004C0A80
	char* troop_book_unit_desc[ 180 ]; // replaces table at 0x004E2780
	char  troop_book_banner_index[ 180 ]; // replaces table at 0x004C0BC0

	DWORD __cdecl GetType( DWORD index ){ return SpriteTable[index].type_id; } // replaces sub_4184B0
	DWORD __cdecl AddRef( DWORD index ){ return SpriteTable[index].ref_count++; } // replaces sub_4184D0
	void __cdecl ZeroRef(){ for( int i = 0; i < _countof( SpriteTable ); i++ ) SpriteTable[i].ref_count = 0; } // replaces sub_418510
	DWORD __cdecl GetLoadedIndex( DWORD index ){ return SpriteTable[index].loaded_index; } // replaces sub_418540
	DWORD __cdecl Release( DWORD index ) // // replaces sub_4184F0
	{
		if( SpriteTable[index].ref_count != 0 ) SpriteTable[index].ref_count--;
		return SpriteTable[index].ref_count;
	}

	void __cdecl ReferencedPortraits( DWORD* arg0 ){ // replaces sub_4018A0
		if( *arg0 == 0 ){
			Portraits_MakeList( arg0 );	// call original
			int count = *((DWORD*)0x005014FC);
			for( int i = X_PORTRAIT_FIRST; i <= X_PORTRAIT_LAST; i++ ){
				if( SpriteTable[i].ref_count != 0 ){ // if used then add to table
					*((DWORD*)(0x00501500 + count++ * 8)) = SpriteTable[i].loaded_index;
				}
			}
			*((DWORD*)0x005014FC) = count;
		}
	}

	void PortraitInit(){ // replaces sub_41EB40
		// init new portraits in sprite table
		// note: game crashes for id > 0x7F
		int id = 0x3F; // entry index in heads.db
		for( int i = X_PORTRAIT_FIRST; i <= X_PORTRAIT_LAST; i++ ){
			SpriteTable[ i ].loaded_index = id++;
		}

		memset( Loaded_Portrait_Array, 0xFF, sizeof(Loaded_Portrait_Array) );
		
		char* fname = GetGameDirStr( "[PORTRAIT]\\script\\heads.db" );
		heads_db = ReadInFile( fname );

		*((DWORD*)0x00533B54) = (DWORD) &Loaded_Portrait_Array;
		*((BYTE*)0x004D5BD4) = 1; // g_IsPortraitInit
		*((DWORD*)0x00533B28) = ((DWORD)heads_db) + 1;
		*((DWORD*)0x004D5BC8) = 0; // timer
	}

	void PortraitShutdown(){ // replaces sub_41EC00
		*((BYTE*)0x004D5BD4) = 0; // g_IsPortraitInit
		*((DWORD*)0x00533B54) = 0; // &Loaded_Portrait_Array
		if( heads_db != NULL ){
			VirtualFree( heads_db, 0, MEM_RELEASE );
			heads_db = NULL;
		}
	}


	void __cdecl LoadedSpriteArrayUnloaded( ){ // replaces sub_42B600
		for( int i = 0; i < _countof(SpriteTable); i++ ){
			// portraits have a hard-coded loaded_index... so skip them
			if( i == PORTRAIT_FIRST ){ i = PORTRAIT_LAST; continue; }
			if( i == X_PORTRAIT_FIRST ){ i = X_PORTRAIT_LAST; continue; }
			SpriteTable[i].loaded_index = 0;
		}
	}

	void __cdecl LoadReferencedSprites() { // replaces sub_42B510
		memset( Loaded_Sprite_Array, 0, sizeof( Loaded_Sprite_Array ) );
		int loaded_count = 0;
		
		for( int i = SPRITE_FIRST; i <= SPRITE_LAST; i++ ){
			if( SpriteTable[i].ref_count != 0 ){ // load sprite if used
				char szPath[MAX_PATH];
				wsprintfA( szPath, GetGameDirStr( "[SPRITES]\\%s.spr" ), SpriteTable[i].name );				
				LoadSprite( *((DWORD*)0x005014BC), 0, szPath, &(Loaded_Sprite_Array[loaded_count]) );
				if( Loaded_Sprite_Array[loaded_count] != 0 ){
					SpriteTable[i].loaded_index_sprites = (WORD) loaded_count;
					loaded_count++;
				}
			}
		}
		for( int i = X_SPRITE_FIRST; i <= X_SPRITE_LAST; i++ ){
			if( SpriteTable[i].ref_count != 0 ){ // load sprite if used
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
		memset( Loaded_Banner_Array, 0, sizeof( Loaded_Banner_Array ) );
		sub_004338D0( *((DWORD*)0x005014BC), 0xA0, 0x004D6EC0, 8, 0x00526D20, (*((DWORD*)0x00501AAC) & 0x10) );
		int loaded_count = 0;
		for( int i = BANNER_FIRST; i <= BANNER_LAST; i++ ){
			if( SpriteTable[i].ref_count != 0 ){ // load banner if used
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
		for( int i = X_BANNER_FIRST; i <= X_BANNER_LAST; i++ ){
			if( SpriteTable[i].ref_count != 0 ){ // load banner if used
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
		
		// parse text file
		const char path[] = { "xslots.txt" };
		if( 0xFFFFFFFF == GetFileAttributes( path ) ) return;
		char* readbuf = ReadInFile( path );
		if( readbuf == NULL ) return;		
		char* text = readbuf;
		int line = 1;
		while( *text != '\0' )
		{	
			// temp vars
			DWORD slot_id;
			char buf[ 12 ]; 
			DWORD len; 
			DWORD required_len;
			
			// scan till some content is found
			SkipWhiteSpaceAndComments( text );
			if( *text == '\r' ) text++;
			if( *text == '\n' ){ text++; line++; continue; }

			// 
			required_len = ReadOutWord( buf, sizeof(buf), text, &len );
			if( ( required_len > sizeof(buf) ) || ( required_len <= 1 ) ){
				Log( "xslot: Error ( line %d )", line );
				goto the_end;
			}
			text += len;
			SkipWhiteSpaceAndComments( text );
			//
			slot_id = ReadOutInteger( text, &len );
			if( len == 0 ){		
				Log( "xslot: Error expected slot_id ( line %d )", line );
				goto the_end;
			}
			text += len;
			SkipWhiteSpaceAndComments( text );
			//
			if( 0 == strcmp( buf, "SPRITE" ) ){
				if( slot_id > ( X_SPRITE_LAST - X_SPRITE_FIRST ) ){
					Log( "xslot: Error %s exceeds max of %d ( line %d )", "slot_id", ( X_SPRITE_LAST - X_SPRITE_FIRST ), line );
					goto the_end;
				}
				SPRITE_SLOT* p = &SpriteTable[ slot_id + X_SPRITE_FIRST ];
				//
				required_len = ReadOutWord( p->name, sizeof(p->name), text, &len );
				if( required_len > sizeof(p->name) ){
					Log( "xslot: Error %s exceeds max of %d ( line %d )", "sprite_file_name", sizeof(p->name), line );
					goto the_end;
				}
				if( len == 0 ){	continue; }
				text += len;
				SkipWhiteSpaceAndComments( text );
				//
				DWORD off = ReadOutInteger( text, &len );
				text += len;
				if( len == 0 ){	
					Log( "xslot: Error missing sprite_type_offset ( line %d )", line );
					goto the_end;
				}
				if( ( off > 0x0000023E ) || ( ( off % 0x000000E ) != 0 ) ){
					Log( "xslot: Error invalid value (0x%08X) for sprite_type_offset ( line %d )", off, line );
					goto the_end;
				}
				p->type_id = 8; // troop sprite
				offset_table[ slot_id + X_SPRITE_FIRST ] = (WORD)off;
			}
			else {
				if( 0 == strcmp( buf, "NAME" ) ){
					if( slot_id > ( X_NAME_LAST - X_NAME_FIRST ) ){
						Log( "xslot: Error %s exceeds max of %d ( line %d )", "slot_id", ( X_NAME_LAST - X_NAME_FIRST ), line );
						goto the_end;
					}
					required_len = ReadOutWord( &x_names[slot_id][0], 64, text, &len );
					if( len == 0 ){	continue; }
					text += len;
					if( required_len > 64 ){
						Log( "xslot: Error %s exceeds max of %d ( line %d )", "name", 64, line );
						goto the_end;
					}
					unit_name[ slot_id + X_NAME_FIRST ] = &x_names[slot_id][0];
				}
				else {
					if( 0 == strcmp( buf, "BANNER" ) ){
						if( slot_id > ( X_BANNER_LAST - X_BANNER_FIRST ) ){
							Log( "xslot: Error %s exceeds max of %d ( line %d )", "slot_id", ( X_BANNER_LAST - X_BANNER_FIRST ), line );
							goto the_end;
						}
						SPRITE_SLOT* p = &SpriteTable[ slot_id + X_BANNER_FIRST ];
						//
						required_len = ReadOutWord( p->name, sizeof(p->name), text, &len );
						if( required_len > sizeof(p->name) ){
							Log( "xslot: Error %s exceeds max of %d ( line %d )", "sprite_file_name", sizeof(p->name), line );
							goto the_end;
						}
						if( len == 0 ){	continue; }
						text += len;
						SkipWhiteSpaceAndComments( text );
						//
						DWORD shape = ReadOutInteger( text, &len );
						if( len == 0 ){	
							Log( "xslot: Error missing banner_shape_id ( line %d )", line );
							goto the_end;
						}
						text += len;
						p->banner_bkgrnd_id = shape;
					}
					else {
						if( 0 == strcmp( buf, "BOOK" ) ){
							if( slot_id > ( X_BOOK_LAST - X_BOOK_FIRST ) ){
								Log( "xslot: Error %s exceeds max of %d ( line %d )", "slot_id", ( X_BOOK_LAST - X_BOOK_FIRST ), line );
								goto the_end;
							}
							//
							troop_book_banner_index[ slot_id + X_BOOK_FIRST ] = (char) ReadOutInteger( text, &len );
							if( len == 0 ){	continue; }
							text += len;
							SkipWhiteSpaceAndComments( text );
							//
							required_len = ReadOutWord( 0, 0, text, &len );
							if( len == 0 ){
								Log( "xslot: Error missing leader_pic ( line %d )", line );
							}
							troop_book_leader_pic[ slot_id + X_BOOK_FIRST ] = (char*) HeapAlloc( GetProcessHeap(), 0, required_len );
							if( troop_book_leader_pic[ slot_id + X_BOOK_FIRST ] == NULL ){
								Log( "xslot: Alloc Failed ( line %d )", line );
								goto the_end;
							}
							ReadOutWord( troop_book_leader_pic[ slot_id + X_BOOK_FIRST ], required_len, text, &len );
							text += len;
							SkipWhiteSpaceAndComments( text );
							//
							required_len = ReadOutWord( 0, 0, text, &len );
							if( len == 0 ){
								Log( "xslot: Error missing troop_pic ( line %d )", line );
								goto the_end;
							}
							troop_book_unit_pic[ slot_id + X_BOOK_FIRST ] = (char*) HeapAlloc( GetProcessHeap(), 0, required_len );
							if( troop_book_unit_pic[ slot_id + X_BOOK_FIRST ] == NULL ){
								Log( "xslot: Alloc Failed ( line %d )", line );
								goto the_end;
							}
							ReadOutWord( troop_book_unit_pic[ slot_id + X_BOOK_FIRST ], required_len, text, &len );
							text += len;
							SkipWhiteSpaceAndComments( text );
							//
							required_len = ReadOutWord( 0, 0, text, &len );
							if( len == 0 ){
								Log( "xslot: Error missing troop_desc ( line %d )", line );
								goto the_end;
							}
							troop_book_unit_desc[ slot_id + X_BOOK_FIRST ] = (char*) HeapAlloc( GetProcessHeap(), 0, required_len );
							if( troop_book_unit_desc[ slot_id + X_BOOK_FIRST ] == NULL ){
								Log( "xslot: Alloc Failed ( line %d )", line );
								goto the_end;
							}
							ReadOutWord( troop_book_unit_desc[ slot_id + X_BOOK_FIRST ], required_len, text, &len );
							text += len;
						}
						else{
							if( 0 == strcmp( buf, "PORTRAIT" ) ){
								if( slot_id > ( X_PORTRAIT_LAST - X_PORTRAIT_FIRST ) ){
									Log( "xslot: Error %s exceeds max of %d ( line %d )", "slot_id", ( X_PORTRAIT_LAST - X_PORTRAIT_FIRST ), line );
									goto the_end;
								}
								DWORD m3d_id = ReadOutInteger( text, &len );
								if( len == 0 ){		
									Log( "xslot: Error expected m3d_id ( line %d )", line );
									goto the_end;
								}
								text += len;
								
								SPRITE_SLOT* p = &SpriteTable[ slot_id + X_PORTRAIT_FIRST ];
								p->loaded_index = m3d_id;
							}
							else {
								Log( "xslot: Error unrecognized command \"%s\" ( line %d )", buf, line );
								goto the_end;
							}
						}
					}
				}
			}
		} // while
		

		// copy original data in from the game executable
		memcpy( SpriteTable, (void*)0x004CEB50, 257 * sizeof( SPRITE_SLOT ) );
		memcpy( offset_table, (void*)0x004EBC88, 96 * sizeof( WORD ) );
		memcpy( unit_name, (void*)0x004E2640, 0x50 * sizeof( char* ) );
		memcpy( troop_book_unit_pic, (void*)0x004C0940, 0x50 * sizeof( char* ) );
		memcpy( troop_book_leader_pic, (void*)0x004C0A80, 0x50 * sizeof( char* ) );
		memcpy( troop_book_unit_desc, (void*)0x004E2780, 0x50 * sizeof( char* ) );
		memcpy( troop_book_banner_index,  (void*)0x004C0BC0, 0x50 * sizeof( char ) );

		// install hooks
		HOOK_CALL( &ReferencedPortraits, 0x00401C8A );
		HOOK_CALL( &ReferencedPortraits, 0x00401E21 );
		HOOK_CALL( PortraitShutdown, 0x0042A3C6 );
		HOOK_CALL( PortraitInit, 0x00428A1F );
		*((BYTE*)0x0041EE08) = 0x7F; // override max head_db entries (0x3F)
		*((BYTE*)0x0041EC9B) = 0x7F; // override max head_db entries (0x3F)
		WRITE_JMP( GetType, 0x004184B0 );
		WRITE_JMP( AddRef, 0x004184D0 );
		WRITE_JMP( Release, 0x004184F0 );
		WRITE_JMP( ZeroRef, 0x00418510 );
		WRITE_JMP( GetLoadedIndex, 0x00418540 );
		WRITE_JMP( LoadReferencedSprites, 0x0042B510 );
		WRITE_JMP( LoadedSpriteArrayUnloaded, 0x0042B600 );
		WRITE_JMP( LoadReferencedBanners, 0x0042B9E0 );
		*((SPRITE_SLOT**)0x004018DF) = &SpriteTable[ PORTRAIT_FIRST ]; // sub_4018A0 ( PortraitsInit )
		*((SPRITE_SLOT**)0x00401910) = &SpriteTable[ PORTRAIT_LAST ]; // sub_4018A0 ( PortraitsInit )
		*((DWORD**)0x0041D3A5) = &(SpriteTable[0].loaded_index); // sub_41D360 ( WHMTG_SpeakNoWait )
		*((DWORD**)0x0042459C) = &(SpriteTable[0].loaded_index); // sub_424530 ( ?? )
		*((DWORD**)0x0042BD81) = &(SpriteTable[0].loaded_index); // sub_42BCC0 ( ?? )
		*((DWORD**)0x0042BEDD) = &(SpriteTable[0].loaded_index); // sub_42BCC0 ( ?? )
		*((DWORD**)0x0042E238) = &(SpriteTable[0].loaded_index); // sub_42E1E0 ( ?? )
		*((DWORD**)0x0042B705) = &(SpriteTable[0].loaded_index); // sub_42B6A0 ( ?? )
		*((WORD**) 0x0047FE01) = offset_table; // sub_47FDF0 ( get sprite type info by id...? )
		*((DWORD*)0x00526D24) = (DWORD)&Loaded_Sprite_Array; 	
		*((DWORD*)0x00526D2C) = (DWORD)&Loaded_Banner_Array;
		*((DWORD*)0x00409F11) = (DWORD)troop_book_unit_pic;
		*((DWORD*)0x00409F52) = (DWORD)troop_book_unit_pic; 
		*((DWORD*)0x0040C0CC) = (DWORD)troop_book_unit_pic; 
		*((DWORD*)0x0040C108) = (DWORD)troop_book_unit_pic; 
		*((DWORD*)0x00409DE3) = (DWORD)troop_book_leader_pic;
		*((DWORD*)0x0040BD24) = (DWORD)troop_book_leader_pic;
		*((DWORD*)0x00409EC2) = (DWORD)unit_name;
		*((DWORD*)0x0040B876) = (DWORD)unit_name;
		*((DWORD*)0x0040BE4A) = (DWORD)unit_name;
		*((DWORD*)0x0040C20F) = (DWORD)unit_name;
		*((DWORD*)0x0040C461) = (DWORD)unit_name;
		*((DWORD*)0x0040D213) = (DWORD)unit_name;
		*((DWORD*)0x0040D9C3) = (DWORD)unit_name;
		*((DWORD*)0x0041985C) = (DWORD)unit_name;
		*((DWORD*)0x0041A5E4) = (DWORD)unit_name;
		*((DWORD*)0x0041B1B0) = (DWORD)unit_name;
		*((DWORD*)0x0041B4CA) = (DWORD)unit_name;
		*((DWORD*)0x0042671A) = (DWORD)unit_name;
		*((DWORD*)0x004286E1) = (DWORD)unit_name;
		*((DWORD*)0x00409E63) = (DWORD)troop_book_unit_desc; 
		*((DWORD*)0x0040BDE0) = (DWORD)troop_book_unit_desc;
		*((DWORD*)0x004099B5) = (DWORD)troop_book_banner_index;
		*((DWORD*)0x00409DAD) = (DWORD)troop_book_banner_index;
		*((DWORD*)0x0040B83D) = (DWORD)troop_book_banner_index;
		*((DWORD*)0x0040BCE0) = (DWORD)troop_book_banner_index;
		*((DWORD*)0x0040C1D5) = (DWORD)troop_book_banner_index;
		*((DWORD*)0x0040C413) = (DWORD)troop_book_banner_index;
		*((DWORD*)0x0040D97C) = (DWORD)troop_book_banner_index;
		*((DWORD*)0x0040E1E9) = (DWORD)troop_book_banner_index;
		*((DWORD*)0x004192A4) = (DWORD)troop_book_banner_index;
		*((DWORD*)0x0041981E) = (DWORD)troop_book_banner_index;
		*((DWORD*)0x0041A39E) = (DWORD)troop_book_banner_index;
		*((DWORD*)0x0041A5A6) = (DWORD)troop_book_banner_index;
		*((DWORD*)0x0041B172) = (DWORD)troop_book_banner_index;
		*((DWORD*)0x0041B48C) = (DWORD)troop_book_banner_index;
		*((DWORD*)0x00425B26) = (DWORD)troop_book_banner_index;
		*((DWORD*)0x00426DEB) = (DWORD)troop_book_banner_index;

	the_end:
		VirtualFree( readbuf, 0, MEM_RELEASE );
		return;
	} 

	void Unload(){
		
		HOOK_CALL( 0x004018A0, 0x00401C8A ); // ReferencedPortraits
		HOOK_CALL( 0x004018A0, 0x00401E21 ); // ReferencedPortraits
		HOOK_CALL( 0x0041EC00, 0x0042A3C6 ); // PortraitShutdown
		HOOK_CALL( 0x0041EB40, 0x00428A1F ); // PortraitInit
		*((BYTE*)0x0041EE08) = 0x3F; // max head_db entries
		*((BYTE*)0x0041EC9B) = 0x3F; // max head_db entries

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
		*((DWORD*)0x00409F11) = 0x004C0940; // troop_book_unit_pic
		*((DWORD*)0x00409F52) = 0x004C0940; // troop_book_unit_pic
		*((DWORD*)0x0040C0CC) = 0x004C0940; // troop_book_unit_pic
		*((DWORD*)0x0040C108) = 0x004C0940; // troop_book_unit_pic
		*((DWORD*)0x00409DE3) = 0x004C0A80; // troop_book_leader_pic
		*((DWORD*)0x0040BD24) = 0x004C0A80; // troop_book_leader_pic
		*((DWORD*)0x00409EC2) = 0x004E2640; // unit name
		*((DWORD*)0x0040B876) = 0x004E2640; // unit name
		*((DWORD*)0x0040BE4A) = 0x004E2640; // unit name
		*((DWORD*)0x0040C20F) = 0x004E2640; // unit name
		*((DWORD*)0x0040C461) = 0x004E2640; // unit name
		*((DWORD*)0x0040D213) = 0x004E2640; // unit name
		*((DWORD*)0x0040D9C3) = 0x004E2640; // unit name
		*((DWORD*)0x0041985C) = 0x004E2640; // unit name
		*((DWORD*)0x0041A5E4) = 0x004E2640; // unit name
		*((DWORD*)0x0041B1B0) = 0x004E2640; // unit name
		*((DWORD*)0x0041B4CA) = 0x004E2640; // unit name
		*((DWORD*)0x0042671A) = 0x004E2640; // unit name
		*((DWORD*)0x004286E1) = 0x004E2640; // unit name
		*((DWORD*)0x00409E63) = 0x004E2780; // unit_desc
		*((DWORD*)0x0040BDE0) = 0x004E2780; // unit_desc
		*((DWORD*)0x004099B5) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x00409DAD) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0040B83D) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0040BCE0) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0040C1D5) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0040C413) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0040D97C) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0040E1E9) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x004192A4) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0041981E) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0041A39E) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0041A5A6) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0041B172) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0041B48C) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x00425B26) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x00426DEB) = 0x004C0BC0; // small_banner_index

		for( int i = 80; i < 180; i++ ){
			if( troop_book_leader_pic[i] != NULL ){ 
				HeapFree( GetProcessHeap(), 0, troop_book_leader_pic[i] );
				troop_book_leader_pic[i] = NULL;
			}
			if( troop_book_unit_pic[i] != NULL ){ 
				HeapFree( GetProcessHeap(), 0, troop_book_unit_pic[i] );
				troop_book_unit_pic[i] = NULL; 
			}
			if( troop_book_unit_desc[i] != NULL ){ 
				HeapFree( GetProcessHeap(), 0, troop_book_unit_desc[i] );
				troop_book_unit_desc[i] = NULL;
			}
		}

	}
}