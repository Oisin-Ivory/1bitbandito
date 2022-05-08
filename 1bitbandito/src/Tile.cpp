
#include "Tile.hpp"
//#include <iostream>


Tile::Tile(int tValue, float xpos, float ypos, sf::Texture &texture,std::vector<sf::IntRect> rects) {
	textureValue = tValue;
	x = xpos;
	y = ypos;
	//std::cout << "Sprite value : " << tValue << "Textures size: " << textures.size() << std::endl;
	sprite.setTexture(texture);
	sprite.setTextureRect(rects[tValue]);
	sprite.setPosition(x, y);
}

Tile::Tile() {
	textureValue = 0;
	x = 0;		
	y = 0;
	sprite = sf::Sprite();
}

void Tile::draw(sf::RenderWindow *window) {
	window->draw(sprite);
}
