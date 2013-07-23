#pragma once

#include <map>
#include <ctime>
#include <Windows.h>
#include "detours.h"

namespace darkomen {
namespace ctl {
	struct CTL_EngineStruct;

	typedef __int16 (*ctlScriptFunc_t)(CTL_EngineStruct* ctlEngineStruct);
	ctlScriptFunc_t* ctlScriptFunc_orig = (ctlScriptFunc_t*)0x4E7250;
	ctlScriptFunc_t ctlScriptFunc_detour[241];

	struct CTL_EngineStruct {
		char* currentRegiment;
		int* startFunctionPointer;
		short controlFlag;
		short startCurrentCommand;
		int continueRegimentScriptExecution;
	};

	struct CTL_EventStruct {
		__int16 targetId;
		__int16 eventId;
		__int16 arg1_sourceId;
		__int16 arg2;
		__int16 arg3;
		__int16 arg4;
		__int16 arg5;
		__int16 indexLast;
	};


	void traceStart(CTL_EngineStruct* ) {}

	void traceEnd(CTL_EngineStruct* ) {}

	__int16 ctlCall(CTL_EngineStruct* ctlEngineStruct, int id) {
		int* functionPointer = *(int**)0x00504824;
		__int16 currentCommand = *(__int16*)0x00504844;
		//int* opcode = (functionPointer) + currentCommand;
		//int target = opcode - 0x8000;
#if 0
		time_t t = time(NULL);
		struct tm * zeit = gmtime ( &t );
		fprintf(a, "[%02d:%02d:%02d]",
			zeit->tm_hour, zeit->tm_min, zeit->tm_sec);

		short aaa = (short)(ctlEngineStruct->currentRegiment);
		fprintf(a, " %02x", aaa);
		/*if (opNames[id] != NULL) {
			fprintf(a, " %s", opNames[id]);
		} else*/
			fprintf(a, " #%x", id);
		if (opLengths[id] == 0) {

		} else if (opLengths[id] == 1) {
			fprintf(a, " %d", opcode[1]);
		} else if (opLengths[id] == 2) {
			fprintf(a, " %d", opcode[1]);
			fprintf(a, " %d", opcode[2]);
		} else if (opLengths[id] == 3) {
			fprintf(a, " %d", opcode[1]);
			fprintf(a, " %d", opcode[2]);
			fprintf(a, " %d", opcode[3]);
		}
		fprintf(a, " %02x", ctlEngineStruct->controlFlag);
		for (int i = 0; i < 1576; ++i)
		fprintf(a, "\r\n");
#endif
		__int16 result = ctlScriptFunc_detour[id](ctlEngineStruct);
		return result;
	}


