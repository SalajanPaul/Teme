#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Prototipuri de funcții
void bubbleSort(vector<int>& numbers);
void selectionSort(vector<int>& numbers);
void quickSort(vector<int>& numbers, int left, int right);

int main() {
    // Citirea numerelor din fișier
    ifstream inputFile("numere.csv");
    if (!inputFile.is_open()) {
        cout << "Eroare la deschiderea fisierului." << endl;
        return 1;
    }

    vector<int> numbers;
    string line, number;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        while (getline(ss, number, ',')) {
            numbers.push_back(stoi(number));
        }
    }

    // Bubble sort
    bubbleSort(numbers);
    cout << "Bubble Sort: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // Selection sort
    numbers.clear(); // Resetarea vectorului
    inputFile.clear();
    inputFile.seekg(0, ios::beg); // Resetarea cursorului fișierului la început
    while (getline(inputFile, line)) {
        stringstream ss(line);
        while (getline(ss, number, ',')) {
            numbers.push_back(stoi(number));
        }
    }
    selectionSort(numbers);
    cout << "Selection Sort: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // Quick sort
    numbers.clear(); // Resetarea vectorului
    inputFile.clear();
    inputFile.seekg(0, ios::beg); // Resetarea cursorului fișierului la început
    while (getline(inputFile, line)) {
        stringstream ss(line);
        while (getline(ss, number, ',')) {
            numbers.push_back(stoi(number));
        }
    }
    quickSort(numbers, 0, numbers.size() - 1);
    cout << "Quick Sort: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    inputFile.close();

    return 0;
}

// Implementarea - Bubble sort
void bubbleSort(vector<int>& numbers) {
    int n = numbers.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                swap(numbers[j], numbers[j + 1]);
            }
        }
    }
}

// Implementarea - Selection sort
void selectionSort(vector<int>& numbers) {
    int n = numbers.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (numbers[j] < numbers[minIndex]) {
                minIndex = j;
            }
        }
        swap(numbers[i], numbers[minIndex]);
    }
}

// Implementarea - Quick sort
void quickSort(vector<int>& numbers, int left, int right) {
    if (left < right) {
        int pivotIndex = left + (right - left) / 2;
        int pivotValue = numbers[pivotIndex];

        // Partitionarea
        int i = left, j = right;
        while (i <= j) {
            while (numbers[i] < pivotValue) {
                i++;
            }
            while (numbers[j] > pivotValue) {
                j--;
            }
            if (i <= j) {
                swap(numbers[i], numbers[j]);
                i++;
                j--;
            }
        }

        // Sortarea recursivă a sub-șirurilor
        quickSort(numbers, left, j);
        quickSort(numbers, i, right);
    }
}
