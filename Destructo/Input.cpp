#include "WindowsInput.h"
#include <Windows.h>

WindowsInput::WindowsInput()
{
}

WindowsInput::~WindowsInput()
{
}

bool WindowsInput::GetKeyDown(const EKeyCode a_key)
{
  return m_keyMap[a_key];
}

bool WindowsInput::GetKeyUp(const EKeyCode a_key)
{
  return !m_keyMap[a_key];
}

void WindowsInput::SetKeyDown(const EKeyCode a_key)
{
  m_keyMap[a_key] = true;
}

void WindowsInput::SetKeyUp(const EKeyCode a_key)
{
  m_keyMap[a_key] = false;
}
