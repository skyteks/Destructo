#pragma once
#include <map>
#include "IComponent.h"

typedef std::map<size_t, IComponent*> ComponentMap;

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

    ComponentMap m_components;
};

#include "IComponentManager.hpp"