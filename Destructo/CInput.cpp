#include "CWindowsInput.h"
#include <Windows.h>

CWindowsInput::CWindowsInput()
{
}

CWindowsInput::~CWindowsInput()
{
}

bool CWindowsInput::GetKeyDown(const EKeyCode a_key)
{
  return m_keyMap[a_key];
}

bool CWindowsInput::GetKeyUp(const EKeyCode a_key)
{
  return !m_keyMap[a_key];
}

void CWindowsInput::SetKeyDown(const EKeyCode a_key)
{
  m_keyMap[a_key] = true;
}

void CWindowsInput::SetKeyUp(const EKeyCode a_key)
{
  m_keyMap[a_key] = false;
}
