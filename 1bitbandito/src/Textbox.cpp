#include "Textbox.hpp"

Textbox::Textbox(sf::Vector2f rposition, sf::Vector2f rsize, std::string bgtext, sf::Font* font) {
	pos = rposition;
	size = rsize;
	background.setPosition(pos);
	background.setSize(size);
	background.setOutlineColor(sf::Color::White);
	background.setFillColor(sf::Color::Black);
	background.setOutlineThickness(2);

	text.setFont(*font);
	text.setFillColor(sf::Color::White);
	text.setPosition(pos);

}

Textbox::Textbox() {
	pos = { 0,0 };
	size = { 0,0 };
}

void Textbox::draw(sf::RenderWindow* window) {
	//std::cout << pos.x <<", " << pos.y << std::endl;
	UpdateDisplayText();
	window->draw(background);
	window->draw(text);
}

void Textbox::setDisplayText(std::string text) {
	displayText = text;
	UpdateDisplayText();
}

void Textbox::UpdateDisplayText() {
	text.setString(displayText);
}

bool Textbox::isPressed(sf::Vector2i mousePos) {
	if (mousePos.x > background.getPosition().x and
		mousePos.x < background.getPosition().x + background.getSize().x and
		mousePos.y > background.getPosition().y and
		mousePos.y < background.getPosition().y + background.getSize().y) {

		return true;
	}
	return false;
}