#include <iostream>
#include <memory>
#include <vector>

// Function that takes a vector of unique_ptrs by reference
void processVector(std::vector<std::unique_ptr<int>>& vec) {
    // Modify the vector or elements if needed
    for (auto& ptr : vec) {
        // Do something with the pointed-to object, e.g., dereference and print
        std::cout << *ptr << std::endl;
    }
}

int main() {
    // Create a vector of unique_ptrs
    std::vector<std::unique_ptr<int>> vec;

    // Add some elements
    vec.push_back(std::make_unique<int>(1));
    vec.push_back(std::make_unique<int>(2));
    vec.push_back(std::make_unique<int>(3));

    // Pass the vector to the function
    processVector(vec);

    // Unique ownership semantics ensure that the resources are properly managed
    // No need to explicitly delete the pointers
    return 0;
}