#include <iostream>
#include <string>
using namespace std;

// ===================== DATA STRUCTURES =====================
struct Driver {
    int id;
    string name;
    double distance;
    double rating;

    Driver() : id(0), name(""), distance(0.0), rating(0.0) {}
    Driver(int i, string n, double d, double r)
        : id(i), name(n), distance(d), rating(r) {}
};

// ===================== DISPLAY FUNCTION =====================
void displayDrivers(Driver drivers[], int size) {
    cout << "\n----------------------------------------\n";
    cout << "ID\tName\tDistance\tRating\n";
    cout << "----------------------------------------\n";
    for (int i = 0; i < size; i++) {
        cout << drivers[i].id << "\t"
             << drivers[i].name << "\t"
             << drivers[i].distance << " km\t\t"
             << drivers[i].rating << "\n";
    }
    cout << "----------------------------------------\n";
}

// ===================== BUBBLE SORT (Closest First) =====================
void bubbleSort(Driver drivers[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (drivers[j].distance > drivers[j + 1].distance) {
                // MANUAL SWAP (NO STL swap)
                Driver temp = drivers[j];
                drivers[j] = drivers[j + 1];
                drivers[j + 1] = temp;
            }
        }
    }
    cout << "\n[BUBBLE SORT] Sorted by Distance (Closest First)\n";
}

// ===================== SELECTION SORT (Closest First) =====================
void selectionSort(Driver drivers[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (drivers[j].distance < drivers[minIndex].distance) {
                minIndex = j;
            }
        }
        // MANUAL SWAP (NO STL swap)
        Driver temp = drivers[i];
        drivers[i] = drivers[minIndex];
        drivers[minIndex] = temp;
    }
    cout << "\n[SELECTION SORT] Sorted by Distance (Closest First)\n";
}

// ===================== INSERTION SORT (Highest Rating First) =====================
void insertionSortByRating(Driver drivers[], int size) {
    for (int i = 1; i < size; i++) {
        Driver key = drivers[i];
        int j = i - 1;
        while (j >= 0 && drivers[j].rating < key.rating) {
            drivers[j + 1] = drivers[j];
            j = j - 1;
        }
        drivers[j + 1] = key;
    }
    cout << "\n[INSERTION SORT] Sorted by Rating (Highest First)\n";
}

// ===================== BINARY SEARCH =====================
int binarySearch(Driver drivers[], int size, int targetId) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (drivers[mid].id == targetId) {
            return mid;
        }
        if (drivers[mid].id < targetId) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// ===================== MAIN =====================
int main() {
    cout << "===== TASK 2: SORTING & SEARCHING ALGORITHMS (ENDRINAL) =====\n";

    const int NUM_DRIVERS = 5;

    // Original Driver Data (Available Drivers for Ride‑Sharing)
    Driver original[NUM_DRIVERS] = {
        Driver(103, "Marco", 2.5, 4.7),
        Driver(101, "Sarah", 1.2, 4.9),
        Driver(105, "Alex", 3.8, 4.5),
        Driver(102, "Jess", 0.8, 4.8),
        Driver(104, "Mark", 2.1, 4.6)
    };

    // --- BUBBLE SORT ---
    cout << "\n=== 1. BUBBLE SORT ===" << endl;
    Driver bubbleArr[NUM_DRIVERS];
    for (int i = 0; i < NUM_DRIVERS; i++) bubbleArr[i] = original[i];
    displayDrivers(bubbleArr, NUM_DRIVERS);
    bubbleSort(bubbleArr, NUM_DRIVERS);
    displayDrivers(bubbleArr, NUM_DRIVERS);

    // Get closest driver after Bubble Sort
    int closestDriverID = bubbleArr[0].id;
    cout << "\nENDRINAL GREEDY RESULT (Bubble Sort): Closest Driver = " << bubbleArr[0].name << " (ID: " << closestDriverID << ")" << endl;

    // --- SELECTION SORT ---
    cout << "\n=== 2. SELECTION SORT ===" << endl;
    Driver selectionArr[NUM_DRIVERS];
    for (int i = 0; i < NUM_DRIVERS; i++) selectionArr[i] = original[i];
    displayDrivers(selectionArr, NUM_DRIVERS);
    selectionSort(selectionArr, NUM_DRIVERS);
    displayDrivers(selectionArr, NUM_DRIVERS);

    // --- INSERTION SORT ---
    cout << "\n=== 3. INSERTION SORT ===" << endl;
    Driver insertionArr[NUM_DRIVERS];
    for (int i = 0; i < NUM_DRIVERS; i++) insertionArr[i] = original[i];
    displayDrivers(insertionArr, NUM_DRIVERS);
    insertionSortByRating(insertionArr, NUM_DRIVERS);
    displayDrivers(insertionArr, NUM_DRIVERS);

    // --- BINARY SEARCH (Verify the CLOSEST Driver for ENDRINAL) ---
    cout << "\n=== 4. BINARY SEARCH (Verify Assigned Closest Driver) ===" << endl;
    Driver searchArr[NUM_DRIVERS];
    for (int i = 0; i < NUM_DRIVERS; i++) searchArr[i] = original[i];

    // Sort array BY ID (REQUIRED for Binary Search) — MANUAL SORT NO swap()
    for (int i = 0; i < NUM_DRIVERS - 1; i++) {
        for (int j = 0; j < NUM_DRIVERS - i - 1; j++) {
            if (searchArr[j].id > searchArr[j + 1].id) {
                // MANUAL SWAP
                Driver temp = searchArr[j];
                searchArr[j] = searchArr[j + 1];
                searchArr[j + 1] = temp;
            }
        }
    }
    cout << "\nSorted by ID for Binary Search:\n";
    displayDrivers(searchArr, NUM_DRIVERS);

    // Auto‑search the closest driver
    cout << "\nBinary Search for our assigned closest driver ID: " << closestDriverID << endl;
    int result = binarySearch(searchArr, NUM_DRIVERS, closestDriverID);
    if (result != -1) {
        cout << "VERIFIED — Driver FOUND at index " << result << ":\n";
        cout << "Name: " << searchArr[result].name
             << " | Distance: " << searchArr[result].distance << "km"
             << " | Rating: " << searchArr[result].rating << "\n";
    } else {
        cout << "NOT FOUND\n";
    }

    // Optional: Let user search another ID
    int searchID;
    cout << "\nEnter additional Driver ID to search (optional): ";
    cin >> searchID;
    result = binarySearch(searchArr, NUM_DRIVERS, searchID);
    if (result != -1) {
        cout << "FOUND at index " << result << ":\n";
        cout << "Name: " << searchArr[result].name
             << " | Distance: " << searchArr[result].distance << "km"
             << " | Rating: " << searchArr[result].rating << "\n";
    } else {
        cout << "NOT FOUND\n";
    }

    cout << "\n===== TASK 2 COMPLETE =====\n";
    return 0;
}
