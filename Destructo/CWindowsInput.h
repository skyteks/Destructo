#pragma once

#include <unordered_map>

#include "IInput.h"

class CWindowsInput : public IInput
{
public:
	CWindowsInput();
	~CWindowsInput();

	bool GetKeyDown(const EKeyCode a_key) override;
	bool GetKeyUp(const EKeyCode a_key) override;

	void SetKeyDown(const EKeyCode a_key) override;
	void SetKeyUp(const EKeyCode a_key) override;

private:
	std::unordered_map<EKeyCode, bool> m_keyMap; // down = true, up = false
};