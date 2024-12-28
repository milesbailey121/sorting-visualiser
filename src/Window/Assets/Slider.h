#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Window/Assets/RoundedRectangle.h>

class Slider
{
private:
    RoundedRectangle slider;
	sf::RectangleShape axis;
	sf::Font font;
	sf::Text text;
	int minValue;
	int maxValue;
	int xCord;
	int yCord;
	int axisWidth;
	int axisHeight;
	int sliderWidth;
	int sliderHeight;
	float sliderValue;
	float previousValue;
	bool valueChanged = false;
public:
    Slider(int x, int y);
	sf::Text returnText(int x, int y, std::string z, int fontSize);
	void create(int min, int max);
	void logic(sf::RenderWindow &window);
	float getSliderValue();
	void setSliderValue(float newValue);
	void setSliderPercentValue(float newPercentValue);
	void drawTo(sf::RenderWindow & window);
	bool hasChanged() const { return valueChanged; }
    void resetChanged() { valueChanged = false; }
};

