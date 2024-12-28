#include "Window/Assets/Button.h"

Button::Button() { }

Button::Button(std::string t, sf::Vector2f size, sf::Vector2f pos, int charSize) {

	if (!font.loadFromFile("../src/Window/Assets/Segoe UI.ttf")) {
    std::cout << "Error loading font\n";
    }

    text.setString(t);
    text.setFillColor(sf::Color(64, 64, 64));
    text.setCharacterSize(charSize);
    text.setFont(font);

    this->colorIdle = sf::Color(192, 192, 192);
    this->colorHover = sf::Color(224, 224, 224);
    this->colorPressed = sf::Color::Red;

    button.setSize(size);
    button.setFillColor(colorIdle);
    button.setPosition(pos);

    // Center the text within the button
    updateTextPosition();
}

// void Button::setPosition(sf::Vector2f pos) {
//     button.setPosition(pos);
//     updateTextPosition();
// }

bool Button::isMouseOver(sf::RenderWindow& window) {
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;

    float btnPosX = button.getPosition().x;
    float btnPosY = button.getPosition().y;

    float btnPosXWidth = button.getPosition().x + button.getSize().x;
    float btnPosYHeight = button.getPosition().y + button.getSize().y;

    // Checks if mouse is within the button!
    if (mouseX < btnPosXWidth && mouseX > btnPosX && mouseY < btnPosYHeight && mouseY > btnPosY) {
        return true;
    }
    return false;
}

const bool Button::isPressed() const {
    return this->buttonState == PRESSED;
}

const bool Button::isHover() const{
    return this->buttonState == HOVER;
}

void Button::logic(sf::RenderWindow& window){
    if (isMouseOver(window))
    {
        button.setFillColor(this->colorHover);
        this->buttonState = HOVER;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            button.setFillColor(this->colorPressed);
            this->buttonState = PRESSED;
        }
    } else {
        button.setFillColor(this->colorIdle);
        this->buttonState = IDLE;
    }
}

void Button::drawTo(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(text);
}

void Button::updateTextPosition() {
    // Center the text horizontally and vertically within the button
    // Get Local Text bounds
    sf::FloatRect textBounds = text.getLocalBounds();

    // Center the text within the button
    text.setPosition(
        button.getPosition().x + (button.getSize().x - textBounds.width) / 2.0f - textBounds.left,
        button.getPosition().y + (button.getSize().y - textBounds.height) / 2.0f - textBounds.top
    );
}