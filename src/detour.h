#pragma once

#include <windows.h>

namespace darkomen {
namespace detour {
	void hookFunc(void* hookFunc, int addr);

	void init();
	void trace(char* fmt, ...);

	extern bool traceEnabled;
	extern FILE* traceFile;
	extern char darkomenExePath[MAX_PATH + 1];
}
}
