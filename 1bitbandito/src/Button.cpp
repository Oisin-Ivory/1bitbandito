#include "Button.hpp"

Button::Button(sf::Vector2f rposition, sf::Vector2f rsize,sf::Font *rfont, int routlineThickness, sf::Color routlineColor, sf::Color rcolor, std::string rtext) {
	position = rposition;
	size = rsize;

	outlineThickness = routlineThickness;
	outlineColor = routlineColor;
	color = rcolor;

	rect = sf::RectangleShape();
	rect.setPosition(position);
	rect.setSize(size);
	rect.setOutlineThickness(outlineThickness);
	rect.setOutlineColor(outlineColor);
	rect.setFillColor(color);

	text = sf::Text();
	text.setString(rtext);
	text.setPosition(position);
	text.setFont(*rfont);


}

Button::Button() {
	position = { 0,0 };
	size = { 100,100 };
	outlineThickness = 1;
	outlineColor = sf::Color::White;
	color = sf::Color::Black;

	rect = sf::RectangleShape();
	rect.setPosition(position);
	rect.setSize(size);
	rect.setOutlineThickness(outlineThickness);
	rect.setOutlineColor(outlineColor);
	rect.setFillColor(color);

	text = sf::Text();
	text.setString("notext");
	text.setPosition(position);


}

void Button::draw(sf::RenderWindow* window) {
	window->draw(rect);
	window->draw(text);
}

bool Button::isPressed(sf::Vector2i mousePos) {
	if (mousePos.x > rect.getPosition().x and
		mousePos.x < rect.getPosition().x + rect.getSize().x and
		mousePos.y > rect.getPosition().y and
		mousePos.y < rect.getPosition().y + rect.getSize().y) {

		return true;
	}
	return false;
}