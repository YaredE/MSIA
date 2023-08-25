#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int findMinimumLengthSubarrayHelper(const vector<int> &arr, int k, int start) {

    unordered_set<int> uniqueElements;
    int minLength = INT_MAX;
    for (int inx=start; inx < arr.size(); inx++){
        uniqueElements.insert(arr[inx]);
        if (uniqueElements.size() == k) {
            int newSize = inx - start + 1;
            minLength = min(minLength, newSize);
        }
    }
    return minLength;
}


int findMinimumLengthSubarrayBruteForce(const vector<int> &arr, int k) {

    int minimumLength = INT_MAX;
    unordered_map<int, int> frequencies;

    for (int inx=0; inx < arr.size(); inx++){
        frequencies[arr[inx]]++;
    }

    if (frequencies.size() < k) { return 0; }

    for (int inx=0; inx < arr.size(); inx++){
        minimumLength = min(minimumLength, findMinimumLengthSubarrayHelper(arr, k, inx));
    }
    return minimumLength;
}


int findMinimumLengthSubarrayOptimalSolution(const vector<int> &arr, int k) {
    int n = arr.size();
    int uniqueCount = 0;
    unordered_map<int, int> frequency;
    int minLength = n + 1;
    for (int left = 0, right = 0; right < n; right++) {
        if (frequency[arr[right]] == 0) {
            uniqueCount++;
        }
        frequency[arr[right]]++;

        while (uniqueCount == k) {
            minLength = min(minLength, right - left + 1);

            frequency[arr[left]]--;
            if (frequency[arr[left]] == 0) {
                uniqueCount--;
            }

            left++;
        }
    }
    return (minLength == n + 1) ? 0 : minLength;
}

int main() {
    vector<int> arr;
    arr.push_back(3);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(3);
    arr.push_back(1);
    arr.push_back(3);
    int k = 3;

    int result = findMinimumLengthSubarrayOptimalSolution(arr, k);
    cout << "Minimum Length sub array with " << k << " unique integers: " << result << endl;

    int result2 = findMinimumLengthSubarrayBruteForce(arr, k);
    cout << "Minimum Length sub array with " << k << " unique integers: " << result2 << endl;

    return 0;
}
