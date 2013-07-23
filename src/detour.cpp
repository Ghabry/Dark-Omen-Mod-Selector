#include <cstdarg>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <string>
#include "detour.h"
#include <windows.h>

namespace darkomen {
namespace detour {
	bool traceEnabled = false;
	FILE* traceFile = NULL;
	char darkomenExePath[MAX_PATH + 1] = {0};

	void hookFunc(void* hookFunc, int addr)
	{
		unsigned char cal = 0xE9;
		int hookAddr = (int)hookFunc - addr - 5;
		memcpy((void*)addr, (void*)&cal, 1);
		memcpy((void*)(addr+1), (void*)&hookAddr, 4);
	}

	void init()
	{
		GetModuleFileNameA(NULL, darkomenExePath, MAX_PATH);
		if (strrchr(darkomenExePath, '\\') != NULL)
		{
			strrchr(darkomenExePath, '\\')[0] = '\0';
			std::string file(darkomenExePath);
			file += "\\trace.txt";
			if (GetFileAttributesA(file.c_str()) == -1)
			{
				file += ".txt";
				if (GetFileAttributesA(file.c_str()) == -1)
				{
					return;
				}
				MessageBoxA(NULL, "trace.txt was not found. But I found trace.txt.txt instead. File extensions are probably hidden, you can fix this in the Windows Explorer folder options.", "Dark Patch", 0x30L);
			}
			traceFile = fopen(file.c_str(), "w");
			if (traceFile)
			{
				traceEnabled = true;
				trace("Dark Patch 2012-05-20");
			}
		}
	}

	void trace(char* fmt, ...)
	{
		if (traceEnabled)
		{
			va_list args;
			va_start(args, fmt);

			char str[512];
			// Get current time
			time_t t = time(NULL);
			struct tm * zeit = gmtime(&t);
			sprintf(str, "[%02d:%02d:%02d] ",
				zeit->tm_hour, zeit->tm_min, zeit->tm_sec);
			std::string out(str);

			// Arguments
			vsprintf(str, fmt, args);
			out += str;

			// Write to file
			fprintf(traceFile, "%s\n", out.c_str());

			va_end(args);
		}
	}
}
}