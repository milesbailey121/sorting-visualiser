#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include <Window/Assets/Button.h>
#include <Window/Assets/Slider.h>
#include <Window/Assets/RadioButton.h>

class GUI {
public:
    GUI();
    std::vector<std::unique_ptr<Button>>& getButtons() { return buttons; }
    std::vector<std::unique_ptr<RadioButton>>& getRadioButtons() { return radioButtons; }
    Slider& getSlider() { return slider; }

private:
    void createButtons();
    void createRadioButtons();
    void createSlider();

    std::vector<std::unique_ptr<Button>> buttons;
    std::vector<std::unique_ptr<RadioButton>> radioButtons;
    Slider slider;
    
    const float buttonWidth = 150.0f;
    const float buttonHeight = 50.0f;
};
