// the multiplier look of the [tab/space] battlemap in single player
// pre-rendered battlemaps ( [MAPS]\\maps.pbd ) are no longer used
// note: sp_mapbord is the background used
//
// force a jump - to use part of the "3DDebug\\MapGrab" feature...

#include "header.h"

#pragma intrinsic( memcpy )
namespace mapboard
{
	void Load(){ memcpy( (void*)0x00424320, "\xE9\x00\x01\x00\x00\x90", 6 ); }
	void Unload(){ memcpy( (void*)0x00424320, "\x0F\x85\xFF\x00\x00\x00", 6 ); }
}