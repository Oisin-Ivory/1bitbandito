#include "Map.hpp"



Map::Map() {
	map = {};
	tileSize = {0,0};
	mapSize = {0,0};
	textureForMap = "";
}

void Map::draw(sf::RenderWindow *window){
	for (int x = 0; x < mapSize[0]; x++) {
		for (int y = 0; y < mapSize[1]; y++) {
			//std::cout << "drawing tile[ y:" << y << " + x:" << x << "* mapSize[0]" << "]" << std::endl;
			tiles[x + y * mapSize[0]].draw(window);
		}
	}
}

int Map::GetTileAtPos(int x, int y) {
	return tiles[x + y * mapSize[0]].textureValue;
}

sf::Vector2f Map::GetTilePos(int x, int y) {
	return tiles[x + y * mapSize[0]].sprite.getPosition();
}
	
void Map::CreateSpriteSheet() {

	int numOfTexturesX = 0;
	int numOfTexturesY = 0;
	int numOfTextures = 0;

	texture = TextureManager::GetTexture(TextureManager::AddTexture(textureForMap));
	//std::cout << "Succsessfully loaded Tileset texture: " << textureForMap << std::endl;
	numOfTexturesX = texture.getSize().x / tileSize[0];
	numOfTexturesY = texture.getSize().y / tileSize[1];
	numOfTextures = numOfTexturesX * numOfTexturesY;
	//std::cout << "numOfTexturesX: " << numOfTexturesX << " numOfTexturesY: " << numOfTexturesY << "numOfTextures: " << numOfTextures << std::endl;
	tilenum.resize(numOfTextures);
	//std::cout << "Textures size: " << tilenum.size();

	for (int y = 0; y < numOfTexturesY; y++) {
		for (int x = 0; x < numOfTexturesX; x++) {
			tilenum[x % numOfTexturesX + y * numOfTexturesX] = sf::IntRect((tileSize[0] * x), (tileSize[1] * y), tileSize[0], tileSize[1]);
		}
	}
}

bool Map::Load(std::string workingFile) {
	nlohmann::json j2;

	//std::cout << "loading file!" << std::endl;
	std::ifstream inputFile("resources/levels/" + workingFile + ".json");
	//std::cout << "Loading map: " << workingFile << ".json" << std::endl;
	//std::cout << "Checking read!" << std::endl;
	if (!inputFile.good()) {
		//std::cout << "No Map Found!" << std::endl;
		map = {};
		textureForMap = "";
		mapSize = { 0,0 };
		tileSize = { 0,0 };
		return false;
	}

	//std::cout << "Assigning map: "<< std::endl;
	inputFile >> j2;
	inputFile.close();

	//std::cout <<"Map is"<< j2 << std::endl;

	const std::string& load_tileset(j2["maptexture"]);
	std::vector<int> load_tiles = j2["map"];
	int load_mapWidth = j2["mapsize"][0];
	int load_mapHeight = j2["mapsize"][1];
	std::vector<int> load_tileSize = j2["tilesize"];

	//std::cout << "J2" << j2 << std::endl;

		
		/*
		for(int i: load_tileSize){
			std::cout << i << std::endl;
		}
		for(int i : load_tiles){
			std::cout << i << std::endl;
		}
		std::cout << "load_tileset: " << load_tileset  << " load_mapWidth: " << load_mapWidth << " load_mapHeight: " << load_mapHeight << std::endl;
		*/
		
	map.resize(load_mapWidth * load_mapHeight);
	tiles.resize(load_mapWidth * load_mapHeight);

	map = load_tiles;
	textureForMap = load_tileset;
	mapSize[0] = load_mapWidth;
	mapSize[1] = load_mapHeight;
	tileSize = load_tileSize;

	textureForMap = "resources/tilemaps/" + load_tileset;
	//std::cout << "Succsessfuly loaded map: " << workingFile << ".json" << std::endl;

	CreateSpriteSheet();
	SetTileSprites();
	return true;
}

void Map::SetTileSprites() {

	float localDisplayScaleFactor = 0.00;

	//std::cout << "Display Factor is: " << 800 << "/" << tileSize[0] << std::endl;

	if (mapSize[0] != 0) {

		localDisplayScaleFactor += (float)800 / ((float)tileSize[0] * (float)mapSize[0]);
		float maxSizePx = ((float)tileSize[0] * ((float)mapSize[0]* localDisplayScaleFactor));
		mapXOffset = ((((float)1280 - maxSizePx)) / (float)2);
		//std::cout << "Map X offset: " << mapXOffset << " Map Width: "<< maxSizePx <<  std::endl;
	}else {
		//std::cout << "Defaulting to 1" << std::endl;
		localDisplayScaleFactor = 1;
	}
	textureScale = localDisplayScaleFactor;

	//std::cout << "Display Factor is: " << localDisplayScaleFactor << std::endl;
	for (int y = 0; y < mapSize[0]; y++) {
		for (int x = 0; x < mapSize[1]; x++) {
			//std::cout << "Setting sprite "<< (x+(y*mapsize)) << " to position :" << x << ", " << y << std::endl;
			tiles[x + (y * mapSize[0])] = Tile(map[x + (y * mapSize[0])], mapXOffset + (x * tileSize[0] * localDisplayScaleFactor), y * tileSize[1] * localDisplayScaleFactor, TextureManager::GetTexture(TextureManager::AddTexture(textureForMap)), tilenum);
			tiles[x + (y * mapSize[0])].displayScaleFactor = localDisplayScaleFactor;
			tiles[x + (y * mapSize[0])].sprite.setScale(localDisplayScaleFactor, localDisplayScaleFactor);
		}
	}
	//std::cout << "Tiles size: " << tiles.size() << std::endl;
}

