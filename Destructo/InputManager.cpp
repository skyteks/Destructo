#include "InputManager.h"

InputManager::InputManager()
  : m_input(nullptr)
{
}

InputManager::~InputManager()
{
}

InputManager& InputManager::GetInstance()
{
  static InputManager inputMgr;
  return inputMgr;
}

void InputManager::SetInput(IInput * a_input)
{
  if (m_input)
  {
    SafeDelete(m_input);
  }

  m_input = a_input;
}

bool InputManager::GetKeyDown(const EKeyCode a_key)
{
  return m_input->GetKeyDown(a_key);
}

bool InputManager::GetKeyUp(const EKeyCode a_key)
{
  return m_input->GetKeyUp(a_key);
}

void InputManager::SetKeyDown(const EKeyCode a_key)
{
  return m_input->SetKeyDown(a_key);
}

void InputManager::SetKeyUp(const EKeyCode a_key)
{
  return m_input->SetKeyUp(a_key);
}

void InputManager::Initialize(IInput * a_input)
{
  SetInput(a_input);
}

void InputManager::Shutdown()
{
  if (m_input)
  {
    SafeDelete(m_input);
  }
}
