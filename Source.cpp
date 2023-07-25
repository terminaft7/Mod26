#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to calculate the sum of numbers in a given array
int calculateSum(const std::vector<int>& arr) {
    int sum = 0;
    for (int num : arr) {
        sum += num;
    }
    return sum;
}

int main() {

    int initialArraySize, numSplits;

    // Ask the user to input the size of the initial array
    cout << "Enter the size of the initial array: ";
    cin >> initialArraySize;

    // Ask the user to input the number of splits
    cout << "Enter the number of separate arrays to create: ";
    cin >> numSplits;

    // Calculate the size of each split array
    int splitSize = initialArraySize / numSplits;
    int remainder = initialArraySize % numSplits; // In case the array cannot be evenly split

    // Create the initial array
    vector<int> initialArray(initialArraySize);

    // Fill the initial array with elements (You can use user input or any other method here)
    for (int i = 0; i < initialArraySize; ++i) {
        initialArray[i] = rand();
    }

    // Create a vector to store the split arrays
    vector<vector<int>> splitArrays;

    // Create the split arrays and copy elements from the initial array
    int startIndex = 0;
    for (int i = 0; i < numSplits; ++i) {
        // Calculate the size of this split
        int currentSplitSize = splitSize;
        if (remainder > 0) {
            currentSplitSize++;
            remainder--;
        }

        // Create the split array
        vector<int> splitArray(currentSplitSize);

        // Copy elements from the initial array to this split
        for (int j = 0; j < currentSplitSize; ++j) {
            splitArray[j] = initialArray[startIndex + j];
        }

        // Add this split array to the vector of split arrays
        splitArrays.push_back(splitArray);

        startIndex += currentSplitSize;
    }

    /* Display the separate arrays
    cout << "Separate arrays:\n";
    for (size_t i = 0; i < splitArrays.size(); ++i) {
        cout << "Array " << i + 1 << ": ";
        for (size_t j = 0; j < splitArrays[i].size(); ++j) {
            cout << splitArrays[i][j] << " ";
        }
        cout << std::endl;
    }*/


    // Start of measuring the required time for calculation
    auto start = high_resolution_clock::now();

    // Calculate the sum of each array using separate threads
    vector<int> arraySums(numSplits);
    vector<std::thread> threads;

    for (int i = 0; i < numSplits; ++i) {
        threads.emplace_back([i, &splitArrays, &arraySums]() {
            arraySums[i] = calculateSum(splitArrays[i]);
            });
    }

    // Wait for all threads to finish
    for (thread& t : threads) {
        t.join();
    }

    // Calculate the sum of all the sums
    int totalSum = 0;
    for (int sum : arraySums) {
        totalSum += sum;
    }

    /* Display the sums of each arrayand the total sum
    cout << "Sums of each array:\n";
    for (int i = 0; i < numSplits; ++i) {
        cout << "Array " << i + 1 << " sum: " << arraySums[i] << std::endl;
    }
    cout << "Total sum of all arrays: " << totalSum << std::endl;*/
    // End of measuring the required time for calculation
    auto stop = high_resolution_clock::now();

    // Calculate and display the required time for calculation
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "It took " << duration.count()/1000 << " milliseconds for the program to complete" << endl;
    return 0;
}
