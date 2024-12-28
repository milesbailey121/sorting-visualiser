#pragma once
#include <SFML/Graphics.hpp>
#include <Window/Assets/RoundedRectangle.h>
#include <iostream>

enum BUTTON_STATE{IDLE = 0, HOVER = 1, PRESSED = 2};

class Button {
private:
    RoundedRectangle button;
    sf::Text text;
    sf::Font font;
    sf::Color colorIdle;
    sf::Color colorHover;
    sf::Color colorPressed;
    int buttonState;
public:
    Button();
    Button(std::string t, sf::Vector2f size, sf::Vector2f pos, int charSize);

    void drawTo(sf::RenderWindow& window);
    void updateTextPosition();

    const RoundedRectangle& getShape() const { return button; }
    std::string getText() {return text.getString();};

    bool isMouseOver(sf::RenderWindow& window);
    const bool isPressed() const;
    const bool isHover() const;
    void logic(sf::RenderWindow& window);
};



