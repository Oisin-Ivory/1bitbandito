#include "ReadableInfoCMPT.hpp"

std::vector<std::string> information;
void ReadableInfoCMPT::Draw(sf::RenderWindow& window, float timeDelta)
{
}

void ReadableInfoCMPT::addComponentDetails(std::string info)
{
	information.push_back(info);
}

bool ReadableInfoCMPT::containsComponentDetails(std::string searchTerm)
{	
	for (std::string info : information) {
		if (info == searchTerm) {
			return true;
		}
	}
	
	return false;
}
