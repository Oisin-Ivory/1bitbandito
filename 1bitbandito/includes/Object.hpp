#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include "components/Component.hpp"

class Object
{

public:

    template <typename T, typename... Args>
    std::shared_ptr<T> AttachComponent(Args... args);

    template <typename T>
    std::shared_ptr<T> GetComponent();

    template <typename T>
    std::shared_ptr<T> GetComponents();

    template <typename T>
    std::shared_ptr<T> SetComponents(std::shared_ptr<T> cmpts);

    bool isactive = true;

private:
    //A collection of all components the object has attached.
    std::vector<std::shared_ptr<Component>> m_components; //vector<Component*> m_component


};

#include "Object.inl"
#endif 