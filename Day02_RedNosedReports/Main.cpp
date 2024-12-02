#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "Utilities.h"

using namespace std;

constexpr int SAFE_REPORT_MAX_DELTA = 3; // not great, not terrible
constexpr int DIRECTION_UP = 1;
constexpr int DIRECTION_DOWN = -1;

// Helpers
void printReport(const vector<int>& report, bool safe);
void testIsSafeReport();

bool isDeltaSafe(int val1, int val2, int direction) {
    const int diff = (val2 - val1) * direction;
    return diff > 0 && diff <= SAFE_REPORT_MAX_DELTA;
}

bool isReportSafe(const vector<int>& report, int direction, bool allowBadValue) {
    for (int i = 1; i < report.size(); i++) {
        if (!isDeltaSafe(report[i - 1], report[i], direction)) {
            if (!allowBadValue) {
                return false;
            }

            // allow current (bad) value if prev-to-next is within safety margin
            if ((i == report.size() - 1) || isDeltaSafe(report[i - 1], report[i + 1], direction)) {
                allowBadValue = false;
                i++;
                continue;
            }

            // special case: allow #0 (bad) if #1-to-#2 is within safety margin
            if ((i == 1) && isDeltaSafe(report[1], report[2], direction)) {
                allowBadValue = false;
                continue;
            }

            return false;
        }
    }

    return true;
}

int countSafeReports(const vector<vector<int>>& reports, bool allowBadValue) {
    int safeReportsCount = 0;
    for (auto&& report : reports) {
        const bool safe = isReportSafe(report, DIRECTION_UP, allowBadValue)
            || isReportSafe(report, DIRECTION_DOWN, allowBadValue);
        //printReport(report, safe);
        safeReportsCount += safe;
    }


    return safeReportsCount;
}

int main(int argc, char* argv[]) {
    //testIsSafeReport();

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    vector<vector<int>> reports;
    readRowsFromFile(argv[1], reports);

    cout << "safe reports (0 bad levels): " << countSafeReports(reports, false) << endl
        << "safe reports (0 or 1 bad levels): " << countSafeReports(reports, true) << endl;
}



void printReport(const vector<int>& report, bool safe) {
    string str;

    str += safe ? "safe:  " : "unsafe:";
    str += convertToString(report);

    cout << str << endl;
}

void testIsSafeReport() {
    auto checkResult = [](const vector<int>& report, int direction, bool expected) {
        bool actual = isReportSafe(report, direction, true);
        if (actual != expected) {
            cout << "Test failed: " << convertToString(report) << " should be "
                << (expected ? "safe" : "unsafe") << endl;
        }};

    checkResult({ 86, 87, 88, 90, 92, 93, 93, 90 }, DIRECTION_UP, false);
    checkResult({ 75, 79, 80, 82 }, DIRECTION_UP, true);
    checkResult({ 43, 45, 46, 49, 51, 58, 61 }, DIRECTION_UP, false);
}