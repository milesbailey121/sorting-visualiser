#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <Algorithms/SortingState.h>
#include <Sound/SoundGenerator.h>

class Visualization {
public:
    static void drawBars(sf::RenderWindow& window, const std::vector<int>& values, 
                        int highlight1 = -1, int highlight2 = -1);
    static void finishAnimation(sf::RenderWindow& window, const std::vector<int>& values, 
                              SoundGenerator& soundGen, int highlight1 = -1, int highlight2 = -1);
    static void finishSort(sf::RenderWindow& window, std::vector<int>& values, 
                          SoundGenerator& soundGen);
private:
    static float calculateBarWidth(size_t numBars);
};