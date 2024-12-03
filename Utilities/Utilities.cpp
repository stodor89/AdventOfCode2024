#include "Utilities.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

bool stringToInt(const string& str, size_t pos, int& out, size_t& length) {
    // Avoid dynamic allocations during substr
    constexpr size_t MAX_INT_LENGTH = 11;

    try {
        out = stoi(str.substr(pos, MAX_INT_LENGTH), &length);
    }
    catch (...) {
        return false;
    }
    return true;
}

string convertToString(const vector<int>& vec, const string& delimiter) {
    if (vec.empty()) {
        return "";
    }

    stringstream ss(to_string(vec[0]));

    for (int i = 1; i < vec.size(); i++) {
        ss << delimiter << vec[i];
    }

    return ss.str();
}

bool readRowsFromFile(const string& filename, vector<vector<int>>& out) {
    ifstream file(filename);
    if (!file) {
        cout << "Could not open " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int n;
        vector<int> nums;
        while (iss >> n) {
            nums.push_back(n);
        }
        out.push_back(nums);
    }
    return true;
}

bool readColumnsFromFile(const string& filename, vector<vector<int>>& out) {
    ifstream file(filename);
    if (!file) {
        cout << "Could not open " << filename << endl;
        return false;
    }

    // First line: create column vectors and add first numbers
    string line;
    if (!getline(file, line)) {
        return false;
    }
    istringstream iss(line);
    int n;
    while (iss >> n) {
        vector<int> column;
        column.push_back(n);
        out.push_back(column);
    }

    // Next lines: add remaining numbers
    while (getline(file, line)) {
        iss = istringstream(line);
        for (int i = 0; (i < out.size()) && (iss >> n); i++) {
            out[i].push_back(n);
        }
    }

    return true;
}

bool readStringFromFile(const std::string& filename, std::string& out) {
    ifstream file(filename);
    if (!file) {
        cout << "Could not open " << filename << endl;
        return false;
    }

    out = string(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
    return true;
}
