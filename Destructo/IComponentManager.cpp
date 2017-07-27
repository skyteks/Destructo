#include "IComponentManager.h"
#include "GlobalFunctions.h"


IComponentManager::IComponentManager()
{
    for (auto& component : m_components)
    {
        component.second->Start();
    }
}


void IComponentManager::UpdateComponents()
{
    for (auto& e : m_components)
    {
        e.second->Update();
    }
}


IComponentManager::~IComponentManager()
{
    // cleanup all components
    for (auto& e : m_components)
    {
        if (e.second)
        {
            SafeDelete(e.second);
        }
    }
}
