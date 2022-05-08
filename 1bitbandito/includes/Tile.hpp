#ifndef TILE_H
#define TILE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
//#include <iostream>

class Tile {

public:
	int textureValue = 0;
	int x = 0;
	int y = 0;
	sf::Sprite sprite = sf::Sprite();
	float displayScaleFactor = 1;
	Tile(int tValue, float xpos, float ypos, sf::Texture& texture, std::vector<sf::IntRect> rects);

	Tile();
	void draw(sf::RenderWindow* window);

};
#endif