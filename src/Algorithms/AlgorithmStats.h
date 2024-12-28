#pragma once
#include <chrono>

class AlgorithmStats
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    int comparisons = 0;
    int swaps = 0;
    double executionTime = 0.0;
public:
    AlgorithmStats();
    void start();
    void end();
    void reset();

    int getComparisons() const;
    int getSwaps() const;
    double getExecutionTime() const;

    void incrementComparisons();
    void incrementSwaps();
};