	__int16 ctlScriptFunc(CTL_EngineStruct* ctlEngineStruct) {
		int* functionPointer = *(int**)0x00504824;
		__int16 currentCommand = *(__int16*)0x00504844;

		int opcode = (*functionPointer) + currentCommand * 4;
		int target = opcode - 0x8000;
		__int16 result = ctlScriptFunc_detour[target](ctlEngineStruct);
		return result;
	}


#pragma region ctlfuncs
	__int16 ctlScriptFunc_00(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 0);
	}
	__int16 ctlScriptFunc_01(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 1);
	}
	__int16 ctlScriptFunc_02(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 2);
	}
	__int16 ctlScriptFunc_03(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 3);
	}
	__int16 ctlScriptFunc_04(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 4);
	}
	__int16 ctlScriptFunc_05(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 5);
	}
	__int16 ctlScriptFunc_06(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 6);
	}
	__int16 ctlScriptFunc_07(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 7);
	}
	__int16 ctlScriptFunc_08(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 8);
	}
	__int16 ctlScriptFunc_09(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 9);
	}
	__int16 ctlScriptFunc_0a(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 10);
	}
	__int16 ctlScriptFunc_0b(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 11);
	}
	__int16 ctlScriptFunc_0c(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 12);
	}
	__int16 ctlScriptFunc_0d(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 13);
	}
	__int16 ctlScriptFunc_0e(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 14);
	}
	__int16 ctlScriptFunc_0f(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 15);
	}
	__int16 ctlScriptFunc_10(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 16);
	}
	__int16 ctlScriptFunc_11(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 17);
	}
	__int16 ctlScriptFunc_12(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 18);
	}
	__int16 ctlScriptFunc_13(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 19);
	}
	__int16 ctlScriptFunc_14(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 20);
	}
	__int16 ctlScriptFunc_15(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 21);
	}
	__int16 ctlScriptFunc_16(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 22);
	}
	__int16 ctlScriptFunc_17(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 23);
	}
	__int16 ctlScriptFunc_18(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 24);
	}
	__int16 ctlScriptFunc_19(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 25);
	}
	__int16 ctlScriptFunc_1a(CTL_EngineStruct* ctlEngineStruct) {
		//multiplayerMessage_orig(1, 0, "Hello World :)");
		return ctlCall(ctlEngineStruct, 26);
	}
	__int16 ctlScriptFunc_1b(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 27);
	}
	__int16 ctlScriptFunc_1c(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 28);
	}
	__int16 ctlScriptFunc_1d(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 29);
	}
	__int16 ctlScriptFunc_1e(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 30);
	}
	__int16 ctlScriptFunc_1f(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 31);
	}
	__int16 ctlScriptFunc_20(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 32);
	}
	__int16 ctlScriptFunc_21(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 33);
	}
	__int16 ctlScriptFunc_22(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 34);
	}
	__int16 ctlScriptFunc_23(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 35);
	}
	__int16 ctlScriptFunc_24(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 36);
	}
	__int16 ctlScriptFunc_25(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 37);
	}
	__int16 ctlScriptFunc_26(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 38);
	}
	__int16 ctlScriptFunc_27(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 39);
	}
	__int16 ctlScriptFunc_28(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 40);
	}
	__int16 ctlScriptFunc_29(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 41);
	}
	__int16 ctlScriptFunc_2a(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 42);
	}
	__int16 ctlScriptFunc_2b(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 43);
	}
	__int16 ctlScriptFunc_2c(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 44);
	}
	__int16 ctlScriptFunc_2d(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 45);
	}
	__int16 ctlScriptFunc_2e(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 46);
	}
	__int16 ctlScriptFunc_2f(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 47);
	}
	__int16 ctlScriptFunc_30(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 48);
	}
	__int16 ctlScriptFunc_31(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 49);
	}
	__int16 ctlScriptFunc_32(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 50);
	}
	__int16 ctlScriptFunc_33(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 51);
	}
	__int16 ctlScriptFunc_34(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 52);
	}
	__int16 ctlScriptFunc_35(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 53);
	}
	__int16 ctlScriptFunc_36(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 54);
	}
	__int16 ctlScriptFunc_37(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 55);
	}
	__int16 ctlScriptFunc_38(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 56);
	}
	__int16 ctlScriptFunc_39(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 57);
	}
	__int16 ctlScriptFunc_3a(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 58);
	}
	__int16 ctlScriptFunc_3b(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 59);
	}
	__int16 ctlScriptFunc_3c(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 60);
	}
	__int16 ctlScriptFunc_3d(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 61);
	}
	__int16 ctlScriptFunc_3e(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 62);
	}
	__int16 ctlScriptFunc_3f(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 63);
	}
	__int16 ctlScriptFunc_40(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 64);
	}
	__int16 ctlScriptFunc_41(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 65);
	}
	__int16 ctlScriptFunc_42(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 66);
	}
	__int16 ctlScriptFunc_43(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 67);
	}
	__int16 ctlScriptFunc_44(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 68);
	}
	__int16 ctlScriptFunc_45(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 69);
	}
	__int16 ctlScriptFunc_46(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 70);
	}
	__int16 ctlScriptFunc_47(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 71);
	}
	__int16 ctlScriptFunc_48(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 72);
	}
	__int16 ctlScriptFunc_49(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 73);
	}
	__int16 ctlScriptFunc_4a(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 74);
	}
	__int16 ctlScriptFunc_4b(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 75);
	}
	__int16 ctlScriptFunc_4c(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 76);
	}
	__int16 ctlScriptFunc_4d(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 77);
	}
	__int16 ctlScriptFunc_4e(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 78);
	}
	__int16 ctlScriptFunc_4f(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 79);
	}
	__int16 ctlScriptFunc_50(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 80);
	}
	__int16 ctlScriptFunc_51(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 81);
	}
	__int16 ctlScriptFunc_52(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 82);
	}
	__int16 ctlScriptFunc_53(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 83);
	}
	__int16 ctlScriptFunc_54(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 84);
	}
	__int16 ctlScriptFunc_55(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 85);
	}
	__int16 ctlScriptFunc_56(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 86);
	}
	__int16 ctlScriptFunc_57(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 87);
	}
	__int16 ctlScriptFunc_58(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 88);
	}
	__int16 ctlScriptFunc_59(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 89);
	}
	__int16 ctlScriptFunc_5a(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 90);
	}
	__int16 ctlScriptFunc_5b(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 91);
	}
	__int16 ctlScriptFunc_5c(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 92);
	}
	__int16 ctlScriptFunc_5d(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 93);
	}
	__int16 ctlScriptFunc_5e(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 94);
	}
	__int16 ctlScriptFunc_5f(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 95);
	}
	__int16 ctlScriptFunc_60(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 96);
	}
	__int16 ctlScriptFunc_61(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 97);
	}
	__int16 ctlScriptFunc_62(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 98);
	}
	__int16 ctlScriptFunc_63(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 99);
	}
	__int16 ctlScriptFunc_64(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 100);
	}
	__int16 ctlScriptFunc_65(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 101);
	}
	__int16 ctlScriptFunc_66(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 102);
	}
	__int16 ctlScriptFunc_67(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 103);
	}
	__int16 ctlScriptFunc_68(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 104);
	}
	__int16 ctlScriptFunc_69(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 105);
	}
	__int16 ctlScriptFunc_6a(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 106);
	}
	__int16 ctlScriptFunc_6b(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 107);
	}
	__int16 ctlScriptFunc_6c(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 108);
	}
	__int16 ctlScriptFunc_6d(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 109);
	}
	__int16 ctlScriptFunc_6e(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 110);
	}
	__int16 ctlScriptFunc_6f(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 111);
	}
	__int16 ctlScriptFunc_70(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 112);
	}
	__int16 ctlScriptFunc_71(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 113);
	}
	__int16 ctlScriptFunc_72(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 114);
	}
	__int16 ctlScriptFunc_73(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 115);
	}
	__int16 ctlScriptFunc_74(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 116);
	}
	__int16 ctlScriptFunc_75(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 117);
	}
	__int16 ctlScriptFunc_76(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 118);
	}
	__int16 ctlScriptFunc_77(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 119);
	}
	__int16 ctlScriptFunc_78(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 120);
	}
	__int16 ctlScriptFunc_79(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 121);
	}
	__int16 ctlScriptFunc_7a(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 122);
	}
	__int16 ctlScriptFunc_7b(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 123);
	}
	__int16 ctlScriptFunc_7c(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 124);
	}
	__int16 ctlScriptFunc_7d(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 125);
	}
	__int16 ctlScriptFunc_7e(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 126);
	}
	__int16 ctlScriptFunc_7f(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 127);
	}
	__int16 ctlScriptFunc_80(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 128);
	}
	__int16 ctlScriptFunc_81(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 129);
	}
	__int16 ctlScriptFunc_82(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 130);
	}
	__int16 ctlScriptFunc_83(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 131);
	}
	__int16 ctlScriptFunc_84(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 132);
	}
	__int16 ctlScriptFunc_85(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 133);
	}
	__int16 ctlScriptFunc_86(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 134);
	}
	__int16 ctlScriptFunc_87(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 135);
	}
	__int16 ctlScriptFunc_88(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 136);
	}
	__int16 ctlScriptFunc_89(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 137);
	}
	__int16 ctlScriptFunc_8a(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 138);
	}
	__int16 ctlScriptFunc_8b(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 139);
	}
	__int16 ctlScriptFunc_8c(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 140);
	}
	__int16 ctlScriptFunc_8d(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 141);
	}
	__int16 ctlScriptFunc_8e(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 142);
	}
	__int16 ctlScriptFunc_8f(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 143);
	}
	__int16 ctlScriptFunc_90(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 144);
	}
	__int16 ctlScriptFunc_91(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 145);
	}
	__int16 ctlScriptFunc_92(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 146);
	}
	__int16 ctlScriptFunc_93(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 147);
	}
	__int16 ctlScriptFunc_94(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 148);
	}
	__int16 ctlScriptFunc_95(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 149);
	}
	__int16 ctlScriptFunc_96(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 150);
	}
	__int16 ctlScriptFunc_97(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 151);
	}
	__int16 ctlScriptFunc_98(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 152);
	}
	__int16 ctlScriptFunc_99(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 153);
	}
	__int16 ctlScriptFunc_9a(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 154);
	}
	__int16 ctlScriptFunc_9b(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 155);
	}
	__int16 ctlScriptFunc_9c(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 156);
	}
	__int16 ctlScriptFunc_9d(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 157);
	}
	__int16 ctlScriptFunc_9e(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 158);
	}
	__int16 ctlScriptFunc_9f(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 159);
	}
	__int16 ctlScriptFunc_a0(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 160);
	}
	__int16 ctlScriptFunc_a1(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 161);
	}
	__int16 ctlScriptFunc_a2(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 162);
	}
	__int16 ctlScriptFunc_a3(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 163);
	}
	__int16 ctlScriptFunc_a4(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 164);
	}
	__int16 ctlScriptFunc_a5(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 165);
	}
	__int16 ctlScriptFunc_a6(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 166);
	}
	__int16 ctlScriptFunc_a7(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 167);
	}
	__int16 ctlScriptFunc_a8(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 168);
	}
	__int16 ctlScriptFunc_a9(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 169);
	}
	__int16 ctlScriptFunc_aa(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 170);
	}
	__int16 ctlScriptFunc_ab(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 171);
	}
	__int16 ctlScriptFunc_ac(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 172);
	}
	__int16 ctlScriptFunc_ad(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 173);
	}
	__int16 ctlScriptFunc_ae(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 174);
	}
	__int16 ctlScriptFunc_af(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 175);
	}
	__int16 ctlScriptFunc_b0(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 176);
	}
	__int16 ctlScriptFunc_b1(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 177);
	}
	__int16 ctlScriptFunc_b2(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 178);
	}
	__int16 ctlScriptFunc_b3(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 179);
	}
	__int16 ctlScriptFunc_b4(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 180);
	}
	__int16 ctlScriptFunc_b5(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 181);
	}
	__int16 ctlScriptFunc_b6(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 182);
	}
	__int16 ctlScriptFunc_b7(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 183);
	}
	__int16 ctlScriptFunc_b8(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 184);
	}
	__int16 ctlScriptFunc_b9(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 185);
	}
	__int16 ctlScriptFunc_ba(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 186);
	}
	__int16 ctlScriptFunc_bb(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 187);
	}
	__int16 ctlScriptFunc_bc(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 188);
	}
	__int16 ctlScriptFunc_bd(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 189);
	}
	__int16 ctlScriptFunc_be(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 190);
	}
	__int16 ctlScriptFunc_bf(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 191);
	}
	__int16 ctlScriptFunc_c0(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 192);
	}
	__int16 ctlScriptFunc_c1(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 193);
	}
	__int16 ctlScriptFunc_c2(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 194);
	}
	__int16 ctlScriptFunc_c3(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 195);
	}
	__int16 ctlScriptFunc_c4(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 196);
	}
	__int16 ctlScriptFunc_c5(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 197);
	}
	__int16 ctlScriptFunc_c6(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 198);
	}
	__int16 ctlScriptFunc_c7(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 199);
	}
	__int16 ctlScriptFunc_c8(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 200);
	}
	__int16 ctlScriptFunc_c9(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 201);
	}
	__int16 ctlScriptFunc_ca(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 202);
	}
	__int16 ctlScriptFunc_cb(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 203);
	}
	__int16 ctlScriptFunc_cc(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 204);
	}
	__int16 ctlScriptFunc_cd(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 205);
	}
	__int16 ctlScriptFunc_ce(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 206);
	}
	__int16 ctlScriptFunc_cf(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 207);
	}
	__int16 ctlScriptFunc_d0(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 208);
	}
	__int16 ctlScriptFunc_d1(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 209);
	}
	__int16 ctlScriptFunc_d2(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 210);
	}
	__int16 ctlScriptFunc_d3(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 211);
	}
	__int16 ctlScriptFunc_d4(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 212);
	}
	__int16 ctlScriptFunc_d5(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 213);
	}
	__int16 ctlScriptFunc_d6(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 214);
	}
	__int16 ctlScriptFunc_d7(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 215);
	}
	__int16 ctlScriptFunc_d8(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 216);
	}
	__int16 ctlScriptFunc_d9(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 217);
	}
	__int16 ctlScriptFunc_da(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 218);
	}
	__int16 ctlScriptFunc_db(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 219);
	}
	__int16 ctlScriptFunc_dc(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 220);
	}
	__int16 ctlScriptFunc_dd(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 221);
	}
	__int16 ctlScriptFunc_de(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 222);
	}
	__int16 ctlScriptFunc_df(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 223);
	}
	__int16 ctlScriptFunc_e0(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 224);
	}
	__int16 ctlScriptFunc_e1(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 225);
	}
	__int16 ctlScriptFunc_e2(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 226);
	}
	__int16 ctlScriptFunc_e3(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 227);
	}
	__int16 ctlScriptFunc_e4(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 228);
	}
	__int16 ctlScriptFunc_e5(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 229);
	}
	__int16 ctlScriptFunc_e6(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 230);
	}
	__int16 ctlScriptFunc_e7(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 231);
	}
	__int16 ctlScriptFunc_e8(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 232);
	}
	__int16 ctlScriptFunc_e9(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 233);
	}
	__int16 ctlScriptFunc_ea(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 234);
	}
	__int16 ctlScriptFunc_eb(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 235);
	}
	__int16 ctlScriptFunc_ec(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 236);
	}
	__int16 ctlScriptFunc_ed(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 237);
	}
	__int16 ctlScriptFunc_ee(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 238);
	}
	__int16 ctlScriptFunc_ef(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 239);
	}
	__int16 ctlScriptFunc_f0(CTL_EngineStruct* ctlEngineStruct) {
		return ctlCall(ctlEngineStruct, 240);
	}
