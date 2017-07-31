#include "CGameObject.h"
#include "CTransform.h"

CGameObject::CGameObject()
    : m_name("New GameObject")
{
    AddComponent<CTransform>(this);
}


CGameObject::CGameObject(std::string a_name)
    : m_name(a_name)
{
    AddComponent<CTransform>(this);
}


CGameObject::~CGameObject()
{
}


void CGameObject::Initialize()
{
}


void CGameObject::Update()
{
    UpdateComponents();
}
