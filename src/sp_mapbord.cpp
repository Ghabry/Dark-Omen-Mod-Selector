// the multiplier look of the [tab/space] battlemap in single player
// ( [MAPS]\\maps.pbd is no longer used )

#include "header.h"

namespace sp_mapbord
{
	void Load(){ memcpy( (void*)0x00424320, "\xE9\x00\x01\x00\x00\x90", 6 ); }
	void Unload(){ memcpy( (void*)0x00424320, "\x0F\x85\xFF\x00\x00\x00", 6 ); }
}