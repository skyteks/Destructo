#include "CGameObject.h"
#include "CTransform.h"

CGameObject::CGameObject()
    //: m_name("New GameObject")
{
    Initialize();
}


//CGameObject::CGameObject(std::string a_name)
//    : m_name(a_name)
//{
//    Initialize();
//}


CGameObject::~CGameObject()
{
}


void CGameObject::Initialize()
{
    AddComponent<CTransform>(this);
}


void CGameObject::Update()
{
    UpdateComponents();
}
