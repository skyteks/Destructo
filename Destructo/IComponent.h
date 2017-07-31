#pragma once

class CGameObject;
class IComponentManager;

class IComponent
{
public:
    IComponent(CGameObject* a_owner);
    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual bool AddRequiredComponents(IComponentManager* a_componentManager) = 0;
    virtual ~IComponent() {};

protected:
    CGameObject* m_owner;
};