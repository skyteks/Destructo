#include "CInputMouseAndKeyboard.h"



CInputMouseAndKeyboard::CInputMouseAndKeyboard()
{

}


CInputMouseAndKeyboard::~CInputMouseAndKeyboard()
{

}

void CInputMouseAndKeyboard::InitializeInput(void* a_windowHandle)
{

}

void CInputMouseAndKeyboard::Release()
{

}

bool CInputMouseAndKeyboard::IsKeyPressed(int a_key)
{
	return GetAsyncKeyState(a_key);
}

void CInputMouseAndKeyboard::Begin()
{

}

void CInputMouseAndKeyboard::End()
{

}
