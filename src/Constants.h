#pragma once
#include <SFML/Graphics.hpp>

namespace Constants {
    const int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width;
    const int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height - 200;
    const int NUM_BARS = 100;
    const int MSEC = 20;
    const int BAR_WIDTH = (WINDOW_WIDTH - 300) / NUM_BARS;  // Adjusted for control panel
}