#include "CApplication.h"
#include "CWindowsInput.h"
#include "CAudio.h"

CApplication* app = nullptr;

/// Install DirectX SDK 2010 https://www.microsoft.com/en-us/download/details.aspx?id=6812
/// Copy fmod.dll from Destructo\Middleware\fmod\api\lowlevel\lib into Destructo\Debug (same folder as program .exe)

/// Project Setting:

/// Change property of Shader.hlsl to "Not part of build"

/// Additional includes:
/// C:\Program Files(x86)\Microsoft DirectX SDK(June 2010)\Include
/// $(SolutionDir)Middleware\fmod\api\lowlevel\inc

/// Additional librarys:
/// C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x86
/// $(SolutionDir)Middleware\fmod\api\lowlevel\lib

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow)
{
    app = new CApplication();

    bool wResult = false;
    ERenderer chosenRenderer = ERenderer::OpenGL;
    wResult = app->Initialize(chosenRenderer, new CAudio(), new CWindowsInput());
    if (!wResult)
        return wResult;

    app->Run();

    app->Shutdown();

    delete app;

    return 1;
}