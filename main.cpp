#include <iostream>
#include <fstream>
#include <vector>

// Function to check if a certain integer exists in the array
int findInteger(const std::vector<int>& arr, int num) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == num) {
            return i;
        }
    }
    return -1; // Return -1 if not found
}

// Function to modify the value of an integer and return the old value
int modifyInteger(std::vector<int>& arr, int index, int newValue) {
    try {
        if (index < 0 || index >= arr.size()) {
            throw std::out_of_range("Invalid index.");
        }
        
        int oldValue = arr[index];
        arr[index] = newValue;
        return oldValue;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}

// Function to add a new integer to the end of the array
void addInteger(std::vector<int>& arr, int num) {
    try {
        arr.push_back(num);
    } catch (const std::bad_alloc& e) {
        std::cerr << "Error: Failed to add integer to the array. Out of memory." << std::endl;
    }
}

// Function to replace the value at a given index with 0 or remove it
void replaceOrRemove(std::vector<int>& arr, int index, bool remove) {
    if (index < 0 || index >= arr.size()) {
        std::cerr << "Invalid index." << std::endl;
        return;
    }
    
    if (remove) {
        arr.erase(arr.begin() + index);
    } else {
        arr[index] = 0;
    }
}

int main() {
    std::ifstream inputFile("data.txt");
    if (!inputFile) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::vector<int> dataArray;
    int num;
    while (inputFile >> num) {
        dataArray.push_back(num);
    }
    
    inputFile.close();

    // Test the functions
    int searchNum = 42;
    int searchResult = findInteger(dataArray, searchNum);
    if (searchResult != -1) {
        std::cout << "Found " << searchNum << " at index " << searchResult << std::endl;
    } else {
        std::cout << searchNum << " not found in the array." << std::endl;
    }

    int modifyIndex = 2;
    int newValue = 100;
    int oldValue = modifyInteger(dataArray, modifyIndex, newValue);
    if (oldValue != -1) {
        std::cout << "Modified element at index " << modifyIndex << ": old value = " << oldValue << ", new value = " << newValue << std::endl;
    }

    int newNum = 999;
    addInteger(dataArray, newNum);
    std::cout << "Added " << newNum << " to the end of the array." << std::endl;

    int replaceIndex = 4;
    bool removeElement = true; // Change to false if you want to replace with 0 instead
    replaceOrRemove(dataArray, replaceIndex, removeElement);
    std::cout << "Element at index " << replaceIndex << " " << (removeElement ? "removed" : "replaced with 0") << "." << std::endl;

    // Print the modified array
    std::cout << "Array after modifications:" << std::endl;
    for (int num : dataArray) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
