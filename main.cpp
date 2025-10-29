// COMSC-210 | Lab 26 | Mika Aquino
// IDE used: Visual Studio 2022

#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace std::chrono;

const string FILE_NAME = "codes.txt";
const string INSERT_VALUE = "TESTCODE";
const int PRINT_WIDTH = 10;

const int NUM_RUNS = 15;    // The experiment will run 15 times.
const int NUM_RACES = 4;    // The 4 races in an experiment are reading, sorting, inserting, and deleting.
const int NUM_DS = 3;       // The 3 data structures competing in the races are a vector, list, and set.

// Arrays containing the names of the races and data structures for convenient printing.
string races[NUM_RACES] = { "Read", "Sort", "Insert", "Delete" };
string dataStructures[NUM_DS] = { "Vector", "List", "Set" };

// Enums for more readable and convenient indexing in the 3D array.
enum Races { READ, SORT, INSERT, DELETE };
enum DataStructures { VECTOR, LIST, SET };

// Functions for RACE 1: Reading
long long readVector(vector<string>& myVector);
long long readList(list<string>& myList);
long long readSet(set<string>& mySet);

// Functions for RACE 2: Sorting
long long sortVector(vector<string>& myVector);
long long sortList(list<string>& myList);
long long sortSet(set<string>& mySet);

// Functions for RACE 3: Inserting
long long insertVector(vector<string>& myVector);
long long insertList(list<string>& myList);
long long insertSet(set<string>& mySet);

// Functions for RACE 4: Deleting
long long deleteVector(vector<string>& myVector);
long long deleteList(list<string>& myList);
long long deleteSet(set<string>& mySet);

int main() {
    // 3D array to hold the results of each experiment.
    // Each cube slice represents 1 experiment, which has 4 races with 3 competitors.
    long long timeResults[NUM_RUNS][NUM_RACES][NUM_DS];

    // 2D array to hold the final accumulated the results of each experiment.
    long long accResults[NUM_RACES][NUM_DS] = {0};

    // Loop to run 15 experiments.
    // Each experiment has 4 races.
    for (int i = 0; i < NUM_RUNS; ++i) {
        // Data structures to compete in the races
        vector<string> myVector;
        list<string> myList;
        set<string> mySet;

        // Ensure that the data structures are clear at the start of each experiment.
        myVector.clear();
        myList.clear();
        mySet.clear();

        // RACE 1: Reading
        timeResults[i][READ][VECTOR] = readVector(myVector);
        timeResults[i][READ][LIST] = readList(myList);
        timeResults[i][READ][SET] = readSet(mySet);

        // RACE 2: Sorting
        timeResults[i][SORT][VECTOR] = sortVector(myVector);
        timeResults[i][SORT][LIST] = sortList(myList);
        timeResults[i][SORT][SET] = sortSet(mySet);

        // RACE 3: Inserting
        timeResults[i][INSERT][VECTOR] = insertVector(myVector);
        timeResults[i][INSERT][LIST] = insertList(myList);
        timeResults[i][INSERT][SET] = insertSet(mySet);

        // RACE 4: Deleting
        timeResults[i][DELETE][VECTOR] = deleteVector(myVector);
        timeResults[i][DELETE][LIST] = deleteList(myList);
        timeResults[i][DELETE][SET] = deleteSet(mySet);
    }

    // Now we must accumulate the results of each experiment.
    // To do this, we iterate through the 3D array:
    for (int i = 0; i < NUM_RUNS; ++i) {            // Dimension 1: number of times the experiment ran
        for (int j = 0; j < NUM_RACES; ++j) {       // Dimension 2: number of races
            for (int k = 0; k < NUM_DS; ++k) {      // Dimension 3: number of data structures
                // Get the time results of a particular operation
                // and sum it in the accumulator.
                accResults[j][k] += timeResults[i][j][k];
            }
        }
    }

    // Print the header.
    cout << "Number of simulations: " << NUM_RUNS << "\n";
    cout << setw(PRINT_WIDTH) << "Operation";
    for (int i = 0; i < NUM_DS; ++i) {
        cout << setw(PRINT_WIDTH) << dataStructures[i];
    }
    cout << "\n";

    // Output the results of each race.
    for (int i = 0; i < NUM_RACES; ++i) {
        // Output the operation name
        cout << setw(PRINT_WIDTH) << races[i];

        // Output the results for vector
        cout << setw(PRINT_WIDTH) << accResults[i][VECTOR] / NUM_RUNS;
        // Output the results for list
        cout << setw(PRINT_WIDTH) << accResults[i][LIST] / NUM_RUNS;
        // Output the results for set
        cout << setw(PRINT_WIDTH) << (i == SORT ? "0" : accResults[i][SET] / NUM_RUNS);
        cout << "\n";
    }

    return 0;
}

// Function to return the time it takes to read elements from a file into a vector.
// Args:    a vector
// Returns: time in microseconds
long long readVector(vector<string>& myVector) {
    // Open the file
    ifstream file(FILE_NAME);
    string line;
    if (!file) {
        cout << "ERROR: Could not open " << FILE_NAME << ".\n";
        return 1;
    }

    // Begin timing
    auto start = high_resolution_clock::now();

    // Read file
    while (getline(file, line)) {
        myVector.push_back(line);
    }

    // End timing
    auto end = high_resolution_clock::now();

    // Close the file
    file.close();

    // Return time result
    return (duration_cast<microseconds>(end - start)).count();
}

