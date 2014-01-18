#include <windows.h>

#define DATA( name, type, address ) static type& name = (*((type*)address));
#define FUNC( name, address, ret_type, call_convention, args ) ret_type(call_convention * const name)args = (ret_type(call_convention *)args) address;
#define PFNC( name, address, ret_type, call_convention, args ) static ret_type (call_convention *& name)args = *( (ret_type(call_convention **)args)address);
#define WRITE_JMP( dst, src ) *((BYTE*)src) = 0xE9; *((DWORD*)(((BYTE*)src) + 1)) = (((DWORD)dst) - ((DWORD)src) - 5); 

namespace sprites
{
	struct SPRITE_SLOT
	{
		DWORD ref_count; // things using this sprite ( units, unit leaders, etc. )
		char name[32]; // GRUXBW, ST_ZZNewPlyr3, etc.
		DWORD type_id; // ?? ( always 0x8 for units )
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

	const DWORD nSlots = 512; // must be at least 257
	const DWORD Sprite_First = 1;
	const DWORD Sprite_Last = 95;
	const DWORD Portrait_First = 96;
	const DWORD Portrait_Last = 178;
	const DWORD Banner_First = 179;
	const DWORD Banner_Last = 251;
	const DWORD HUD = 255;
	const DWORD Expanded_First = 257;
	const DWORD Expanded_Last = nSlots - 1;

