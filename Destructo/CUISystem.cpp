#include "CUISystem.h"
#include <Windows.h>
#include "CApplication.h"

//void CUISystem::EventHandler_OnPress()
//{
//	//__asm
//	//{
//	//  int 3
//	//}
//}
//
//
//void CUISystem::EventHandler_OnHover()
//{
//
//}
//
//
//void CUISystem::EventHandler_OnNormal()
//{
//
//}

extern CApplication* app;

void CUISystem::EventHandler_OnPressButtonGDI()
{
	app->ChangeRenderer(SRenderer::GDI);
}


void CUISystem::EventHandler_OnPressButtonOpenGL()
{
	app->ChangeRenderer(SRenderer::OpenGL);
}


void CUISystem::EventHandler_OnPressButtonDirectX11()
{
	app->ChangeRenderer(SRenderer::DirectX11);
}