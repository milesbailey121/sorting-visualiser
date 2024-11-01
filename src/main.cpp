#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

#include <sound_generator.h>

const int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width;
const int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height - 200;
const int NUM_BARS = 100;
const int MSEC = 5;
const int BAR_WIDTH = WINDOW_WIDTH / NUM_BARS;


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
void finishSort(std::vector<int> values, sf::RenderWindow& window, SoundGenerator& soundGen,int highlight1 = -1, int highlight2 = -1){
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
void bubbleSort(std::vector<int> values, sf::RenderWindow& window, SoundGenerator& soundGen) {
    bool swapped;
    for (size_t i = 0; i < values.size(); ++i) {
        for (size_t j = 0; j < values.size() - i - 1; ++j) {
            if (values[j] > values[j + 1]) {
                std::swap(values[j], values[j + 1]);
                drawBars(window, values, j, j + 1);
                soundGen.playSoundForValue(values[j]);
                swapped = true;
                
                // Small delay to make visualization slower
                sf::sleep(sf::milliseconds(MSEC));
            }
        }
        
        // If no swapping occurred, array is already sorted
        if (!swapped) {
            break;
        }
    }
    for (size_t i = 0; i < values.size(); i++)
   {
        finishSort(values,window,soundGen,i, i);
        soundGen.playSoundForValue(values[i]);
        sf::sleep(sf::milliseconds(MSEC));
   }
}

void selectionSort(std::vector<int> values, sf::RenderWindow& window, SoundGenerator& soundGen) {
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
    for (size_t i = 0; i < values.size(); i++)
   {
        finishSort(values,window,soundGen,i, i);
        soundGen.playSoundForValue(values[i]);
        sf::sleep(sf::milliseconds(MSEC));
   }
}

void insertionSort(std::vector<int> values, sf::RenderWindow& window, SoundGenerator& soundGen){
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
   for (size_t i = 0; i < values.size(); i++)
   {
        finishSort(values,window,soundGen,i, i);
        soundGen.playSoundForValue(values[i]);
        sf::sleep(sf::milliseconds(MSEC));
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

    // Reset window and create new shuffled values for selection sort
    selectionSort(values, window, soundGen);

    insertionSort(values, window, soundGen);

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
