#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <Window/GUI.h>
#include <Constants.h>
#include <Sound/SoundGenerator.h>
#include <Algorithms/Algorithms.h>
#include <Algorithms/SortingState.h>
#include <Window/Visualisation.h>

using namespace Constants;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Visualised Sorts");
    
    // Enable vertical sync to prevent screen tearing
    window.setVerticalSyncEnabled(true);
    
    // Initialize GUI
    GUI gui;
    SortingState state;
    SoundGenerator soundGen;
    soundGen.initializeSoundBuffers(WINDOW_HEIGHT);

    bool isSorting = false;
    std::string selectedSort = "";

    // Create a background rectangle
    sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH - 350, WINDOW_HEIGHT));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::Black);

    auto initializeValues = [&]() {
        int size = gui.getSlider().getSliderValue();
        state.values.resize(size);
        for (int i = 0; i < size; ++i) {
            state.values[i] = i + 1;
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(state.values.begin(), state.values.end(), g);
    };

    initializeValues();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    break;
                default:
                    break;
            }

            if (gui.getSlider().hasChanged()) {
                state.reset();
                initializeValues();
                gui.getSlider().resetChanged(); // Reset the flag after handling
            }
        }

        // Handle radio button selection
        for (auto& button : gui.getRadioButtons()) {
            if (button->isPressed(window)) {
                for (auto& btn : gui.getRadioButtons()) {
                    btn->deselect();
                }
                button->select();
                state.currentAlgorithm = button->getText();
                std::cout << "Algorithm selected: " << state.currentAlgorithm << "\n";
            }
        }

        // Handle button clicks
        for (auto& button : gui.getButtons()) {
            if (button->isPressed()) {
                if (button->getText() == "Start" && state.isSorting == false && !state.currentAlgorithm.empty()) {
                    state.isSorting = true;
                    std::cout << "Sorting started.\n";
                    if (state.currentAlgorithm == "Bubble Sort") {
                        std::cout << "Bubble Sort selected\n";  
                        state.printState();
                        SortingAlgorithms::prepareBubbleSort(state);
                    }
                    else if (state.currentAlgorithm == "Quick Sort") {
                        state.printState();
                        SortingAlgorithms::prepareQuickSort(state, 0, state.values.size() - 1);
                    }
                    else if (state.currentAlgorithm == "Merge Sort") {
                        SortingAlgorithms::prepareMergeSort(state, 0, state.values.size() - 1);
                    }
                    else if (state.currentAlgorithm == "Insertion Sort") {
                        state.printState();
                        SortingAlgorithms::prepareInsertionSort(state);
                    }
                    else if (state.currentAlgorithm == "Selection Sort") {
                        state.printState();
                        SortingAlgorithms::prepareSelectionSort(state);
                    }
                }
                else if (button->getText() == "Stop") {
                    state.isSorting = false;
                }
                else if (button->getText() == "Randomise" && state.isSorting == false) {
                    state.reset();
                    initializeValues();
                }
            }
        }
                
        
        if (state.isSorting == true && !state.sortingSteps.empty()) {
            state.printState();
            state.sortingSteps.front()();
            state.sortingSteps.pop();
        
            soundGen.playSoundForValue(state.values[state.currentIndex]);

            if (state.sortingSteps.empty()) {
                state.isSorting = false;
                Visualization::finishSort(window, state.values, soundGen);
                state.reset();
            }
        }


        window.clear();
        // Draw background
        window.draw(background);
        
        // Draw bars
        Visualization::drawBars(window, state.values, state.currentIndex, state.compareIndex);

        // Draw GUI elements on top
        for (auto& button : gui.getRadioButtons()) {
            button->drawTo(window);
        }

        for (auto& button : gui.getButtons()) {
            button->drawTo(window);
            button->logic(window);
        }

        gui.getSlider().drawTo(window);

        // Single display call per frame
        window.display();
    }

    return 0;
}