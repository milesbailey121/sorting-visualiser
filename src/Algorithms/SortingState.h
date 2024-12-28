#pragma once
#include <vector>
#include <queue>
#include <functional>
#include <string>

struct SortingState {
    std::vector<int> values;                
    int currentIndex = -1;                  // Current element being processed
    int compareIndex = -1;                  // Element being compared
    bool isSorting = false;                
    std::string currentAlgorithm;           // Name of the active algorithm
    std::queue<std::function<void()>> sortingSteps; // Steps to perform

    void reset();                           // Reset the state to initial
    void addStep(const std::function<void()>& step); // Add a new step
    void executeNextStep();                 // Execute the next step
    void printState() const;                // Debug information
};

