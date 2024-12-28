#include <algorithm>
#include <Window/Visualisation.h>
#include <Constants.h>
#include <iostream>
using namespace Constants;

float Visualization::calculateBarWidth(size_t numBars) {
    // Calculate available width for visualization
    float availableWidth = WINDOW_WIDTH - 350;
    // Calculate bar width (subtract 1 for gap between bars)
    return (availableWidth / numBars) - 1;
}

void Visualization::drawBars(sf::RenderWindow& window, const std::vector<int>& values, 
                           int highlight1, int highlight2) {
    int maxValue = *std::max_element(values.begin(), values.end());
    float heightScale = static_cast<float>(WINDOW_HEIGHT) / maxValue;
    float barWidth = calculateBarWidth(values.size());

    for (size_t i = 0; i < values.size(); ++i) {
        float barHeight = values[i] * heightScale;
        sf::RectangleShape bar(sf::Vector2f(barWidth, barHeight));
        
        // Position bars with dynamic width, leaving room for GUI on right
        bar.setPosition(i * (barWidth + 1), 
                       WINDOW_HEIGHT - barHeight);

        if (i == highlight1 || i == highlight2) {
            bar.setFillColor(sf::Color::Red);
        } else {
            bar.setFillColor(sf::Color::White);
        }

        window.draw(bar);
    }
}

void Visualization::finishAnimation(sf::RenderWindow& window, const std::vector<int>& values, 
                                  SoundGenerator& soundGen, int highlight1, int highlight2) {
    int maxValue = *std::max_element(values.begin(), values.end());
    float heightScale = static_cast<float>(WINDOW_HEIGHT) / maxValue;
    float barWidth = calculateBarWidth(values.size());
    std::cout << "finishAnimation started!" << std::endl;  
    for (size_t i = 0; i < values.size(); ++i) {
        float barHeight = values[i] * heightScale;
        sf::RectangleShape bar(sf::Vector2f(barWidth, barHeight));
        bar.setPosition(i * (barWidth + 1), 
                       WINDOW_HEIGHT - barHeight);
        
        if (highlight1 >= i) {
            bar.setFillColor(sf::Color::Green);
        } else if (i == highlight1 || i == highlight2) {
            bar.setFillColor(sf::Color::Red);
        } else {
            bar.setFillColor(sf::Color::White);
        }   
        
        window.draw(bar);
    }
}

void Visualization::finishSort(sf::RenderWindow& window, std::vector<int>& values, 
                             SoundGenerator& soundGen) {
    std::cout << "finishSort started!" << std::endl;                           
    for (size_t i = 0; i < values.size(); i++) {
        
        
        finishAnimation(window, values, soundGen, i, i + 1); // Highlight the current index
        soundGen.playSoundForValue(values[i]);
        window.display();

        
        sf::sleep(sf::milliseconds(MSEC));
    }
}