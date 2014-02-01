#include "header.h"

/* 
increment the reference count of spell sprites and magic books just before loading them
which should allow a spellcaster to have any spell from any school of magic, without crashing 
it should be safe to inc refs because at the end of the battle all refs are zero'd 

mixed_magic and spr_extender hooks should play nice together...
*/

#define DATA( name, type, address ) static type& name = (*((type*)address));
#define HOOK_CALL( dst, src ) *((DWORD*)(((BYTE*)src) + 1)) = (((DWORD)dst) - ((DWORD)src) - 5); 
#define FUNC( name, address, ret_type, call_convention, args ) ret_type(call_convention * const name)args = (ret_type(call_convention *)args) address;

namespace mixed_magic
{
	void __cdecl IncSplSprRefs_LoadRefSpr()
	{
		FUNC( SpriteAddRef, 0x004184D0, DWORD, __cdecl, ( DWORD index ) );
		FUNC( LoadReferencedSprites, 0x0042B510, void, __cdecl, ( ) );

		SpriteAddRef( 5 ); // SPL_ITEM
		SpriteAddRef( 6 ); // SPL_BRI
		SpriteAddRef( 7 ); // SPL_BRI // Ice?
		SpriteAddRef( 8 ); // SPL_BRI // Waaargh?
		SpriteAddRef( 9 ); // SPL_DARK
		LoadReferencedSprites();
	}

	void IncBookRefs_LoadRefFurnture( DWORD arg1, DWORD arg2 )
	{
		FUNC( FurntureAddRef, 0x0041B6A0, DWORD, __cdecl, ( DWORD index ) );
		FUNC( LoadReferencedFurnture, 0x00408280, void, __cdecl, ( DWORD, DWORD ) );

		//FurntureAddRef( 2 ) // MT_ItemMagicMesh // used?
		FurntureAddRef( 3 ); // Bright
		FurntureAddRef( 4 ); // Ice
		FurntureAddRef( 5 ); // Green ( waaargh )
		FurntureAddRef( 6 ); // Dark
	    LoadReferencedFurnture( arg1, arg2 );
	}

	void Load(){
		HOOK_CALL( &IncSplSprRefs_LoadRefSpr, 0x00451021 );
		HOOK_CALL( &IncBookRefs_LoadRefFurnture, 0x00401CDC );
		HOOK_CALL( &IncBookRefs_LoadRefFurnture, 0x00401E73 );
	}

	void Unload() {
		HOOK_CALL( 0x0042B510, 0x00451021 );
		HOOK_CALL( 0x00408280, 0x00401CDC );
		HOOK_CALL( 0x00408280, 0x00401E73 );
	}
}