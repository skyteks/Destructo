#include "CWindow.h"

CWindow::CWindow()
    : m_hwnd()
{

}


CWindow::~CWindow()
{

}

bool CWindow::Initialize(const SWindowDesc& a_windowDesc, CApplication* a_application)
{
    RECT m_rect = { 0,0,a_windowDesc.x2, a_windowDesc.y2 };
    const int windowStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_BORDER | WS_VISIBLE;
    AdjustWindowRect(&m_rect, windowStyle, false);

    this->m_hwnd = CreateWindow(
        a_windowDesc.WindowName.c_str(),
        a_windowDesc.WindowName.c_str(),
        windowStyle,
        20, 20,
        m_rect.right - m_rect.left, m_rect.bottom - m_rect.top,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        a_application);

    SetForegroundWindow(this->m_hwnd);
    SetFocus(this->m_hwnd);

    RECT r = {};

    GetClientRect(this->m_hwnd, &r);

    if (this->m_hwnd == nullptr)
        return false;

    return true;
}

HWND CWindow::GetWindowHandle()
{
    return this->m_hwnd;
}