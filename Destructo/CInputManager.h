#pragma once

#include "IInput.h"
#include "GlobalFunctions.h"

// CInputManager can contain different IInputs, for example windows, linux, or mac,...
// He is basically just a wrapper and holds the correct InputSystem for the current platform

class CInputManager : public IInput
{
public:
    CInputManager();
    ~CInputManager();

    void Initialize(IInput* a_input);
    void Shutdown();

    static CInputManager& GetInstance();
    void SetInput(IInput* a_input);

    bool GetKeyDown(const EKeyCode a_key) override;
    bool GetKeyUp(const EKeyCode a_key) override;
    void SetKeyDown(const EKeyCode a_key) override;
    void SetKeyUp(const EKeyCode a_key) override;

    bool GetKey(const EKeyCode a_key) override;

    void Clear() override;

private:
    CInputManager(const CInputManager&);

    IInput* m_input;
};
