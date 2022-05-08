#pragma once
#include <SFML/Graphics.hpp>
class Button
{
public:
    Button(sf::Vector2f rposition, sf::Vector2f rsize, sf::Font* rfont, int routlineThickness, sf::Color routlineColor, sf::Color rcolor,std::string rtext);
    Button();
    void draw(sf::RenderWindow* window);
    bool isPressed(sf::Vector2i mousePos);
private:
    sf::RectangleShape rect;
    sf::Text text;
    //sf::Font* font;
    sf::Vector2f size;
    sf::Color outlineColor;
    int outlineThickness;
    sf::Vector2f position;
    sf::Color color;
};

