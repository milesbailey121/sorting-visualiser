#pragma once
#include <Algorithms/SortingState.h>

class SortingAlgorithms {
public:
    static void prepareBubbleSort(SortingState& state);
    static void prepareSelectionSort(SortingState& state);
    static void prepareInsertionSort(SortingState& state);
    //Quick Sort
    static void prepareQuickSort(SortingState& state, int low, int high);
    static int partition(SortingState& state, int low, int high);
    // Merge
    static void prepareMergeSort(SortingState& state, int left, int right);
    static void merge(SortingState& state, int left, int mid, int right);
private:
    // Helper functions
};