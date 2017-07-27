#pragma once

#include "IComponentManager.h"

class IComponentManager;

class IComponent
{
public:
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual bool AddRequiredComponents(IComponentManager* a_componentManager) = 0;
    virtual ~IComponent() {};
};