	// replaces table at 004CEB50
	SPRITE_SLOT SpriteTable [ nSlots ] = {
		{ 0, "VOIDTYPE", 0, 0 }, // 0
		{ 0, "BtlSprit", 0, 0 }, // 1
		{ 0, "flags", 1, 0 }, // 2
		{ 0, "missiles", 1, 0 }, // 3
		{ 0, "mi", 1, 0 }, // 4
		{ 0, "SPL_ITEM", 0, 0 }, // 5
		{ 0, "SPL_BRI", 0, 0 }, // 6
		{ 0, "SPL_BRI", 0, 0 }, // 7
		{ 0, "SPL_BRI", 0, 0 }, // 8
		{ 0, "SPL_DARK", 0, 0 }, // 9
		{ 0, "XST_ZNewMisc5", 0, 0 }, // 10
		{ 0, "XST_ZNewMisc6", 0, 0 }, // 11
		{ 0, "GRAILK", 8, 0 }, // 12
		{ 0, "KREALM", 8, 0 }, // 13
		{ 0, "DWARF", 8, 0 }, // 14
		{ 0, "BERNHD", 8, 0 }, // 15
		{ 0, "GRUCAV", 8, 0 }, // 16
		{ 0, "GRUINF", 8, 0 }, // 17
		{ 0, "GRUXBW", 8, 0 }, // 18
		{ 0, "CANNON", 8, 0 }, // 19
		{ 0, "CARLSS", 8, 0 }, // 20
		{ 0, "BRIGHT", 8, 0 }, // 21
		{ 0, "IMPHAL", 8, 0 }, // 22
		{ 0, "IMPBOW", 8, 0 }, // 23
		{ 0, "FLAGEL", 8, 0 }, // 24
		{ 0, "ST_ImpSwordsman", 8, 0 }, // 25
		{ 0, "STMTNK", 8, 0 }, // 26
		{ 0, "MORTAR", 8, 0 }, // 27
		{ 0, "OGRE", 8, 0 }, // 28
		{ 0, "OUTINF", 8, 0 }, // 29
		{ 0, "IMPGRT", 8, 0 }, // 30
		{ 0, "ICEMAG", 8, 0 }, // 31
		{ 0, "RAGNAR", 8, 0 }, // 32
		{ 0, "OUTPIS", 8, 0 }, // 33
		{ 0, "ST_ReiksKnight", 8, 0 }, // 34
		{ 0, "ARTILL", 8, 0 }, // 35
		{ 0, "GLADE", 8, 0 }, // 36
		{ 0, "ELFARC", 8, 0 }, // 37
		{ 0, "TREEMN", 8, 0 }, // 38
		{ 0, "ST_BrokenWagon", 8, 0 }, // 39
		{ 0, "DUMMY", 8, 0 }, // 40
		{ 0, "ST_ZZNewPlyr3", 8, 0 }, // 41
		{ 0, "ST_ZZNewPlyr4", 8, 0 }, // 42
		{ 0, "ST_ZZNewPlyr5", 8, 0 }, // 43
		{ 0, "ST_ZZNewPlyr6", 8, 0 }, // 44
		{ 0, "TROLL", 8, 0 }, // 45
		{ 0, "SPIDER", 8, 0 }, // 46
		{ 0, "SCORPN", 8, 0 }, // 47
		{ 0, "NGOB", 8, 0 }, // 48
		{ 0, "FANATC", 8, 0 }, // 49
		{ 0, "NGARCH", 8, 0 }, // 50
		{ 0, "NGSHAM", 8, 0 }, // 51
		{ 0, "ARRERB", 8, 0 }, // 52
		{ 0, "BOAR", 8, 0 }, // 53
		{ 0, "ORCBOY", 8, 0 }, // 54
		{ 0, "BIGUNS", 8, 0 }, // 55
		{ 0, "BOLT", 8, 0 }, // 56
		{ 0, "ROCKLB", 8, 0 }, // 57
		{ 0, "ORCSHM", 8, 0 }, // 58
		{ 0, "ST_ZZNewGreen1", 8, 0 }, // 59
		{ 0, "ST_ZZNewGreen2", 8, 0 }, // 60
		{ 0, "ST_ZZNewGreen3", 8, 0 }, // 61
		{ 0, "ST_ZZNewGreen4", 8, 0 }, // 62
		{ 0, "ST_ZZNewGreen5", 8, 0 }, // 63
		{ 0, "ST_ZZNewGreen6", 8, 0 }, // 64
		{ 0, "DREAD", 8, 0 }, // 65
		{ 0, "GHOUL", 8, 0 }, // 66
		{ 0, "CARST", 8, 0 }, // 67
		{ 0, "VAMP", 8, 0 }, // 68
		{ 0, "ST_Vampiress", 8, 0 }, // 69
		{ 0, "MUMMY", 8, 0 }, // 70
		{ 0, "NECRO", 8, 0 }, // 71
		{ 0, "SSKULL", 8, 0 }, // 72
		{ 0, "SKELBW", 8, 0 }, // 73
		{ 0, "SKELCV", 8, 0 }, // 74
		{ 0, "SKELWR", 8, 0 }, // 75
		{ 0, "CHARIO", 8, 0 }, // 76
		{ 0, "UNKNIG", 8, 0 }, // 77
		{ 0, "WIGHT", 8, 0 }, // 78
		{ 0, "WRAITH", 8, 0 }, // 79
		{ 0, "ZOMBIE", 8, 0 }, // 80
		{ 0, "NAGASH", 8, 0 }, // 81
		{ 0, "SKELHS", 8, 0 }, // 82
		{ 0, "ST_ZZNewUndead3", 8, 0 }, // 83
		{ 0, "ST_ZZNewUndead4", 8, 0 }, // 84
		{ 0, "ST_ZZNewUndead5", 8, 0 }, // 85
		{ 0, "ST_ZZNewUndead6", 8, 0 }, // 86
		{ 0, "BANSWD", 8, 0 }, // 87
		{ 0, "BANARC", 8, 0 }, // 88
		{ 0, "PEASMN", 8, 0 }, // 89
		{ 0, "PEASBY", 8, 0 }, // 90
		{ 0, "ST_ZZNewOther3", 8, 0 }, // 91
		{ 0, "ST_ZZNewOther4", 8, 0 }, // 92
		{ 0, "ST_ZZNewOther5", 8, 0 }, // 93
		{ 0, "PEASWM", 8, 0 }, // 94
		{ 0, "XST_LastSprite", 0, 0 }, // 95
		{ 0, "PT_Bernhardt", 0, 0 }, // 96
		{ 0, "PT_Zimmerman", 0, 1 }, // 97
		{ 0, "PT_Schepke", 0, 2 }, // 98
		{ 0, "PT_Fletcher", 0, 3 }, // 99
		{ 0, "PT_Schwatzkopf", 0, 4 }, // 100
		{ 0, "PT_Rotgut", 0, 5 }, // 101
		{ 0, "PT_Weiss", 0, 6 }, // 102
		{ 0, "PT_OutlawInf", 0, 7 }, // 103
		{ 0, "PT_Franz", 0, 8 }, // 104
		{ 0, "PT_Lieberwitz", 0, 9 }, // 105
		{ 0, "PT_Theogonist", 0, 0x0A }, // 106
		{ 0, "PT_WitchHunter", 0, 0x0B }, // 107
		{ 0, "PT_Carlsson", 0, 0x0C }, // 108
		{ 0, "PT_BogenMayor", 0, 0x0D }, // 109
		{ 0, "PT_Flamestrike", 0, 0x0E }, // 110
		{ 0, "PT_Schaeffer", 0, 0x0F }, // 111
		{ 0, "PT_ImpHalberdier", 0, 0x10 }, // 112
		{ 0, "PT_ImpSwordsman", 0, 0x11 }, // 113
		{ 0, "PT_ImpLongbows", 0, 0x12 }, // 114
		{ 0, "PT_Eusebio", 0, 0x13 }, // 115
		{ 0, "PT_Uberdorf", 0, 0x14 }, // 116
		{ 0, "PT_Blomkwist", 0, 0x15 }, // 117
		{ 0, "PT_Todbringer", 0, 0xFF }, // 118
		{ 0, "PT_Flugenheim", 0, 0x16 }, // 119
		{ 0, "PT_DeLaTour", 0, 0x17 }, // 120
		{ 0, "PT_LeGrande", 0, 0x18 }, // 121
		{ 0, "PT_Leoncouer", 0, 0x19 }, // 122
		{ 0, "PT_Stormbringer", 0, 0x1A }, // 123
		{ 0, "PT_Ragnar", 0, 0x1B }, // 124
		{ 0, "PT_Tzarina", 0, 0x1C }, // 125
		{ 0, "PT_Bloodfist", 0, 0x1D }, // 126
		{ 0, "PT_Galed", 0, 0x1E }, // 127
		{ 0, "PT_Elrod", 0, 0x1F }, // 128
		{ 0, "PT_Knarlroot", 0, 0x20 }, // 129
		{ 0, "PT_Orion", 0, 0x21 }, // 130
		{ 0, "PT_Fitzherbert", 0, 0xFF }, // 131
		{ 0, "PT_Rotblud", 0, 0xFF }, // 132
		{ 0, "PT_ZZNewPlyrPort3", 0, 0xFF }, // 133
		{ 0, "PT_ZZNewPlyrPort4", 0, 0xFF }, // 134
		{ 0, "PT_ZZNewPlyrPort5", 0, 0xFF }, // 135
		{ 0, "PT_ZZNewPlyrPort6", 0, 0xFF }, // 136
		{ 0, "PT_NightGoblin", 0, 0x22 }, // 137
		{ 0, "PT_NightGobFanatic", 0, 0xFF }, // 138
		{ 0, "PT_NightGobArcher", 0, 0x23 }, // 139
		{ 0, "PT_NightGobShaman", 0, 0x24 }, // 140
		{ 0, "PT_OrcBoy", 0, 0x25 }, // 141
		{ 0, "PT_OrcBigUn", 0, 0x26 }, // 142
		{ 0, "PT_OrcArrerBoy", 0, 0x27 }, // 143
		{ 0, "PT_OrcBoarBoy", 0, 0x28 }, // 144
		{ 0, "PT_OrcBoltThrower", 0, 0x29 }, // 145
		{ 0, "PT_OrcRockLobber", 0, 0x2A }, // 146
		{ 0, "PT_OrcShaman", 0, 0x2B }, // 147
		{ 0, "PT_GiganticSpider", 0, 0x2C }, // 148
		{ 0, "PT_GiantScorpion", 0, 0x2D }, // 149
		{ 0, "PT_Troll", 0, 0x2E }, // 150
		{ 0, "PT_ZZNewGreenPort2", 0, 0xFF }, // 151
		{ 0, "PT_ZZNewGreenPort3", 0, 0xFF }, // 152
		{ 0, "PT_ZZNewGreenPort4", 0, 0xFF }, // 153
		{ 0, "PT_ZZNewGreenPort5", 0, 0xFF }, // 154
		{ 0, "PT_ZZNewGreenPort6", 0, 0xFF }, // 155
		{ 0, "PT_Zombie", 0, 0x2F }, // 156
		{ 0, "PT_SkellyInf", 0, 0x30 }, // 157
		{ 0, "PT_Ghoul", 0, 0x31 }, // 158
		{ 0, "PT_Wight", 0, 0x32 }, // 159
		{ 0, "PT_Mummy", 0, 0x33 }, // 160
		{ 0, "PT_SkellyCav", 0, 0x34 }, // 161
		{ 0, "PT_SkellyArcher", 0, 0x35 }, // 162
		{ 0, "PT_SkullCatapult", 0, 0x36 }, // 163
		{ 0, "PT_UndeadChariot", 0, 0x37 }, // 164
		{ 0, "PT_Necromancer", 0, 0x38 }, // 165
		{ 0, "PT_Vampire", 0, 0x39 }, // 166
		{ 0, "PT_Wraith", 0, 0x3A }, // 167
		{ 0, "PT_DreadKing", 0, 0x3B }, // 168
		{ 0, "PT_Carstein", 0, 0x3C }, // 169
		{ 0, "PT_Vampiress", 0, 0xFF }, // 170
		{ 0, "PT_TheBlackGrail", 0, 0x3D }, // 171
		{ 0, "PT_HandOfNagash", 0, 0x3E }, // 172
		{ 0, "PT_ZZNewUndedPort2", 0, 0xFF }, // 173
		{ 0, "PT_ZZNewUndedPort3", 0, 0xFF }, // 174
		{ 0, "PT_ZZNewUndedPort4", 0, 0xFF }, // 175
		{ 0, "PT_ZZNewUndedPort5", 0, 0xFF }, // 176
		{ 0, "PT_ZZNewUndedPort6", 0, 0xFF }, // 177
		{ 0, "XPT_LastPort", 0, 0 }, // 178
		{ 0, "HBGRAILK", 0, 0 }, // 179
		{ 0, "HBKREALM", 0, 0 }, // 180
		{ 0, "HBDWARF", 0, 0 }, // 181
		{ 0, "HBGRUCAV", 0, 0 }, // 182
		{ 0, "HBGRUINF", 0, 0 }, // 183
		{ 0, "HBGRUXBW", 0, 0 }, // 184
		{ 0, "HBCANNON", 1, 0 }, // 185
		{ 0, "HBCARLSS", 0, 0 }, // 186
		{ 0, "HBBRIGHT", 0, 0 }, // 187
		{ 0, "HBIMPHAL", 1, 0 }, // 188
		{ 0, "HBIMPBOW", 0, 0 }, // 189
		{ 0, "HBFLAGEL", 0, 0 }, // 190
		{ 0, "HBIMPSWD", 0, 0 }, // 191
		{ 0, "HBSTMTNK", 1, 0 }, // 192
		{ 0, "HBMORTAR", 0, 0 }, // 193
		{ 0, "HBOGRE", 0, 0 }, // 194
		{ 0, "HBOUTINF", 0, 0 }, // 195
		{ 0, "HBIMPGRT", 0, 0 }, // 196
		{ 0, "HBICEMAG", 0, 0 }, // 197
		{ 0, "HBRAGNAR", 7, 0 }, // 198
		{ 0, "HBOUTPIS", 3, 0 }, // 199
		{ 0, "BT_ReiksKnight", 0, 0 }, // 200
		{ 0, "HBGLADE", 6, 0 }, // 201
		{ 0, "HBELFARC", 2, 0 }, // 202
		{ 0, "HBTREEMN", 0, 0 }, // 203
		{ 0, "HBIMPCAN", 0, 0 }, // 204
		{ 0, "BT_TalabheimCannon", 0, 0 }, // 205
		{ 0, "BT_ImpLongbows", 0, 0 }, // 206
		{ 0, "BT_ZZNewPlyrBann4", 0, 0 }, // 207
		{ 0, "BT_ZZNewPlyrBann5", 0, 0 }, // 208
		{ 0, "BT_ZZNewPlyrBann6", 0, 0 }, // 209
		{ 0, "OBTROLL", 0, 0 }, // 210
		{ 0, "OBSPIDER", 0, 0 }, // 211
		{ 0, "OBSCORPN", 0, 0 }, // 212
		{ 0, "OBNGOB", 0, 0 }, // 213
		{ 0, "OBFANATC", 0, 0 }, // 214
		{ 0, "OBNGARCH", 5, 0 }, // 215
		{ 0, "OBNGSHAM", 0, 0 }, // 216
		{ 0, "OBARRERB", 5, 0 }, // 217
		{ 0, "OBBOAR", 0, 0 }, // 218
		{ 0, "OBORCBOY", 0, 0 }, // 219
		{ 0, "OBBIGUNS", 0, 0 }, // 220
		{ 0, "OBBOLT", 0, 0 }, // 221
		{ 0, "OBROCKLB", 0, 0 }, // 222
		{ 0, "OBORCSHM", 0, 0 }, // 223
		{ 0, "BT_ZZNewGreenBann1", 0, 0 }, // 224
		{ 0, "BT_ZZNewGreenBann2", 0, 0 }, // 225
		{ 0, "BT_ZZNewGreenBann3", 0, 0 }, // 226
		{ 0, "BT_ZZNewGreenBann4", 0, 0 }, // 227
		{ 0, "BT_ZZNewGreenBann5", 0, 0 }, // 228
		{ 0, "BT_ZZNewGreenBann6", 0, 0 }, // 229
		{ 0, "DBDREAD", 0, 0 }, // 230
		{ 0, "DBGHOUL", 0, 0 }, // 231
		{ 0, "DBCARST", 0, 0 }, // 232
		{ 0, "DBVAMP", 0, 0 }, // 233
		{ 0, "BT_Vampiress", 0, 0 }, // 234
		{ 0, "DBMUMMY", 0, 0 }, // 235
		{ 0, "DBNECRO", 0, 0 }, // 236
		{ 0, "DBSSKULL", 0, 0 }, // 237
		{ 0, "DBSKELBW", 0, 0 }, // 238
		{ 0, "DBSKELCV", 0, 0 }, // 239
		{ 0, "DBSKELWR", 0, 0 }, // 240
		{ 0, "DBCHARIO", 4, 0 }, // 241
		{ 0, "DBUNKNIG", 0, 0 }, // 242
		{ 0, "DBWIGHT", 0, 0 }, // 243
		{ 0, "DBWRAITH", 4, 0 }, // 244
		{ 0, "DBZOMBIE", 0, 0 }, // 245
		{ 0, "DBHAND", 0, 0 }, // 246
		{ 0, "DBGYPSWD", 0, 0 }, // 247
		{ 0, "DBGYPARC", 0, 0 }, // 248
		{ 0, "BT_ZZNewUndeadBan4", 0, 0 }, // 249
		{ 0, "BT_ZZNewUndeadBan5", 0, 0 }, // 250
		{ 0, "BT_ZZNewUndeadBan6", 0, 0 }, // 251
		{ 0, 0, 0, 0 }, // 252
		{ 0, 0, 0, 0 }, // 253
		{ 0, "void", 0, 0 }, // 254
		{ 0, "HUD", 1, 0 }, // 255
		{ 0, "ICONS2", 0, 0 } // 256
		//expanded slots
	};


