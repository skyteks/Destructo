#include "CInputManager.h"

CInputManager::CInputManager()
    : m_input(nullptr)
{
}

CInputManager::~CInputManager()
{
}

CInputManager& CInputManager::GetInstance()
{
    static CInputManager inputMgr;
    return inputMgr;
}

void CInputManager::SetInput(IInput* a_input)
{
    if (m_input)
    {
        SafeDelete(m_input);
    }

    m_input = a_input;
}

bool CInputManager::GetKeyDown(const EKeyCode a_key)
{
    return m_input->GetKeyDown(a_key);
}

bool CInputManager::GetKeyUp(const EKeyCode a_key)
{
    return m_input->GetKeyUp(a_key);
}

void CInputManager::SetKeyDown(const EKeyCode a_key)
{
    return m_input->SetKeyDown(a_key);
}

void CInputManager::SetKeyUp(const EKeyCode a_key)
{
    return m_input->SetKeyUp(a_key);
}

bool CInputManager::GetKey(const EKeyCode a_key)
{
    return m_input->GetKey(a_key);
}

void CInputManager::Clear()
{
    m_input->Clear();
}

void CInputManager::Initialize(IInput* a_input)
{
    SetInput(a_input);
}

void CInputManager::Shutdown()
{
    if (m_input)
    {
        SafeDelete(m_input);
    }
}