#pragma endregion


	int opLengths[] = {   1, 0, 0, 0, 0, 0, 
		0, 0, 0, 1, 0, 1, 
		1, 1, 1, 1, 1, 1, 
		0, 0, 2, 0, 0, 1, 
		1, 0, 0, 1, 1, 0, 
		2, 2, 2, 2, 1, 2, 
		2, 2, 0, 0, 1, 1, 
		1, 0, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 
		2, 1, 2, 1, 1, 1, 
		2, 0, 0, 0, 1, 0, 
		0, 0, 0, 0, 0, 0, 
		1, 0, 0, 0, 1, 1, 
		1, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 
		0, 0, 1, 1, 1, 1, 
		0, 1, 1, 1, 1, 0, 
		0, 0, 1, 1, 0, 0, 
		0, 0, 1, 1, 1, 1, 
		0, 0, 0, 1, 1, 0, 
		0, 0, 0, 1, 0, 0, 
		1, 3, 2, 1, 0, 0, 
		1, 0, 0, 1, 1, 1, 
		0, 1, 3, 3, 1, 2, 
		0, 1, 2, 0, 3, 1, 
		3, 1, 1, 1, 2, 2, 
		2, 2, 3, 3, 3, 2, 
		1, 2, 1, 0, 0, 1, 
		1, 3, 2, 1, 0, 0, 
		1, 0, 0, 1, 0, 4, 
		1, 1, 1, 1, 1, 1, 
		0, 0, 0, 0, 0, 0, 
		0, 1, 1, 1, 1, 1, 
		0, 1, 0, 2, 1, 1, 
		1, 1, 3, 1, 1, 2, 
		2, 2, 2, 2, 1, 0, 
		1, 2, 0, 2, 0, 2, 
		0, 2, 3, 0, 1, 0, 
		1 };

	std::map<int, char*> createMap() {
		std::map<int, char*> opNames;
		opNames[0] = "init_unit";
		opNames[0x01] = "wait_for_deploy";
		opNames[0x02] = "reset_call_stack";
		opNames[0x03] = "restore_ip";
		opNames[0x04] = "saveip";
		opNames[0x05] = "do";
		opNames[0x06] = "always";
		opNames[0x07] = "while";
		opNames[0x08] = "whilenot";
		opNames[0x09] = "for";
		opNames[0x0a] = "next";
		opNames[0x0b] = "goto";
		opNames[0x0c] = "branch1";
		opNames[0x0d] = "branch2";
		opNames[0x0e] = "branch3";
		opNames[0x0f] = "branch4";
		opNames[0x10] = "branch5";
		opNames[0x11] = "call";
		opNames[0x12] = "return";
		opNames[0x13] = "return_from_event_handler";

		opNames[0x15] = "sleep1";
		opNames[0x16] = "sleep2";
		opNames[0x17] = "cond_skip";
		opNames[0x18] = "set_timer";
		opNames[0x19] = "test_waiting_for_timer";
		opNames[0x1a] = "wait_for_timer";

		opNames[0x1b] = "set_x_i";
		opNames[0x1c] = "add_x_i";
		opNames[0x1d] = "test_x_eq_0";

		opNames[0x1e] = "set_unit_r_i";    
		opNames[0x1f] = "add_unit_r_i";
		opNames[0x20] = "test_unit_r_eq_i";
		opNames[0x21] = "test_unit_r_eq_r";
		opNames[0x22] = "set_unit_r_random1to10";

		opNames[0x23] = "set_global_r_i";
		opNames[0x24] = "add_global_r_i";
		opNames[0x25] = "test_global_r_eq_i";
		opNames[0x28] = "move_to_node";
		opNames[0x29] = "retreat_to_node";

		opNames[0x2a] = "patrol_to_waypoint";
		opNames[0x2b] = "block_movement";
		opNames[0x2c] = "wait_unit_flag1_clear";
		opNames[0x2d] = "wait_unit_flag1_set";
		opNames[0x2e] = "test_unit_flag1";
		opNames[0x2f] = "set_unit_flag1";
		opNames[0x30] = "clear_unit_flag1";

		opNames[0x31] = "wait_unit_flag2_clear";
		opNames[0x32] = "wait_unit_flag2_set";
		opNames[0x33] = "test_unit_flag2";
		opNames[0x34] = "set_unit_flag2";
		opNames[0x35] = "clear_unit_flag2";

		opNames[0x36] = "wait_unit_flag3_clear";
		opNames[0x37] = "wait_unit_flag3_set";
		opNames[0x38] = "test_unit_flag3";

		opNames[0x39] = "set_ctrl_flag";
		opNames[0x3a] = "clear_ctrl_flag";
		opNames[0x3b] = "test_ctrl_flag";

		opNames[0x3d] = "set_event_handler";
		opNames[0x3f] = "set_label";

		opNames[0x41] = "test_label_exists";

		opNames[0x52] = "move_rand_in_radius";

		opNames[0x53] = "init_teleport";
		opNames[0x55] = "teleport_to";

		opNames[0x5a] = "charge";
		opNames[0x5c] = "retreat";

		opNames[0x65] = "hold";
		opNames[0x69] = "send_event_to_this";
		opNames[0x6b] = "raise_event2";
		opNames[0x6d] = "raise_event3";
		opNames[0x6e] = "raise_event4";
		opNames[0x70] = "raise_event5";
		opNames[0x71] = "teleport_to2";
		opNames[0x72] = "get_event";
		opNames[0x73] = "test_more_events";
		opNames[0x74] = "on_event";
		opNames[0x75] = "end_event";
		opNames[0x76] = "iftrue";
		opNames[0x77] = "iffalse";
		opNames[0x78] = "else";
		opNames[0x79] = "endif";

		opNames[0x97] = "init_teleport_spell";

		opNames[0xa2] = "search_and_attack_enemy";
		opNames[0xac] = "search_and_shoot_enemy";

		opNames[0xae] = "play";
		opNames[0xaf] = "play_other_unit";

		opNames[0xb2] = "test_unit_afraid";
		opNames[0xb3] = "test_unit_at_node";
		opNames[0xb5] = "test_unit_at_node2";
		opNames[0xb6] = "send_event_to_labelled";
		opNames[0xb8] = "test_event_from_enemy";
		opNames[0xba] = "test_unit_class";

		opNames[0xc1] = "test_unit_label";

		opNames[0xd8] = "test_other_unit_alive";
		opNames[0xd9] = "test_user_action";       
		opNames[0xda] = "ui_indicate";
		opNames[0xde] = "test_other_unit_at_node";
		opNames[0xdf] = "test_other_unit_attacking";
		opNames[0xe0] = "test_other_unit_flags";

		opNames[0xe2] = "test_other_unit_selected";

		opNames[0xe6] = "test_mapmode";
		opNames[0xe7] = "test_other_unit_status";

		opNames[0xea] = "test_sound_playing";
		opNames[0xed] = "end_mission";
		opNames[0xee] = "test_other_unit_dead";
		return opNames;
	}

	std::map<int, char*> opNames = createMap();

	void applyHooksCTL()
	{
		PBYTE targetFunc = (PBYTE)*(ctlScriptFunc_orig + 0);
		ctlScriptFunc_detour[0] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_00);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 1);
		ctlScriptFunc_detour[1] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_01);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 2);
		ctlScriptFunc_detour[2] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_02);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 3);
		ctlScriptFunc_detour[3] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_03);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 4);
		ctlScriptFunc_detour[4] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_04);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 5);
		ctlScriptFunc_detour[5] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_05);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 6);
		ctlScriptFunc_detour[6] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_06);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 7);
		ctlScriptFunc_detour[7] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_07);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 8);
		ctlScriptFunc_detour[8] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_08);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 9);
		ctlScriptFunc_detour[9] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_09);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 10);
		ctlScriptFunc_detour[10] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_0a);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 11);
		ctlScriptFunc_detour[11] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_0b);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 12);
		ctlScriptFunc_detour[12] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_0c);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 13);
		ctlScriptFunc_detour[13] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_0d);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 14);
		ctlScriptFunc_detour[14] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_0e);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 15);
		ctlScriptFunc_detour[15] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_0f);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 16);
		ctlScriptFunc_detour[16] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_10);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 17);
		ctlScriptFunc_detour[17] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_11);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 18);
		ctlScriptFunc_detour[18] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_12);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 19);
		ctlScriptFunc_detour[19] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_13);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 20);
		ctlScriptFunc_detour[20] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_14);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 21);
		ctlScriptFunc_detour[21] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_15);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 22);
		ctlScriptFunc_detour[22] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_16);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 23);
		ctlScriptFunc_detour[23] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_17);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 24);
		ctlScriptFunc_detour[24] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_18);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 25);
		ctlScriptFunc_detour[25] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_19);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 26);
		ctlScriptFunc_detour[26] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_1a);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 27);
		ctlScriptFunc_detour[27] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_1b);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 28);
		ctlScriptFunc_detour[28] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_1c);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 29);
		ctlScriptFunc_detour[29] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_1d);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 30);
		ctlScriptFunc_detour[30] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_1e);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 31);
		ctlScriptFunc_detour[31] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_1f);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 32);
		ctlScriptFunc_detour[32] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_20);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 33);
		ctlScriptFunc_detour[33] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_21);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 34);
		ctlScriptFunc_detour[34] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_22);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 35);
		ctlScriptFunc_detour[35] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_23);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 36);
		ctlScriptFunc_detour[36] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_24);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 37);
		ctlScriptFunc_detour[37] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_25);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 38);
		ctlScriptFunc_detour[38] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_26);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 39);
		ctlScriptFunc_detour[39] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_27);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 40);
		ctlScriptFunc_detour[40] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_28);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 41);
		ctlScriptFunc_detour[41] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_29);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 42);
		ctlScriptFunc_detour[42] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_2a);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 43);
		ctlScriptFunc_detour[43] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_2b);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 44);
		ctlScriptFunc_detour[44] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_2c);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 45);
		ctlScriptFunc_detour[45] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_2d);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 46);
		ctlScriptFunc_detour[46] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_2e);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 47);
		ctlScriptFunc_detour[47] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_2f);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 48);
		ctlScriptFunc_detour[48] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_30);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 49);
		ctlScriptFunc_detour[49] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_31);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 50);
		ctlScriptFunc_detour[50] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_32);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 51);
		ctlScriptFunc_detour[51] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_33);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 52);
		ctlScriptFunc_detour[52] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_34);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 53);
		ctlScriptFunc_detour[53] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_35);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 54);
		ctlScriptFunc_detour[54] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_36);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 55);
		ctlScriptFunc_detour[55] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_37);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 56);
		ctlScriptFunc_detour[56] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_38);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 57);
		ctlScriptFunc_detour[57] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_39);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 58);
		ctlScriptFunc_detour[58] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_3a);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 59);
		ctlScriptFunc_detour[59] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_3b);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 60);
		ctlScriptFunc_detour[60] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_3c);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 61);
		ctlScriptFunc_detour[61] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_3d);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 62);
		ctlScriptFunc_detour[62] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_3e);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 63);
		ctlScriptFunc_detour[63] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_3f);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 64);
		ctlScriptFunc_detour[64] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_40);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 65);
		ctlScriptFunc_detour[65] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_41);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 66);
		ctlScriptFunc_detour[66] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_42);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 67);
		ctlScriptFunc_detour[67] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_43);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 68);
		ctlScriptFunc_detour[68] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_44);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 69);
		ctlScriptFunc_detour[69] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_45);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 70);
		ctlScriptFunc_detour[70] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_46);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 71);
		ctlScriptFunc_detour[71] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_47);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 72);
		ctlScriptFunc_detour[72] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_48);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 73);
		ctlScriptFunc_detour[73] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_49);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 74);
		ctlScriptFunc_detour[74] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_4a);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 75);
		ctlScriptFunc_detour[75] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_4b);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 76);
		ctlScriptFunc_detour[76] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_4c);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 77);
		ctlScriptFunc_detour[77] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_4d);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 78);
		ctlScriptFunc_detour[78] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_4e);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 79);
		ctlScriptFunc_detour[79] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_4f);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 80);
		ctlScriptFunc_detour[80] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_50);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 81);
		ctlScriptFunc_detour[81] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_51);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 82);
		ctlScriptFunc_detour[82] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_52);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 83);
		ctlScriptFunc_detour[83] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_53);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 84);
		ctlScriptFunc_detour[84] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_54);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 85);
		ctlScriptFunc_detour[85] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_55);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 86);
		ctlScriptFunc_detour[86] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_56);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 87);
		ctlScriptFunc_detour[87] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_57);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 88);
		ctlScriptFunc_detour[88] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_58);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 89);
		ctlScriptFunc_detour[89] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_59);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 90);
		ctlScriptFunc_detour[90] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_5a);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 91);
		ctlScriptFunc_detour[91] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_5b);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 92);
		ctlScriptFunc_detour[92] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_5c);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 93);
		ctlScriptFunc_detour[93] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_5d);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 94);
		ctlScriptFunc_detour[94] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_5e);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 95);
		ctlScriptFunc_detour[95] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_5f);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 96);
		ctlScriptFunc_detour[96] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_60);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 97);
		ctlScriptFunc_detour[97] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_61);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 98);
		ctlScriptFunc_detour[98] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_62);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 99);
		ctlScriptFunc_detour[99] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_63);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 100);
		ctlScriptFunc_detour[100] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_64);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 101);
		ctlScriptFunc_detour[101] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_65);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 102);
		ctlScriptFunc_detour[102] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_66);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 103);
		ctlScriptFunc_detour[103] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_67);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 104);
		ctlScriptFunc_detour[104] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_68);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 105);
		ctlScriptFunc_detour[105] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_69);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 106);
		ctlScriptFunc_detour[106] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_6a);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 107);
		ctlScriptFunc_detour[107] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_6b);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 108);
		ctlScriptFunc_detour[108] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_6c);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 109);
		ctlScriptFunc_detour[109] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_6d);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 110);
		ctlScriptFunc_detour[110] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_6e);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 111);
		ctlScriptFunc_detour[111] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_6f);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 112);
		ctlScriptFunc_detour[112] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_70);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 113);
		ctlScriptFunc_detour[113] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_71);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 114);
		ctlScriptFunc_detour[114] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_72);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 115);
		ctlScriptFunc_detour[115] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_73);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 116);
		ctlScriptFunc_detour[116] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_74);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 117);
		ctlScriptFunc_detour[117] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_75);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 118);
		ctlScriptFunc_detour[118] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_76);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 119);
		ctlScriptFunc_detour[119] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_77);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 120);
		ctlScriptFunc_detour[120] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_78);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 121);
		ctlScriptFunc_detour[121] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_79);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 122);
		ctlScriptFunc_detour[122] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_7a);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 123);
		ctlScriptFunc_detour[123] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_7b);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 124);
		ctlScriptFunc_detour[124] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_7c);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 125);
		ctlScriptFunc_detour[125] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_7d);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 126);
		ctlScriptFunc_detour[126] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_7e);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 127);
		ctlScriptFunc_detour[127] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_7f);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 128);
		ctlScriptFunc_detour[128] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_80);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 129);
		ctlScriptFunc_detour[129] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_81);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 130);
		ctlScriptFunc_detour[130] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_82);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 131);
		ctlScriptFunc_detour[131] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_83);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 132);
		ctlScriptFunc_detour[132] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_84);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 133);
		ctlScriptFunc_detour[133] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_85);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 134);
		ctlScriptFunc_detour[134] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_86);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 135);
		ctlScriptFunc_detour[135] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_87);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 136);
		ctlScriptFunc_detour[136] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_88);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 137);
		ctlScriptFunc_detour[137] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_89);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 138);
		ctlScriptFunc_detour[138] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_8a);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 139);
		ctlScriptFunc_detour[139] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_8b);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 140);
		ctlScriptFunc_detour[140] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_8c);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 141);
		ctlScriptFunc_detour[141] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_8d);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 142);
		ctlScriptFunc_detour[142] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_8e);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 143);
		ctlScriptFunc_detour[143] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_8f);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 144);
		ctlScriptFunc_detour[144] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_90);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 145);
		ctlScriptFunc_detour[145] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_91);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 146);
		ctlScriptFunc_detour[146] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_92);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 147);
		ctlScriptFunc_detour[147] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_93);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 148);
		ctlScriptFunc_detour[148] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_94);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 149);
		ctlScriptFunc_detour[149] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_95);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 150);
		ctlScriptFunc_detour[150] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_96);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 151);
		ctlScriptFunc_detour[151] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_97);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 152);
		ctlScriptFunc_detour[152] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_98);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 153);
		ctlScriptFunc_detour[153] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_99);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 154);
		ctlScriptFunc_detour[154] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_9a);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 155);
		ctlScriptFunc_detour[155] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_9b);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 156);
		ctlScriptFunc_detour[156] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_9c);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 157);
		ctlScriptFunc_detour[157] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_9d);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 158);
		ctlScriptFunc_detour[158] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_9e);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 159);
		ctlScriptFunc_detour[159] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_9f);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 160);
		ctlScriptFunc_detour[160] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_a0);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 161);
		ctlScriptFunc_detour[161] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_a1);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 162);
		ctlScriptFunc_detour[162] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_a2);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 163);
		ctlScriptFunc_detour[163] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_a3);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 164);
		ctlScriptFunc_detour[164] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_a4);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 165);
		ctlScriptFunc_detour[165] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_a5);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 166);
		ctlScriptFunc_detour[166] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_a6);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 167);
		ctlScriptFunc_detour[167] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_a7);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 168);
		ctlScriptFunc_detour[168] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_a8);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 169);
		ctlScriptFunc_detour[169] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_a9);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 170);
		ctlScriptFunc_detour[170] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_aa);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 171);
		ctlScriptFunc_detour[171] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_ab);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 172);
		ctlScriptFunc_detour[172] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_ac);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 173);
		ctlScriptFunc_detour[173] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_ad);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 174);
		ctlScriptFunc_detour[174] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_ae);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 175);
		ctlScriptFunc_detour[175] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_af);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 176);
		ctlScriptFunc_detour[176] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_b0);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 177);
		ctlScriptFunc_detour[177] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_b1);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 178);
		ctlScriptFunc_detour[178] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_b2);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 179);
		ctlScriptFunc_detour[179] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_b3);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 180);
		ctlScriptFunc_detour[180] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_b4);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 181);
		ctlScriptFunc_detour[181] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_b5);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 182);
		ctlScriptFunc_detour[182] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_b6);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 183);
		ctlScriptFunc_detour[183] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_b7);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 184);
		ctlScriptFunc_detour[184] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_b8);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 185);
		ctlScriptFunc_detour[185] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_b9);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 186);
		ctlScriptFunc_detour[186] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_ba);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 187);
		ctlScriptFunc_detour[187] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_bb);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 188);
		ctlScriptFunc_detour[188] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_bc);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 189);
		ctlScriptFunc_detour[189] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_bd);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 190);
		ctlScriptFunc_detour[190] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_be);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 191);
		ctlScriptFunc_detour[191] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_bf);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 192);
		ctlScriptFunc_detour[192] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_c0);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 193);
		ctlScriptFunc_detour[193] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_c1);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 194);
		ctlScriptFunc_detour[194] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_c2);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 195);
		ctlScriptFunc_detour[195] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_c3);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 196);
		ctlScriptFunc_detour[196] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_c4);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 197);
		ctlScriptFunc_detour[197] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_c5);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 198);
		ctlScriptFunc_detour[198] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_c6);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 199);
		ctlScriptFunc_detour[199] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_c7);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 200);
		ctlScriptFunc_detour[200] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_c8);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 201);
		ctlScriptFunc_detour[201] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_c9);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 202);
		ctlScriptFunc_detour[202] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_ca);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 203);
		ctlScriptFunc_detour[203] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_cb);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 204);
		ctlScriptFunc_detour[204] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_cc);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 205);
		ctlScriptFunc_detour[205] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_cd);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 206);
		ctlScriptFunc_detour[206] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_ce);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 207);
		ctlScriptFunc_detour[207] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_cf);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 208);
		ctlScriptFunc_detour[208] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_d0);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 209);
		ctlScriptFunc_detour[209] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_d1);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 210);
		ctlScriptFunc_detour[210] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_d2);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 211);
		ctlScriptFunc_detour[211] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_d3);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 212);
		ctlScriptFunc_detour[212] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_d4);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 213);
		ctlScriptFunc_detour[213] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_d5);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 214);
		ctlScriptFunc_detour[214] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_d6);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 215);
		ctlScriptFunc_detour[215] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_d7);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 216);
		ctlScriptFunc_detour[216] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_d8);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 217);
		ctlScriptFunc_detour[217] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_d9);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 218);
		ctlScriptFunc_detour[218] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_da);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 219);
		ctlScriptFunc_detour[219] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_db);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 220);
		ctlScriptFunc_detour[220] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_dc);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 221);
		ctlScriptFunc_detour[221] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_dd);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 222);
		ctlScriptFunc_detour[222] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_de);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 223);
		ctlScriptFunc_detour[223] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_df);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 224);
		ctlScriptFunc_detour[224] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_e0);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 225);
		ctlScriptFunc_detour[225] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_e1);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 226);
		ctlScriptFunc_detour[226] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_e2);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 227);
		ctlScriptFunc_detour[227] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_e3);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 228);
		ctlScriptFunc_detour[228] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_e4);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 229);
		ctlScriptFunc_detour[229] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_e5);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 230);
		ctlScriptFunc_detour[230] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_e6);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 231);
		ctlScriptFunc_detour[231] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_e7);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 232);
		ctlScriptFunc_detour[232] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_e8);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 233);
		ctlScriptFunc_detour[233] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_e9);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 234);
		ctlScriptFunc_detour[234] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_ea);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 235);
		ctlScriptFunc_detour[235] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_eb);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 236);
		ctlScriptFunc_detour[236] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_ec);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 237);
		ctlScriptFunc_detour[237] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_ed);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 238);
		ctlScriptFunc_detour[238] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_ee);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 239);
		ctlScriptFunc_detour[239] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_ef);
		targetFunc = (PBYTE)*(ctlScriptFunc_orig + 240);
		ctlScriptFunc_detour[240] = (ctlScriptFunc_t)DetourFunction(targetFunc, (PBYTE)ctlScriptFunc_f0);

	}
}
}