	// replaces the dynamically allocated array pointed to by dword_526D24 
	void* Loaded_Sprite_Array[ nSlots ];

	// these offsets somehow control how a sprite is used. e.g. archers or infantry or wizard
	// replaces the table at 004EBC88 
	WORD offset_table[ _countof( Loaded_Sprite_Array ) ] = {
		0xFFFF, // 0
		0x0000, // 1 
		0x000E, // 2
		0x001C, // 3
		0x002A, // 4
		0x0038, // 5
		0x0046, // 6
		0x0054, // 7
		0x0062, // 8
		0x0070, // 9
		0x0000, // 10
		0x0000, // 11
		0x008C, // 12
		0x008C, // 13
		0x010A, // 14
		0x008C, // 15
		0x008C, // 16
		0x007E, // 17
		0x007E, // 18
		0x009A, // 19
		0x008C, // 20
		0x00A8, // 21
		0x00FC, // 22
		0x0222, // 23
		0x0188, // 24
		0x023E, // 25
		0x01A4, // 26
		0x009A, // 27
		0x0196, // 28
		0x007E, // 29
		0x007E, // 30
		0x00B6, // 31
		0x01C0, // 32
		0x008C, // 33
		0x023E, // 34
		0x007E, // 35
		0x00FC, // 36
		0x0134, // 37
		0x0196, // 38
		0x023E, // 39
		0x0214, // 40
		0x023E, // 41
		0x023E, // 42
		0x023E, // 43
		0x023E, // 44
		0x017A, // 45
		0x016C, // 46
		0x016C, // 47
		0x007E, // 48
		0x01B2, // 49
		0x007E, // 50
		0x00C4, // 51
		0x0134, // 52
		0x0142, // 53
		0x007E, // 54
		0x007E, // 55
		0x01EA, // 56
		0x01F8, // 57
		0x00D2, // 58
		0x023E, // 59
		0x023E, // 60
		0x023E, // 61
		0x023E, // 62
		0x023E, // 63
		0x023E, // 64
		0x01CE, // 65
		0x010A, // 66
		0x00EE, // 67
		0x0230, // 68
		0x023E, // 69
		0x007E, // 70
		0x00E0, // 71
		0x0206, // 72
		0x0222, // 73
		0x01DC, // 74
		0x007E, // 75
		0x0150, // 76
		0x01DC, // 77
		0x007E, // 78
		0x017A, // 79
		0x0126, // 80
		0x0150, // 81
		0x015E, // 82
		0x023E, // 83
		0x023E, // 84
		0x023E, // 85
		0x023E, // 86
		0x007E, // 87
		0x0222, // 88
		0x0118, // 89
		0x0118, // 90
		0x023E, // 91
		0x023E, // 92
		0x023E, // 93
		0x0118, // 94
		0x0000  // 95
		// expanded slots...
	};


