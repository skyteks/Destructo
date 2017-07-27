#pragma once
#include <map>
#include "IComponent.h"

class IComponent;

class IComponentManager
{
public:
    IComponentManager();
    virtual ~IComponentManager();

    template <typename T, typename ...Args>
    T* AddComponent(Args ... args);

    template <typename T>
    void RemoveComponent();

    template <typename T>
    T* GetComponent();

protected:
    void UpdateComponents();

    std::map<size_t, IComponent*> m_components; // key = hash, value = ptr
};

#include "IComponentManager.hpp"