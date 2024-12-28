#include <Algorithms/AlgorithmStats.h>

AlgorithmStats::AlgorithmStats():
    comparisons(0),
    swaps(0),
    executionTime(0) {}

void AlgorithmStats::start(){
    reset();
    startTime = std::chrono::high_resolution_clock::now();
}

void AlgorithmStats::end(){
    auto endTime = std::chrono::high_resolution_clock::now();
    executionTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();
}

void AlgorithmStats::reset(){
    comparisons = 0;
    swaps = 0;
    executionTime = 0;
}

int AlgorithmStats::getComparisons() const{
    return comparisons;
}    

int AlgorithmStats::getSwaps() const{
    return swaps;
}    

double AlgorithmStats::getExecutionTime() const{
    return comparisons;
}    

void AlgorithmStats::incrementComparisons(){
    ++comparisons;
}

void AlgorithmStats::incrementSwaps(){
    ++swaps;
}