#include "util.h"

#include <windows.h>
#include <detour.h>
#include <cassert>
#include <io.h>
#include <algorithm>
#include "functions.h"

// Simple wrapper around the CreateFile API that calls the non-hooked version of CreateFile
// and converts it to a FILE handle because I don't like the WinApi ;)
FILE* openFile(const std::string& filename, const std::string& mode) {
	HANDLE handle = NULL;
	if (mode == "r") {
		handle = createFile_orig(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	else if (mode == "w") {
		handle = createFile_orig(filename.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	else {
		assert(false && "Invalid open mode");
	}

	if (handle == INVALID_HANDLE_VALUE) {
		return NULL;
	}

	int fd = _open_osfhandle(reinterpret_cast<intptr_t>(handle), 0);
	return _fdopen(fd, mode.c_str());
}

std::string getPathOfFile(const std::string& filename) {
	size_t pos = filename.find_last_of("\\/");
	if (pos == std::string::npos) {
		return "";
	}

	return filename.substr(0, filename.find_last_of("\\/"));
}

std::string toLowerCase(const std::string& str) {
	std::string low = str;
	std::transform(low.begin(), low.end(), low.begin(), ::tolower);
	return low;
}

bool startsWith(const std::string& str, const std::string& substr) {
	return str.find(substr) == 0;
}
