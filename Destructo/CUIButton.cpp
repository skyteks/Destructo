#include "CUIButton.h"

CUIButton::CUIButton()
{
	m_bitmap = nullptr;
}

CUIButton::CUIButton(ITexture* a_bitmap, const SRect& a_size)
	: m_bitmap(a_bitmap)
	, m_size(a_size)
	, m_state(EButtonState::OnNormal)
	, m_lastState(EButtonState::OnNormal)
{
}

CUIButton::CUIButton(ITexture* a_bitmap, const SRect& a_size, ButtonMap& a_map)
	: m_bitmap(a_bitmap)
	, m_size(a_size)
	, m_state(EButtonState::OnNormal)
	, m_lastState(EButtonState::OnNormal)
{
	m_buttonMap = a_map;
}

void CUIButton::SetState(EButtonState a_state)
{
	// don't do anything if the new state is the same as last frame
	if (a_state == m_lastState)
	{
		return;
	}

	m_state = a_state;

	switch (m_lastState)
	{
	case EButtonState::OnPress:
		if (CMouse::isLeftMouseDown == false)
		{
			HandleCallback(m_lastState);
		}
		break;
	case EButtonState::OnHover:
		HandleCallback(m_lastState);
		break;
	case EButtonState::OnNormal:
		HandleCallback(m_lastState);
		break;
	default:
		break;
	}

	m_lastState = m_state;
}
void CUIButton::SetButtonMap(ButtonMap& a_map)
{
	m_buttonMap = a_map;
}
void CUIButton::UpdateState()
{
	if (CMouse::isLeftMouseDown)// || CMouse::isRightMouseDown)
	{
		if (IsMouseHovering())
		{
			SetState(EButtonState::OnPress);
		}
		else
		{
			SetState(EButtonState::OnNormal);
		}
	}
	else if (IsMouseHovering())
	{
		SetState(EButtonState::OnHover);
	}
	else
	{
		SetState(EButtonState::OnNormal);
	}
}
ITexture * CUIButton::GetTexture()
{
	return m_bitmap;
}
SRect CUIButton::GetDestination()
{
	return m_size;
}
SRect CUIButton::GetSource()
{
	return m_buttonMap[m_state].m_rect;
}
bool CUIButton::IsMouseHovering()
{
	if (CMouse::x >= m_size.m_x1 && CMouse::x <= (m_size.m_x1 + m_size.m_x2) &&
		CMouse::y >= m_size.m_y1 && CMouse::y <= (m_size.m_y1 + m_size.m_y2))
	{
		return true;
	}

	return false;
}
void CUIButton::HandleCallback(EButtonState a_state)
{
	auto m_callback = m_buttonMap[a_state].m_callback;
	if (m_callback)
	{
		m_callback();
	}
}
