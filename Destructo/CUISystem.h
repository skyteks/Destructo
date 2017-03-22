#pragma once

class CUISystem
{
public:
	//static void EventHandler_OnPress();
	//static void EventHandler_OnHover();
	//static void EventHandler_OnNormal();

	static void EventHandler_OnPressButtonGDI();
	static void EventHandler_OnPressButtonOpenGL();
	static void EventHandler_OnPressButtonDirectX11();
	static void EventHandler_OnPressButtonDirect2D();
};

