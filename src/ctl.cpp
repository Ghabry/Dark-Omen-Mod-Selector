// repoint [armytmp] to a folder in the game directory
// somewhere that doesn't require admin rights to write to...
// folder is created if missing

#include "header.h"
#include "stdint.h"
#include "functions.h"
#include <detours.h>

namespace ctl
{
	struct CTLEngineStruct {
		int a;
	};

	typedef struct CTLEngineStruct CTLEngineStruct;

	typedef int16_t(*ctlFunc_t)(CTLEngineStruct* engine);

	ctlFunc_t* ctl_opcode_table;

	int16_t* current_command;
	int32_t** current_function;

	noarg_int_t battle_init_orig = (noarg_int_t)0x4714B0;

	int battle_init() {
		// Reset deployment limit
		uint8_t* limit = (uint8_t*)0x45D999;
		*limit = 10;

		return battle_init_orig();
	}

	int16_t f1_opcode_handler(CTLEngineStruct* engine) {
		int16_t opcode = (*current_function)[*current_command + 1];
		int16_t arg = (*current_function)[*current_command + 2];

		switch (opcode)	{
		case 0: // set_deployment_limit
			uint8_t* limit = (uint8_t*)0x45D999;
			*limit = arg;
			break;
		}

		return *current_command + 3;
	}

	int16_t f2_opcode_handler(CTLEngineStruct* engine) {
		// To be decided
		return *current_command + 1;
	}

	void Load()	{
		ctl_opcode_table = (ctlFunc_t*)0x004E7250;
		current_command = (int16_t*)0x00504844;
		current_function = (int32_t**)0x000504824;

		ctl_opcode_table[241] = f1_opcode_handler;
		ctl_opcode_table[242] = f2_opcode_handler;

		battle_init_orig = (noarg_int_t)DetourFunction((PBYTE)battle_init_orig, (PBYTE)battle_init);
	}

	void Unload() {
		
	}
}
