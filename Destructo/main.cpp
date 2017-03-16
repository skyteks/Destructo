#include "CApplication.h"

#include "CSoundEngine.h"
#include "CWindowsInput.h"

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
	wResult = app->Initialize(chosenRenderer, new CSoundEngine(), new CWindowsInput());
	if (!wResult)
		return false;

	app->Run();

	app->Shutdown();

	delete app;

	return true;
}