	// replaces sub_4184B0
	DWORD __cdecl GetType( DWORD index )
	{
		return SpriteTable[index].type_id;
	}


	// replaces sub_4184D0
	DWORD __cdecl AddRef( DWORD index )
	{
		return SpriteTable[index].ref_count++;
	}


	// replaces sub_4184F0
	DWORD __cdecl Release( DWORD index )
	{
		if( SpriteTable[index].ref_count != 0 ) SpriteTable[index].ref_count--;
		return SpriteTable[index].ref_count;
	}


	// replaces sub_418510
	void __cdecl ZeroRef()
	{
		for( int i = 0; i < _countof( SpriteTable ); i++ ) SpriteTable[i].ref_count = 0;
	}


	// replaces sub_418540
	DWORD __cdecl GetLoadedIndex( DWORD index )
	{
		return SpriteTable[index].loaded_index;
	}


	// replaces sub_42B510
	void __cdecl LoadReferencedSprites()
	{
		RtlSecureZeroMemory( Loaded_Sprite_Array, sizeof( Loaded_Sprite_Array ) );

		int loaded_count = 0;
		for( int i = Sprite_First; i < nSlots; i++ )
		{
			// load from 1 thru 95 then skip to end
			if( ( i == Portrait_First ) )
			{
				i = Expanded_First - 1;
				continue;
			}

			if( SpriteTable[i].ref_count != 0 ) // load sprite if used
			{	
				char szPath[MAX_PATH];
				wsprintfA( szPath, GetGameDirStr( "[SPRITES]\\%s.spr" ), SpriteTable[i].name );				
				LoadSprite( *((DWORD*)0x005014BC), 0, szPath, &(Loaded_Sprite_Array[loaded_count]) );
				if( Loaded_Sprite_Array[loaded_count] != 0 )
				{
					SpriteTable[i].loaded_index_sprites = loaded_count;
					loaded_count++;
				}
			}
		}	

		// some random OO junk in the original: set pointer to function
		*((DWORD*)0x00502AF4) = 0x0042B430;
	}


