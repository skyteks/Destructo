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
	app->ChangeRenderer(ERenderer::GDI);
}


void CUISystem::EventHandler_OnPressButtonOpenGL()
{
	app->ChangeRenderer(ERenderer::OpenGL);
}


void CUISystem::EventHandler_OnPressButtonDirectX11()
{
	app->ChangeRenderer(ERenderer::DirectX11);
}


void CUISystem::EventHandler_OnPressButtonDirect2D()
{
	app->ChangeRenderer(ERenderer::Direct2D);
}

void CUISystem::EventHandler_OnPressButtonGame()
{
	app->ChangeScene(EScenes::GAME);
}