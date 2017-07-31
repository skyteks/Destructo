#include "IComponentManager.h"
#include <typeinfo>
#include "GlobalFunctions.h"

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

    if (component == nullptr)
    {
        return nullptr;
    }

    // check if required components exist / can be added
    if (!component->AddRequiredComponents(this))
    {
        SafeDelete(component);
    }

    if (component == nullptr)
    {
        return nullptr;
    }

    m_components[typeid(T).hash_code()] = component;

    // start component
    component->Initialize();

    return component;
}

template <typename T>
bool IComponentManager::RemoveComponent()
{
    auto component = m_components.find(typeid(T).hash_code());

    if (component != m_components.end() && component->second != nullptr)
    {
        SafeDelete(component->second);
        return true;
    }
    return false;
}

template <typename T>
T* IComponentManager::GetComponent() const
{
    auto component = m_components.find(typeid(T).hash_code());

    if (component != m_components.end())
    {
        return reinterpret_cast<T*>(component->second);
    }

    return nullptr;
}
