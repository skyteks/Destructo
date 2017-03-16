#pragma once

#include "IInput.h"
#include "GlobalFunctions.h"

// InputManager can contain different IInputs, for example windows, linux, or mac,...
// He is basically just a wrapper and holds the correct InputSystem for the current platform

class InputManager : public IInput
{
public:
  InputManager();
  ~InputManager();

  void Initialize(IInput* a_input);
  void Shutdown();

  static InputManager& GetInstance();
  void SetInput(IInput* a_input);

  bool GetKeyDown(const EKeyCode a_key) override;
  bool GetKeyUp(const EKeyCode a_key) override;
  void SetKeyDown(const EKeyCode a_key) override;
  void SetKeyUp(const EKeyCode a_key) override;


private:
  InputManager(const InputManager&);

  IInput* m_input;
};
