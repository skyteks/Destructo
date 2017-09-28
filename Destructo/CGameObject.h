#pragma once
#include "IComponentManager.h"
#include <vector>

class CGameObject : public IComponentManager
{
public:
    //#define GetTransform() GetComponent<CTransform>();

    CGameObject();
    CGameObject(std::string a_name);

    virtual ~CGameObject();

    void Update();
    //const CGameObject* GetRoot() const;
    //const CGameObject* GetParent() const;
    //void SetParent(CGameObject* a_parent);

protected:
    std::string m_name;
    //CGameObject* m_parent;
    //std::vector<CGameObject*> m_children;
};