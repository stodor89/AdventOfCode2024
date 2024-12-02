#pragma once

#include <string>
#include <vector>

std::string convertToString(const std::vector<int>& vec, const std::string& delimiter = " ");

bool readRowsFromFile(const std::string& filename, std::vector<std::vector<int>>& out);
bool readColumnsFromFile(const std::string& filename, std::vector<std::vector<int>>& out);