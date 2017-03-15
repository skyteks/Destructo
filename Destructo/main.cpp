#include "CApplication.h"

CApplication* app = nullptr;

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{
	app = new CApplication();


	bool wResult = false;
	SRenderer::ERenderer chosenRenderer = SRenderer::DirectX11;
	wResult = app->InitializeApplication(chosenRenderer);
	if (!wResult)
		return false;

	app->Run();

	return true;
}
