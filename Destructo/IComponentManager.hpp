#pragma once

//#include <typeinfo>
#include "IComponentManager.h"

template<typename T, typename... Args>
T* IComponentManager::AddComponent(Args ... args)
{
    // Only allow one component for now...
    if (m_components.find(typeid(T).hash_code()) != m_components.end())
    {
        return nullptr;
    }

    // add new component with variadic arguments
    T* component = new T(args...);

    if (!component)
    {
        return nullptr;
    }

    // check if required components exist / can be added
    if (!component->AddRequiredComponents(this))
    {
        delete component;
        component = nullptr;
    }

    // start component
    component->Start();

    if (component)
    {
        m_components[typeid(T).hash_code()] = component;
        return component;
    }

    return nullptr;
}

template <typename T>
void IComponentManager::RemoveComponent()
{
    auto component = m_components.find(typeid(T).hash_code());

    if (component != m_components.end() && component->second != nullptr)
    {
        delete component->second;
        component->second = nullptr;
    }
}

template <typename T>
T* IComponentManager::GetComponent()
{
    auto component = m_components.find(typeid(T).hash_code());

    if (component != m_components.end())
    {
        return reinterpret_cast<T*>(component->second);
    }

    return nullptr;
}
