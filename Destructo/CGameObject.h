#pragma once
#include "IComponentManager.h"

class CGameObject : public IComponentManager
{
public:
    CGameObject();
    //CGameObject(std::string a_name);

    virtual ~CGameObject();

    void Initialize();
    void Update();

    //std::string m_name;
};