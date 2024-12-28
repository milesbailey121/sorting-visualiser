#include <Algorithms/SortingState.h>
#include <iostream>

void SortingState::reset() {
    currentIndex = -1;
    compareIndex = -1;
    while (!sortingSteps.empty()) sortingSteps.pop();
    isSorting = false;
}

void SortingState::addStep(const std::function<void()>& step) {
    sortingSteps.push(step);
}

void SortingState::executeNextStep() {
    if (!sortingSteps.empty()) {
        sortingSteps.front()();  // Execute the next step
        sortingSteps.pop();
    }
}

void SortingState::printState() const {
    std::cout << "SortingState Debug Info:\n";
    std::cout << "  Current Index: " << currentIndex << "\n";
    std::cout << "  Compare Index: " << compareIndex << "\n";
    std::cout << "  Is Sorting: " << (isSorting ? "Yes" : "No") << "\n";
    std::cout << "  Current Algorithm: " << currentAlgorithm << "\n";
    std::cout << "  Steps in Queue: " << sortingSteps.size() << "\n";
}