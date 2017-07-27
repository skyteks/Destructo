#pragma once

#include "EKeyCode.h"

class IInput
{
public:
    virtual bool GetKeyDown(const EKeyCode a_key) = 0;
    virtual bool GetKeyUp(const EKeyCode a_key) = 0;

    virtual void SetKeyDown(const EKeyCode a_key) = 0;
    virtual void SetKeyUp(const EKeyCode a_key) = 0;

    virtual bool GetKey(const EKeyCode a_key) = 0;

    virtual void Clear() = 0;

    virtual ~IInput() {};
};