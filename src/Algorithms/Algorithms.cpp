#include <Algorithms/Algorithms.h>
#include <iostream>

// Bubble Sort
void SortingAlgorithms::prepareBubbleSort(SortingState& state) {
    size_t n = state.values.size();
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            state.sortingSteps.push([&state, j]() {
                state.currentIndex = j;            // Update current index
                state.compareIndex = j + 1;       // Update compare index
                if (state.values[j] > state.values[j + 1]) {
                    std::swap(state.values[j], state.values[j + 1]); // Swap values
                }
            });
        }
    }
}

void SortingAlgorithms::prepareSelectionSort(SortingState& state) {
    size_t n = state.values.size();

    for (size_t i = 0; i < n - 1; i++) {
        size_t minIdx = i;

        for (size_t j = i + 1; j < n; j++) {
            state.sortingSteps.push([&state, j, &minIdx]() {
                state.currentIndex = minIdx;
                state.compareIndex = j;

                if (state.values[j] < state.values[minIdx]) {
                    minIdx = j;
                }
            });
        }

        state.sortingSteps.push([&state, i, minIdx]() {
            if (i != minIdx) {
                std::swap(state.values[i], state.values[minIdx]);
            }
        });
    }
}

void SortingAlgorithms::prepareInsertionSort(SortingState& state) {
    size_t n = state.values.size();

    for (size_t i = 1; i < n; i++) {
        int key = state.values[i];
        int j = i - 1;

        // Push a step to indicate the start of the current iteration
        state.sortingSteps.push([&state, i]() {
            state.currentIndex = i;
            state.compareIndex = i - 1;
        });

        // Inner loop: comparing and shifting elements
        while (j >= 0 && state.values[j] > key) {
            state.sortingSteps.push([&state, i, j]() {
                state.currentIndex = i;
                state.compareIndex = j;
                state.values[j + 1] = state.values[j]; // Shift value
                std::cout << "Shifting value at index " << j << " to index " << (j + 1) << std::endl;
            });
            j--;
        }

        // Place the key in its correct position
        state.sortingSteps.push([&state, j, key]() {
            state.values[j + 1] = key;
        });

        if (i == n - 1) {
            std::cout << "Final iteration: i=" << i << ", key=" << key << std::endl;
        }
    }
}

// void SortingAlgorithms::prepareInsertionSort(SortingState& state) {
//     size_t n = state.values.size();

//     for (size_t i = 1; i < n; i++) {
//         int key = state.values[i];
//         int j = i - 1;

 
//         while (j >= 0 && state.values[j] > key) {
//             state.sortingSteps.push([&state,i, j]() {
//                 state.currentIndex = i;
//                 state.compareIndex = j;
//                 state.values[j + 1] = state.values[j];
//             });
//             j--;
//         }

//         state.sortingSteps.push([&state, j, key]() {
//             state.values[j + 1] = key;
//         });
//     }
// }

void SortingAlgorithms::prepareQuickSort(SortingState& state, int low, int high) {
    if (low < high) {
        int pivot = partition(state, low, high);
        prepareQuickSort(state, low, pivot - 1);
        prepareQuickSort(state, pivot + 1, high);
    }
}

int SortingAlgorithms::partition(SortingState& state, int low, int high) {
    int pivot = state.values[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        state.sortingSteps.push([&state, j, pivot, &i, high]() {
            state.currentIndex = j;
            state.compareIndex = high;

            if (state.values[j] < pivot) {
                i++;
                std::swap(state.values[i], state.values[j]);
            }
        });
    }

    state.sortingSteps.push([&state, &i, high]() {
        std::swap(state.values[i + 1], state.values[high]);
    });

    return i + 1;
}

void SortingAlgorithms::prepareMergeSort(SortingState& state, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    prepareMergeSort(state, left, mid);
    prepareMergeSort(state, mid + 1, right);
    merge(state, left, mid, right);
}

void SortingAlgorithms::merge(SortingState& state, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        state.sortingSteps.push([&state, &i, &j, &k, &temp]() {
            state.currentIndex = i;
            state.compareIndex = j;

            if (state.values[i] <= state.values[j]) {
                temp[k++] = state.values[i++];
            } else {
                temp[k++] = state.values[j++];
            }
        });
    }

    while (i <= mid) {
        state.sortingSteps.push([&state, &i, &k, &temp]() {
            state.currentIndex = i;
            temp[k++] = state.values[i++];
        });
    }

    while (j <= right) {
        state.sortingSteps.push([&state, &j, &k, &temp]() {
            state.compareIndex = j;
            temp[k++] = state.values[j++];
        });
    }

    state.sortingSteps.push([&state, &temp, left, right]() {
        for (int m = 0; m < temp.size(); m++) {
            state.values[left + m] = temp[m];
        }
    });
}