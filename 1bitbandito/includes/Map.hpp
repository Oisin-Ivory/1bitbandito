#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include "Tile.hpp"
#include <fstream>
#include "TextureManager.hpp"

class Map {
public:
	Map();
	void draw(sf::RenderWindow* window);

	int GetTileAtPos(int x, int y);
	sf::Vector2f GetTilePos(int x, int y);
	void CreateSpriteSheet();
	bool Load(std::string workingFile);
	void SetTileSprites();

	std::vector<int> map;
	std::vector<int> tileSize, mapSize;
	std::string textureForMap;
	std::vector<sf::IntRect> tilenum;
	sf::Texture initTexture = sf::Texture();
	sf::Texture& texture = initTexture;
	std::vector<Tile> tiles;
	float mapXOffset = 0;
	float textureScale = 1;

};