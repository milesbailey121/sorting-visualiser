#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>
#include <cmath>
#include <sound_generator.h>

const int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width;
const int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height;
const int BAR_WIDTH = 10;
const int MSEC = 5;


// Drawing utility function
void drawBars(sf::RenderWindow& window, const std::vector<int>& values, int highlight1 = -1, int highlight2 = -1) {
    window.clear(sf::Color::Black);

    for (size_t i = 0; i < values.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH, values[i]));
        bar.setPosition(i * BAR_WIDTH, (WINDOW_HEIGHT - values[i]));

        if (i == highlight1 || i == highlight2) {
            bar.setFillColor(sf::Color::Red);  // Highlight elements being swapped
        } else {
            bar.setFillColor(sf::Color::White); // Normal bar color
        }

        window.draw(bar);
    }

    window.display();
}

void finishSort(std::vector<int> values, sf::RenderWindow& window, SoundGenerator& soundGen,int highlight1 = -1, int highlight2 = -1){
    for (size_t i = 0; i < values.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH, values[i]));
        bar.setPosition(i * BAR_WIDTH, (WINDOW_HEIGHT - values[i]));
        if (i == highlight1 || i == highlight2) {
            bar.setFillColor(sf::Color::Red);  // Highlight elements being swapped
        } else {
            bar.setFillColor(sf::Color::White); // Normal bar color
        }
        bar.setFillColor(sf::Color::Green);  // Highlight corretly sorted 
        window.draw(bar);
        soundGen.playSoundForValue(values[i]);
    }
    window.display();
}

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
                // sf::sleep(sf::milliseconds(10));
            }
        }
        
        // If no swapping occurred, array is already sorted
        if (!swapped) {
            break;
        }
    }
    finishSort(values,window,soundGen);
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
        drawBars(window, values, i, i);
        soundGen.playSoundForValue(values[i]);
        sf::sleep(sf::milliseconds(MSEC));
    }
    finishSort(values,window,soundGen);
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
        drawBars(window, values, i, i);
        soundGen.playSoundForValue(values[i]);
        sf::sleep(sf::milliseconds(MSEC));
   }
   
   finishSort(values,window,soundGen);
}

int main() {
    // Initialize values with random heights for visualization
    std::vector<int> values(WINDOW_WIDTH / BAR_WIDTH);

    // Create the window first
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Visualised Sorts");

    // Fill with values from WINDOW_HEIGHT down to 0
    for (int i = 0; i < values.size(); ++i) {
        values[i] = WINDOW_HEIGHT - i;
    }

    // Shuffle the values
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(values.begin(), values.end(), g);

    // Initialize sound generator
    SoundGenerator soundGen;
    soundGen.initializeSoundBuffers(WINDOW_HEIGHT);

    // // // Run the visualised sorting algorithms
    // bubbleSort(values, window, soundGen);

    // // // Reset window and create new shuffled values for selection sort
    // std::shuffle(values.begin(), values.end(), g);
    // selectionSort(values, window, soundGen);

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
