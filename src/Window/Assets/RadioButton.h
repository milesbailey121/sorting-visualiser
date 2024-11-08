#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class RadioButton {
public:
    RadioButton(std::string label, sf::Vector2f position, int charSize, bool isSelected = false);
    void drawTo(sf::RenderWindow &window);
    bool isPressed(sf::RenderWindow &window) const;
    void select();
    void deselect();
    bool isSelected() const;
    std::string getText() {return text.getString();};

private:
    sf::CircleShape outerCircle;  // Outer circle for radio button
    sf::CircleShape innerCircle;  // Inner circle (only shown if selected)
    sf::Text text;                // Label for the button
    sf::Font font;                // Font for the text
    bool selected;                // Whether this radio button is selected
};

#endif
