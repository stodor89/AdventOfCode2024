#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "Utilities.h"

using namespace std;

constexpr int SAFE_REPORT_MAX_DELTA = 3;
constexpr int DIRECTION_UP = 1;
constexpr int DIRECTION_DOWN = -1;

// Helpers
void printReport(const vector<int>& report, bool safe);
void testIsSafelyChanging();

bool isSafeChange(int val1, int val2, int safetyMargin, int diffMult) {
    const int diff = (val2 - val1) * diffMult;
    return diff > 0 && diff <= safetyMargin;
}

bool isSafelyChanging(const vector<int>& report, int safetyMargin, int direction, bool allowBadValue) {
    for (int i = 1; i < report.size(); i++) {
        if (!isSafeChange(report[i - 1], report[i], safetyMargin, direction)) {
            if (!allowBadValue) {
                return false;
            }
            // allow current (bad) value if prev-to-next is within safety margin
            if ((i == report.size() - 1) || isSafeChange(report[i - 1], report[i + 1], safetyMargin, direction)) {
                allowBadValue = false;
                i++;
                continue;
            }
            // special case: allow first (bad) if current-to-next is within safety margin  
            if ((i == 1) && isSafeChange(report[i], report[i + 1], safetyMargin, direction)) {
                allowBadValue = false;
                continue;
            }
            return false;
        }
    }

    return true;
}

int countSafeReports(const vector<vector<int>>& reports, int safetyMargin, bool allowBadValue) {
    int safeReportsCount = 0;
    for (auto&& report : reports) {
        const bool safe = isSafelyChanging(report, safetyMargin, DIRECTION_UP, allowBadValue)
            || isSafelyChanging(report, safetyMargin, DIRECTION_DOWN, allowBadValue);
        //printReport(report, safe);
        safeReportsCount += safe;
    }


    return safeReportsCount;
}

int main(int argc, char* argv[]) {
    //testIsSafelyChanging();

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    vector<vector<int>> reports;
    readRowsFromFile(argv[1], reports);

    cout << "safe reports (0 bad levels): " << countSafeReports(reports, SAFE_REPORT_MAX_DELTA, false)
        << endl
        << "safe reports (0 or 1 bad levels): " << countSafeReports(reports, SAFE_REPORT_MAX_DELTA, true)
        << endl;
}



void printReport(const vector<int>& report, bool safe) {
    string str;

    str += safe ? "safe:  " : "unsafe:";
    str += convertToString(report);

    cout << str << endl;
}

void testIsSafelyChanging() {
    auto checkResult = [](const vector<int>& report, bool expected, int direction) {
        bool actual = isSafelyChanging(report, SAFE_REPORT_MAX_DELTA, direction, true);
        if (actual != expected) {
            cout << "Test failed: " << convertToString(report) << " should be "
                << (expected ? "safe" : "unsafe") << endl;
        }
        };

    checkResult({ 86, 87, 88, 90, 92, 93, 93, 90 }, false, DIRECTION_UP);
    checkResult({ 75, 79, 80, 82 }, true, DIRECTION_UP);
    checkResult({ 43, 45, 46, 49, 51, 58, 61 }, false, DIRECTION_UP);
}