
#ifndef GraphicsCmpt_hpp
#define GraphicsCmpt_hpp

#include <stdio.h>
#include "component.hpp"
#include <SFML/Graphics.hpp>

class GraphicsCmpt: public Component
{
public:
    GraphicsCmpt(){}
    void Draw(sf::RenderWindow &window, float timeDelta); 
private:
    float m_timeDelta; 
};
#endif /* GraphicsCmpt_hpp */