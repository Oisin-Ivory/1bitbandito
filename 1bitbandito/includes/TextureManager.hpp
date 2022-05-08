#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class TextureManager{
public:
	
	static int AddTexture(string filePath);

	static int AddTexture(string filePath,sf::IntRect area);
	
	static void RemoveTexture(int textureID);
	
	static Texture& GetTexture(int textureID);
	
private:

	static int m_currentId;
	static map<string,pair<int,unique_ptr<Texture>>> m_textures;
};
 
#endif