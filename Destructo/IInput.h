#pragma once

#include "EKeyCode.h"

class IInput
{
public:
  virtual bool GetKeyDown(const EKeyCode a_key) = 0;
  virtual bool GetKeyUp(const EKeyCode a_key) = 0;

  virtual void SetKeyDown(const EKeyCode a_key) = 0;
  virtual void SetKeyUp(const EKeyCode a_key) = 0;

  virtual ~IInput() {};
};


//virtual void InitializeInput(void* m_windowHandle) = 0;

//virtual void Release() = 0;

//virtual bool IsKeyPressed(int key) = 0;

//virtual void Begin() = 0;

//virtual void End() = 0;