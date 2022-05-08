#ifndef inputControllerCmpt_hpp
#define inputControllerCmpt_hpp

#include <stdio.h>
#include <iostream>
#include "component.hpp"

class inputControllerCmpt : public Component
{
public:
    inputControllerCmpt();
    enum class KEY { LEFT, RIGHT, UP, DOWN, W, A, S, D, ESC, SHIFT };
    bool IsKeyPressed(KEY keycode);


};
#endif


/*
#ifndef inputControllerCmpt_hpp
#define inputControllerCmpt_hpp

#include <stdio.h>
#include <iostream>
#include "component.hpp"

class inputControllerCmpt : public Component
{
public:
    inputControllerCmpt(){}
    enum KEY {LEFT, RIGHT, UP, DOWN, ATTACK, ESC, SHIFT};
    
bool IsKeyPressed(KEY keycode)
    {
       switch (keycode)
       {
           case KEY::LEFT:
               if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
               {
                   std::cout <<"You pressed the left key" <<std::endl;
                   return true;
               }
               break;
       }
    }
    
};
#endif /* inputControllerCmpt_hpp */
