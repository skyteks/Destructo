#include "CGameObject.h"
#include "CTransform.h"

CGameObject::CGameObject()
    : m_name("New GameObject")
    , m_parent(nullptr)
    , m_children()
{
    AddComponent<CTransform>(this);
}


CGameObject::CGameObject(std::string a_name)
    : m_name(a_name)
    , m_parent(nullptr)
    , m_children()
{
    AddComponent<CTransform>(this);
}


CGameObject::~CGameObject()
{
}


void CGameObject::Update()
{
    UpdateComponents();
}

const CGameObject* CGameObject::GetRoot() const
{
    return (m_parent == nullptr ? this : m_parent->GetRoot());
}

const CGameObject* CGameObject::GetParent() const
{
    return m_parent;
}

void CGameObject::SetParent(CGameObject* a_parent)
{
    m_parent = a_parent;
    m_parent->m_children.push_back(this);
}
