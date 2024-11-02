#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

#include <SoundGenerator.h>
#include <Constants.h>

using namespace Constants;

/**
 * @brief Draws bars representing values on the SFML window.
 *
 * Each bar represents a value in the `values` vector, with optional highlights
 * for elements being swapped or compared.
 *
 * @param window The SFML RenderWindow where bars are drawn.
 * @param values A vector of integers representing the heights of each bar.
 * @param highlight1 The index of the first element to highlight (default: -1).
 * @param highlight2 The index of the second element to highlight (default: -1).
 */
void drawBars(sf::RenderWindow& window, const std::vector<int>& values, int highlight1 = -1, int highlight2 = -1) {
    window.clear(sf::Color::Black);

    // Find the maximum value in values for height scaling
    int maxValue = *std::max_element(values.begin(), values.end());
    float heightScale = static_cast<float>(WINDOW_HEIGHT) / maxValue;

    for (size_t i = 0; i < values.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH - 1, values[i] * heightScale)); // Leave a small gap between bars
        bar.setPosition(i * BAR_WIDTH, WINDOW_HEIGHT - (values[i] * heightScale));

        if (i == highlight1 || i == highlight2) {
            bar.setFillColor(sf::Color::Red);  // Highlight elements being swapped
        } else {
            bar.setFillColor(sf::Color::White); // Normal bar color
        }

        window.draw(bar);
    }

    window.display();
}

/**
 * @brief Draws bars representing values on the SFML window after sorting.
 *
 * Each bar represents a value in the `values` vector, with highlights
 * for elements being sorted or not.
 *
 * @param values A vector of integers representing the heights of each bar.
 * @param window The SFML RenderWindow where bars are drawn.
 * @param soundGen 
 * @param highlight1 The index of the first element to highlight (default: -1).
 * @param highlight2 The index of the second element to highlight (default: -1).
 */
void finishAnimation(std::vector<int>& values, sf::RenderWindow& window, SoundGenerator& soundGen,int highlight1 = -1, int highlight2 = -1){
    int maxValue = *std::max_element(values.begin(), values.end());
    float heightScale = static_cast<float>(WINDOW_HEIGHT) / maxValue;
    for (size_t i = 0; i < values.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH - 1, values[i] * heightScale)); // Leave a small gap between bars
        bar.setPosition(i * BAR_WIDTH, WINDOW_HEIGHT - (values[i] * heightScale));
        if (highlight1 >= i){
            bar.setFillColor(sf::Color::Green);  // Highlight corretly sorted 
        } else {
            bar.setFillColor(sf::Color::White); // Normal bar color
        }
        window.draw(bar);
    }
    window.display();
}

void finishSort(std::vector<int>& values, sf::RenderWindow& window, SoundGenerator& soundGen){
    for (size_t i = 0; i < values.size(); i++)
   {
        finishAnimation(values,window,soundGen,i, i);
        soundGen.playSoundForValue(values[i]);
        sf::sleep(sf::milliseconds(MSEC));
   }
}

/**
 * @brief Sorts the vector `values` using the Bubble Sort algorithm with visualization.
 *
 * This function sorts the given vector `values` by iteratively comparing adjacent elements
 * and swapping them if needed. The algorithm provides real-time visual feedback on the SFML
 * window and plays corresponding sounds for each swap.
 *
 * @param values The vector of integers to sort.
 * @param window The SFML window where the sorting visualization is displayed.
 * @param soundGen The SoundGenerator object that plays sound feedback.
 *
 * @note This function uses a `bool` flag to detect if no swaps occurred in an iteration,
 *       allowing early exit when the vector is already sorted.
 */
void bubbleSort(std::vector<int>& values, sf::RenderWindow& window, 
                SoundGenerator& soundGen) {

    for (size_t i = 0; i < values.size(); ++i) {
        for (size_t j = 0; j < values.size() - i - 1; ++j) {
            if (values[j] > values[j + 1]) {
                std::swap(values[j], values[j + 1]);
                drawBars(window, values, j, j + 1);
                soundGen.playSoundForValue(values[j]);
                sf::sleep(sf::milliseconds(MSEC));
            }
        }
    }
}

void selectionSort(std::vector<int>& values, sf::RenderWindow& window, SoundGenerator& soundGen) {
    for (size_t i = 0; i < values.size(); i++) {
        int min_index = i;
        for (size_t j = i + 1; j < values.size(); j++) {
            if (values[min_index] > values[j]) {
                min_index = j;
            }
        }
        
        // swap i index with min_index 
        std::swap(values[i], values[min_index]);
        drawBars(window, values, i, min_index);  // Draw bars with highlighted swap
        soundGen.playSoundForValue(values[i]);
        
        // Small delay to make visualization slower
        sf::sleep(sf::milliseconds(MSEC));
    }
}

void insertionSort(std::vector<int>& values, sf::RenderWindow& window, SoundGenerator& soundGen){
   for (size_t i = 1; i < values.size(); i++) // Start with second element of the array
   {
    int key = values[i];
    int j = i - 1;

    while (j >= 0 && values[j] > key)
    {
        values[j + 1] = values[j];
        drawBars(window, values, j+1, j);  // Draw bars with highlighted swap
        soundGen.playSoundForValue(values[j + 1]);
        sf::sleep(sf::milliseconds(MSEC));
        j = j -1;
    }
    values[j + 1] = key;
   }
}

