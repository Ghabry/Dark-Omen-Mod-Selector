// Fixes Battles.eng limitations in the multiplayer scene

#include "header.h"

namespace multiplayer_scene
{
	char battle_eng_storage[308 * 200];

	void Load() {
		memset(battle_eng_storage, '\0', sizeof(battle_eng_storage));

		*((DWORD*)0x00404017) = (DWORD)&battle_eng_storage;
		*((DWORD*)0x00404078) = (DWORD)&battle_eng_storage;
		*((DWORD*)0x0040407F) = (DWORD)&battle_eng_storage;
		*((DWORD*)0x004044C1) = (DWORD)&battle_eng_storage;
	}
	void Unload() {
		*((DWORD*)0x00404017) = (DWORD)0x0054AB20;
		*((DWORD*)0x00404078) = (DWORD)0x0054AB20;
		*((DWORD*)0x0040407F) = (DWORD)0x0054AB20;
		*((DWORD*)0x004044C1) = (DWORD)0x0054AB20;
	}
}
