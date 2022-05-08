#ifndef READABLEINFOCMPT_H
#define READABLEINFOCMPT_H

#include <iostream>
#include "Component.hpp"

class ReadableInfoCMPT : public Component
{
public:
    ReadableInfoCMPT() {}
    virtual void Update(float timeDelta) {};
    void Draw(sf::RenderWindow& window, float timeDelta);
    void addComponentDetails(std::string info);
    bool containsComponentDetails(std::string searchTerm);
    std::vector<std::string> information;
private:
    float m_timeDelta;
   
};

#endif