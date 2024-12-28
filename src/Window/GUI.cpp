#include "Window/GUI.h"
#include <Constants.h>

GUI::GUI() : slider(Constants::WINDOW_WIDTH - 263, 150) {
    createButtons();
    createRadioButtons();
    createSlider();
}

void GUI::createButtons() {
    buttons.emplace_back(std::make_unique<Button>("Start", 
        sf::Vector2f(buttonWidth, buttonHeight),
        sf::Vector2f(Constants::WINDOW_WIDTH - 320, 10), 24));
        
    buttons.emplace_back(std::make_unique<Button>("Stop",
        sf::Vector2f(buttonWidth, buttonHeight),
        sf::Vector2f(Constants::WINDOW_WIDTH - 160, 10), 24));
        
    buttons.emplace_back(std::make_unique<Button>("Randomise",
        sf::Vector2f(buttonWidth, buttonHeight),
        sf::Vector2f(Constants::WINDOW_WIDTH - 320, 70), 24));
        
    buttons.emplace_back(std::make_unique<Button>("About",
        sf::Vector2f(buttonWidth, buttonHeight),
        sf::Vector2f(Constants::WINDOW_WIDTH - 160, 70), 24));
}

void GUI::createRadioButtons() {
    radioButtons.emplace_back(std::make_unique<RadioButton>("Bubble Sort",
        sf::Vector2f(Constants::WINDOW_WIDTH - 320, 200), 18));
    radioButtons.emplace_back(std::make_unique<RadioButton>("Quick Sort",
        sf::Vector2f(Constants::WINDOW_WIDTH - 320, 250), 18));
    radioButtons.emplace_back(std::make_unique<RadioButton>("Merge Sort",
        sf::Vector2f(Constants::WINDOW_WIDTH - 320, 300), 18));
    radioButtons.emplace_back(std::make_unique<RadioButton>("Insertion Sort",
        sf::Vector2f(Constants::WINDOW_WIDTH - 320, 350), 18));
    radioButtons.emplace_back(std::make_unique<RadioButton>("Selection Sort",
        sf::Vector2f(Constants::WINDOW_WIDTH - 320, 400), 18));
}

void GUI::createSlider() {
    slider.create(10, 10000);
    slider.setSliderValue(100.0f);
}
