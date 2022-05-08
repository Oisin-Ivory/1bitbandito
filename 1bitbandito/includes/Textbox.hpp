#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Textbox {
public:
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::RectangleShape  background;
	sf::Text text;
	std::string displayText;

	Textbox(sf::Vector2f rposition, sf::Vector2f rsize, std::string bgtext, sf::Font* font);

	Textbox();

	void draw(sf::RenderWindow* window);

	void setDisplayText(std::string text);

	void UpdateDisplayText();

	bool isPressed(sf::Vector2i mousePos);
};


