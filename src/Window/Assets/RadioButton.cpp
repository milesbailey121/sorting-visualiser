#include "Window/Assets/RadioButton.h"
#include <iostream>

RadioButton::RadioButton(std::string t, sf::Vector2f pos, int charSize, bool isSelected) : selected(isSelected) {
    // Load font
    if (!font.loadFromFile("../src/Window/Assets/Segoe UI.ttf")) {
        std::cout << "Error loading font\n";
    } 

    // Set up the label text
    text.setString(t);
    text.setFont(font);
    text.setCharacterSize(charSize);
    text.setFillColor(sf::Color::White);
    text.setPosition(pos.x + 30, pos.y - 5);  // Offset to the right of the circle

    // Set up the outer circle for the button
    outerCircle.setRadius(10);
    outerCircle.setOutlineThickness(2);
    outerCircle.setOutlineColor(sf::Color::Black);
    outerCircle.setFillColor(sf::Color::White);
    outerCircle.setPosition(pos);

    // Set up the inner circle (only visible when selected)
    innerCircle.setRadius(5);
    innerCircle.setFillColor(sf::Color::Black);
    innerCircle.setPosition(pos.x + 5, pos.y + 5);  // Centered inside the outer circle
}

void RadioButton::drawTo(sf::RenderWindow &window) {
    window.draw(outerCircle);

    // Draw the inner circle only if the radio button is selected
    if (selected) {
        window.draw(innerCircle);
    }

    window.draw(text);
}

bool RadioButton::isPressed(sf::RenderWindow &window) const {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return outerCircle.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }
    return false;
}

void RadioButton::select() {
    selected = true;
}

void RadioButton::deselect() {
    selected = false;
}

bool RadioButton::isSelected() const {
    return selected;
}
