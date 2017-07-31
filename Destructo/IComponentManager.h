#pragma once
#include <map>

class IComponent;

class IComponentManager
{
public:
    IComponentManager();
    virtual ~IComponentManager();

    template <typename T, typename ...Args>
    T* AddComponent(Args ... args);

    template <typename T>
    bool RemoveComponent();

    template <typename T>
    T* GetComponent() const;

protected:
    void UpdateComponents();

    std::map<size_t, IComponent*> m_components; // key = hash, value = ptr
};

#include "IComponentManager.hpp"