int partition(std::vector<int>& values, sf::RenderWindow& window, SoundGenerator& soundGen, int low, int high) {
    int pivot = values[high];
    int i = low - 1;

    // Highlight pivot element
    drawBars(window, values, high, -1);
    sf::sleep(sf::milliseconds(MSEC));

    for (int j = low; j <= high - 1; j++) {
        // Highlight current element being compared
        drawBars(window, values, j, high);
        soundGen.playSoundForValue(values[j]);
        sf::sleep(sf::milliseconds(MSEC));

        if (values[j] < pivot) {
            i++;
            std::swap(values[i], values[j]);
            // Highlight swapped elements
            drawBars(window, values, i, j);
            soundGen.playSoundForValue(values[j]);
            sf::sleep(sf::milliseconds(MSEC));
        }
    }
    std::swap(values[i + 1], values[high]);
    drawBars(window, values, i+1, high);
    soundGen.playSoundForValue(values[high]);
    sf::sleep(sf::milliseconds(MSEC));
    return i + 1;
}

void quickSort(std::vector<int>& values, sf::RenderWindow& window, SoundGenerator& soundGen, int low, int high) {
    if (low < high) {
        // Show current partition range
        drawBars(window, values, low, high);
        sf::sleep(sf::milliseconds(MSEC));

        int pivot = partition(values, window, soundGen, low, high);
        quick_sort(values, window, soundGen, low, pivot - 1);    // Sort left partition
        quick_sort(values, window, soundGen, pivot + 1, high);   // Sort right partition
    }
}

void merge(std::vector<int>& values, sf::RenderWindow& window,SoundGenerator& soundGen, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> leftVal(n1), rightVal(n2);
    
    // Copy data to temporary vectors
    for (i = 0; i < n1; i++)
        leftVal[i] = values[left + i];
    for (j = 0; j < n2; j++)
        rightVal[j] = values[mid + 1 + j];
    
    i = 0;
    j = 0;
    k = left;
    
    while (i < n1 && j < n2) {
        // Highlight the elements being compared
        drawBars(window, values, left + i, mid + 1 + j);
        soundGen.playSoundForValue(values[mid + 1 + j]);
        sf::sleep(sf::milliseconds(MSEC));
        
        if (leftVal[i] <= rightVal[j]) {
            values[k] = leftVal[i];
            i++;
        } else {
            values[k] = rightVal[j];
            j++;
        }
        k++;
        
        // Show the result after each merge step
        drawBars(window, values, k - 1);
        soundGen.playSoundForValue(values[k - 1]);
        sf::sleep(sf::milliseconds(MSEC));
    }
    
    while (i < n1) {
        values[k] = leftVal[i];
        // Highlight the remaining elements being copied
        drawBars(window, values, left + i);
        soundGen.playSoundForValue(values[left + i]);
        sf::sleep(sf::milliseconds(MSEC));
        i++;
        k++;
    }
    
    while (j < n2) {
        values[k] = rightVal[j];
        // Highlight the remaining elements being copied
        drawBars(window, values, mid + 1 + j);
        soundGen.playSoundForValue(values[mid + 1 + j]);
        sf::sleep(sf::milliseconds(MSEC));
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& values, sf::RenderWindow& window,SoundGenerator& soundGen, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Highlight the current section being sorted
        drawBars(window, values, left, right);
        soundGen.playSoundForValue(values[right]);
        sf::sleep(sf::milliseconds(MSEC));
        
        mergeSort(values, window, soundGen, left, mid);
        mergeSort(values, window, soundGen, mid + 1, right);
        
        merge(values, window, soundGen, left, mid, right);
    }
}

/**
 * @brief Main entry point for the sorting visualization program.
 *
 * Initializes the window, generates a random set of values, and calls a sorting
 * algorithm with real-time visualization and sound playback.
 *
 * @return int Status code, 0 for successful execution.
 */
int main() {
    // Initialize values with random heights for visualization
    std::vector<int> values(NUM_BARS);

    // Create the window first
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Visualised Sorts");

    // Fill with values from WINDOW_HEIGHT down to 0
    for (int i = 1; i < values.size(); ++i) {
        values[i] = i;
    }

    // Shuffle the values
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(values.begin(), values.end(), g);

    // Initialize sound generator
    SoundGenerator soundGen;
    soundGen.initializeSoundBuffers(WINDOW_HEIGHT);

    // Run the visualised sorting algorithms
    bubbleSort(values, window, soundGen);
    finishSort(values, window, soundGen);
    std::shuffle(values.begin(), values.end(), g);

    selectionSort(values, window, soundGen);
    finishSort(values, window, soundGen);
    std::shuffle(values.begin(), values.end(), g);

    insertionSort(values, window, soundGen);
    finishSort(values, window, soundGen);
    std::shuffle(values.begin(), values.end(), g);

    quickSort(values,window, soundGen, 0, values.size() - 1);
    finishSort(values, window, soundGen);
    std::shuffle(values.begin(), values.end(), g);

    mergeSort(values,window,soundGen,0, values.size() - 1);
    finishSort(values, window, soundGen);
    std::shuffle(values.begin(), values.end(), g);

    // Wait until the window is closed
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    return 0;
}
