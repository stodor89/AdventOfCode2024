#pragma once

#include <string>
#include <vector>

// Scalars
bool stringToInt(const std::string& str, size_t pos, int& out, size_t& length);

// Collections
std::string convertToString(const std::vector<int>& vec, const std::string& delimiter = " ");

// Files
bool readRowsFromFile(const std::string& filename, std::vector<std::vector<int>>& out);
bool readColumnsFromFile(const std::string& filename, std::vector<std::vector<int>>& out);
bool readStringFromFile(const std::string& filename, std::string& out);