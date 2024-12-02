#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include "Utilities.h"

using namespace std;

int totalDistance(const vector<int>& sortedNums1, const vector<int>& sortedNums2) {
    int totalDistance = 0;
    for (int i = 0; i < sortedNums1.size(); i++) {
        totalDistance += abs(sortedNums1[i] - sortedNums2[i]);
    }

    return totalDistance;
}

int similarityScore(vector<int>& sortedNums1, vector<int> sortedNums2) {
    int i = 0, j = 0, similarityScore = 0;
    while (i < sortedNums1.size() && j < sortedNums2.size()) {
        const int value = sortedNums1[i];
        for (; j < sortedNums2.size() && sortedNums2[j] < value; j++) {
        }

        int nums1Occurrences = 0;
        for (; i < sortedNums1.size() && sortedNums1[i] == value; i++) {
            nums1Occurrences++;
        }

        int nums2Occurrences = 0;
        for (; j < sortedNums2.size() && sortedNums2[j] == value; j++) {
            nums2Occurrences++;
        }

        similarityScore += value * nums1Occurrences * nums2Occurrences;
    }

    return similarityScore;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    vector<vector<int>> locations;
    readColumnsFromFile(argv[1], locations);
    if (locations.size() != 2) {
        cout << "File " << argv[1] << "should contain 2 columns of numbers." << endl;
        return 1;
    }

    for (auto&& vec : locations) {
        sort(vec.begin(), vec.end());
    }

    cout << "total distance: " << totalDistance(locations[0], locations[1]) << endl
        << "similarity score: " << similarityScore(locations[0], locations[1]) << endl;
}