#include "Object.hpp"

template <typename T, typename... Args>
std::shared_ptr<T> Object::AttachComponent(Args... args)
{
    // Create the component.
    std::shared_ptr<T> newComponent = std::make_shared<T>();
    // Check that we don't already have a component of this type.
    for (std::shared_ptr<Component>& exisitingComponent : m_components)
    {
        if (std::dynamic_pointer_cast<T>(exisitingComponent))
        {
            // If we do replace it.
            exisitingComponent = newComponent;
            return newComponent;
        }

    }

    // The component is the first of its type so add it.

    
    m_components.push_back(newComponent);

    return newComponent;
}

template <typename T>
std::shared_ptr<T> Object::GetComponent()//returning effectively T*
{
    // Check that we have a component of this type.
    for (std::shared_ptr<Component> exisitingComponent : m_components)
    {
        if (std::dynamic_pointer_cast<T>(exisitingComponent))
        {
            return std::dynamic_pointer_cast<T>(exisitingComponent);
        }
    }
    return nullptr;
}

template <typename T>
std::shared_ptr<T> Object::GetComponents()//returning effectively T*
{
    return m_components;
}

template <typename T>
std::shared_ptr<T> Object::SetComponents(std::shared_ptr<T> cmpts)//returning effectively T*
{
    m_components = cmpts;
}