	// replaces sub_42B600
	void __cdecl FreeLoadedSprites( )
	{
		for( int i = 0; i < nSlots; i++ )
		{
			// portraits have a hard-coded loaded_index... so skip
			if( ( i == Portrait_First ) )
			{ 
				i = Portrait_Last;
				continue;
			}

			SpriteTable[i].loaded_index = 0;
		}
	}

/*
	I'm pretty sure the game leaks "Loaded_Banner_Array"... // *((DWORD*)0x00526D2C) = (DWORD)&Loaded_Banner_Array; 
	I'm too lazy to figure out why the code below isn't working... as I don't really need it

	// replaces sub_42B9E0
	void __cdecl LoadReferencedBanners()
	{
		char szPath[MAX_PATH];
		int loaded_count = 0;

		RtlSecureZeroMemory( Loaded_Banner_Array, sizeof( Loaded_Banner_Array ) );

		sub_004338D0( *((DWORD*)0x005014BC), 0xA0, 0x004D6EC0, 8, 0x00526D20, (*((DWORD*)0x00501AAC) & 0x10) );

		for( int i = Banner_First; i <= Banner_Last; i++ )
		{
			if( SpriteTable[i].ref_count != 0 ) // load sprite if used
			{
				wsprintfA( szPath, "[BANNERS]\\%s.spr", SpriteTable[i].name );
				LoadBanner( *((DWORD*)0x00526D20), szPath, &Loaded_Banner_Array[loaded_count], 1, 1, (*((DWORD*)0x00501AAC) & 0x10) );
				if( Loaded_Banner_Array[loaded_count] != 0 )
				{
					sub_00435340( *((DWORD*)0x005014BC), 4, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0, 0, 4, 0 );
					sub_00435340( *((DWORD*)0x005014BC), 0, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 1, 1, 4, 0 );
					SpriteTable[i].loaded_index_banners = loaded_count;
					loaded_count++;
				}
			}
		}

		// load HUD
		wsprintfA( szPath, "[SPRITES]\\%s.spr", SpriteTable[HUD].name );
		*((DWORD*)0x00526D28) = loaded_count << 0x10; // HIWORD
		LoadBanner( *((DWORD*)0x00526D20), szPath, &Loaded_Banner_Array[loaded_count], 1, 1, (*((DWORD*)0x00501AAC) & 0x10) );
		if( Loaded_Sprite_Array[HUD] != 0 )
		{
			sub_00435340( *((DWORD*)0x005014BC), 4, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x00, 0x00, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 1, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x00, 0x01, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 1, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x31, 0x31, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 2, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x04, 0x23, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 6, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x2C, 0x2F, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 1, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x30, 0x30, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 3, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x50, 0x67, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 5, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x68, 0x71, 4, 0 );
			sub_00435340( *((DWORD*)0x005014BC), 7, Loaded_Banner_Array[loaded_count], *((DWORD*)0x00526D20), 0x32, 0x40, 4, 0 );

			SpriteTable[HUD].loaded_index_banners = loaded_count;
		}
	}
*/

	void InstallHooks()
	{
		WRITE_JMP( GetType, 0x004184B0 );
		WRITE_JMP( AddRef, 0x004184D0 );
		WRITE_JMP( Release, 0x004184F0 );
		WRITE_JMP( ZeroRef, 0x00418510 );
		WRITE_JMP( GetLoadedIndex, 0x00418540 );
		WRITE_JMP( LoadReferencedSprites, 0x0042B510 );
		WRITE_JMP( FreeLoadedSprites, 0x0042B600 );

		// load banners
		*((DWORD**)0x0042BA17) = &(SpriteTable[179].ref_count);
		*((DWORD**)0x0042BA26) = &(SpriteTable[257].ref_count);
		*((DWORD**)0x0042BA3F) = (DWORD*)(&(SpriteTable[179].name));
		*((DWORD**)0x0042BADA) = (DWORD*)(&(SpriteTable[252].name));
		*((DWORD**)0x0042BC7F) = (DWORD*)(&(SpriteTable[257].name));

		// misc
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
	}
}