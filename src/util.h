#pragma once

#include <string>

FILE* openFile(const std::string& filename, const std::string& mode);

std::string getPathOfFile(const std::string& filename);

std::string toLowerCase(const std::string& str);

bool startsWith(const std::string& str, const std::string& substr);
