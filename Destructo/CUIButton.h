#pragma once


#include "ITexture.h"
#include "CMouse.h"
#include "EButtonState.h"
#include "SButtonData.h"
#include "SRect.h"

class CUIButton
{
public:
    CUIButton();
    CUIButton(const ITexture* a_bitmap, const SRect<float>& a_size);
    CUIButton(const ITexture* a_bitmap, const SRect<float>& a_size, ButtonMap& a_map);
    void SetState(EButtonState a_state);
    void SetButtonMap(ButtonMap& a_map);
    void UpdateState();
    const ITexture& GetTexture() const;
    const SRect<float>& GetDestination() const;
    const SRect<float>& GetSource() const;

private:
    bool IsMouseHovering();
    void HandleCallback(EButtonState a_state);
    EButtonState m_state;
    EButtonState m_lastState;
    ButtonMap m_buttonMap;
    const ITexture* m_bitmap = nullptr;
    SRect<float> m_size;
};
