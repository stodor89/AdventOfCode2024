#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

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
        return 0;
    }

    vector<int> locations1, locations2;
    {
        ifstream file(argv[1]);
        if (!file) {
            cout << "Could not open " << argv[1] << endl;
            return 1;
        }

        int loc1, loc2;
        while (file >> loc1 >> loc2) {
            locations1.push_back(loc1);
            locations2.push_back(loc2);
        }
    }

    sort(locations1.begin(), locations1.end());
    sort(locations2.begin(), locations2.end());

    cout << "total distance: " << totalDistance(locations1, locations2) << endl
        << "similarity score: " << similarityScore(locations1, locations2) << endl;
}