// Function to return the time it takes to read elements from a file into a list.
// Args:    a list
// Returns: time in microseconds
long long readList(list<string>& myList) {
    // Open the file
    ifstream file(FILE_NAME);
    string line;
    if (!file) {
        cout << "ERROR: Could not open " << FILE_NAME << ".\n";
        return 1;
    }

    // Begin timing
    auto start = high_resolution_clock::now();

    // Read file
    while (getline(file, line)) {
        myList.push_back(line);
    }

    // End timing
    auto end = high_resolution_clock::now();

    // Close the file
    file.close();

    // Return time result
    return (duration_cast<microseconds>(end - start)).count();
}

// Function to return the time it takes to read elements from a file into a set.
// Args:    a set
// Returns: time in microseconds
long long readSet(set<string>& mySet) {
    // Open the file
    ifstream file(FILE_NAME);
    string line;
    if (!file) {
        cout << "ERROR: Could not open " << FILE_NAME << ".\n";
        return 1;
    }

    // Begin timing
    auto start = high_resolution_clock::now();

    // Read file
    while (getline(file, line)) {
        mySet.insert(line);
    }

    // End timing
    auto end = high_resolution_clock::now();

    // Close the file
    file.close();

    // Return time result
    return (duration_cast<microseconds>(end - start)).count();
}

// Function to return the time it takes to sort a vector.
// Args:    a vector
// Returns: time in microseconds
long long sortVector(vector<string>& myVector) {
    auto start = high_resolution_clock::now();                  // Begin timing
    sort(myVector.begin(), myVector.end());                     // Sort vector
    auto end = high_resolution_clock::now();                    // End timing
    return (duration_cast<microseconds>(end - start)).count();  // Return time result
}

// Function to return the time it takes to sort a list.
// Args:    a list
// Returns: time in microseconds
long long sortList(list<string>& myList) {
    auto start = high_resolution_clock::now();                  // Begin timing
    myList.sort();                                              // Sort list
    auto end = high_resolution_clock::now();                    // End timing
    return (duration_cast<microseconds>(end - start)).count();  // Return time result
}

// Function to return the time it takes to sort a set.
// Args:    a set
// Returns: -1 (because a set is already sorted)
long long sortSet(set<string>& mySet) {
    return -1;
}

// Function to return the time it takes insert an element in the middle of a vector.
// Args:    a vector
// Returns: time in microseconds
long long insertVector(vector<string>& myVector) {
    auto start = high_resolution_clock::now();                  // Begin timing
    auto middleIt = myVector.begin() + (myVector.size() / 2);   // Create an iterator in the middle
    myVector.insert(middleIt, INSERT_VALUE);                    // Insert a value in the middle
    auto end = high_resolution_clock::now();                    // End timing
    return (duration_cast<microseconds>(end - start)).count();  // Return time result
}

// Function to return the time it takes insert an element in the middle of a list.
// Args:    a list
// Returns: time in microseconds
long long insertList(list<string>& myList) {
    auto start = high_resolution_clock::now();                  // Begin timing
    auto middleIt = myList.begin();                             // Create an iterator
    advance(middleIt, (myList.size() / 2));                     // Advance the iterator to the middle
    myList.insert(middleIt, INSERT_VALUE);                      // Insert a value in the middle
    auto end = high_resolution_clock::now();                    // End timing
    return (duration_cast<microseconds>(end - start)).count();  // Return time result
}

// Function to return the time it takes insert an element in a set.
// Args:    a set
// Returns: time in microseconds
long long insertSet(set<string>& mySet) {
    auto start = high_resolution_clock::now();                  // Begin timing
    mySet.insert(INSERT_VALUE);                                 // Insert a value
    auto end = high_resolution_clock::now();                    // End timing
    return (duration_cast<microseconds>(end - start)).count();  // Return time result
}

// Function to return the time it takes delete an element in the middle of a vector.
// Args:    a vector
// Returns: time in microseconds
long long deleteVector(vector<string>& myVector) {
    auto start = high_resolution_clock::now();                  // Begin timing
    auto middleIt = myVector.begin() + (myVector.size() / 2);   // Create an iterator in the middle
    myVector.erase(middleIt);                                   // Delete a value in the middle
    auto end = high_resolution_clock::now();                    // End timing
    return (duration_cast<microseconds>(end - start)).count();  // Return time result
}

// Function to return the time it takes delete an element in the middle of a list.
// Args:    a list
// Returns: time in microseconds
long long deleteList(list<string>& myList) {
    auto start = high_resolution_clock::now();                  // Begin timing
    auto middleIt = myList.begin();                             // Create an iterator
    advance(middleIt, (myList.size() / 2));                     // Advance the iterator to the middle
    myList.erase(middleIt);                                     // Delete a value in the middle
    auto end = high_resolution_clock::now();                    // End timing
    return (duration_cast<microseconds>(end - start)).count();  // Return time result
}

// Function to return the time it takes delete an element in the middle of a set.
// Args:    a set
// Returns: time in microseconds
long long deleteSet(set<string>& mySet) {
    auto start = high_resolution_clock::now();                  // Begin timing
    auto middleIt = mySet.begin();                              // Create an iterator
    advance(middleIt, (mySet.size() / 2));                      // Advance the iterator to the middle
    mySet.erase(middleIt);                                      // Delete a value in the middle
    auto end = high_resolution_clock::now();                    // End timing
    return (duration_cast<microseconds>(end - start)).count();  // Return time result
}