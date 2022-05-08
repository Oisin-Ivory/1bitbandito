#include "inputControllerCmpt.hpp"

inputControllerCmpt::inputControllerCmpt() {

}
bool inputControllerCmpt::IsKeyPressed(KEY keycode)
{
    switch (keycode)
    {
    case KEY::LEFT:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            //std::cout << "You pressed the left key" << std::endl;
            return true;
        }
        break;

    case KEY::RIGHT:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            //std::cout << "You pressed the right key" << std::endl;
            return true;
        }
        break;
    case KEY::UP:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            //std::cout << "You pressed the up key" << std::endl;
            return true;
        }
        break;
    case KEY::DOWN:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            //std::cout << "You pressed the DOWN key" << std::endl;
            return true;
        }
        break;
    case KEY::A:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            //std::cout << "You pressed the left key" << std::endl;
            return true;
        }
        break;

    case KEY::D:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            //std::cout << "You pressed the right key" << std::endl;
            return true;
        }
        break;
    case KEY::W:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            //std::cout << "You pressed the up key" << std::endl;
            return true;
        }
        break;
    case KEY::S:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            //std::cout << "You pressed the DOWN key" << std::endl;
            return true;
        }
        break;
    }
}


