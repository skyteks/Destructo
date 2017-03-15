#include "CApplication.h"

bool CApplication::engineRunning = false;
SRenderer::ERenderer CApplication::currentRenderer;

CApplication::CApplication()
	: window()
	, m_renderer(nullptr)
	, instance(GetModuleHandle(nullptr))
{

}


CApplication::~CApplication()
{

}


bool CApplication::InitializeApplication(SRenderer::ERenderer a_chosenRenderer)
{
	printf("Engine Start\n");

	bool wResult = false;

	// Create window
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(wc));
	wc.lpfnWndProc = CApplication::WndProc;
	wc.hInstance = instance;
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(HOLLOW_BRUSH));
	wc.lpszClassName = wndDesc.WindowName.c_str();
	wc.style = CS_VREDRAW | CS_HREDRAW;

	RegisterClass(&wc);

	wResult = window.InitializeWindow(wndDesc, this);
	if (!wResult)
		return false;

	// Create Renderer
	wResult = ChangeRenderer(a_chosenRenderer);
	if (!wResult)
		return false;

	// Create Scene
	wResult = ChangeScene();
	if (!wResult)
		return false;

	return true;
}


bool CApplication::ChangeScene()
{
	bool wResult = false;

	// Delete old scene, if One exists
	if (scene != nullptr)
	{
		scene->ShutdownScene();
		delete scene;
		scene = nullptr;
	}

	// Create a new scene
	scene = new CScene();
	wResult = scene->InitializeScene(m_renderer);
	if (!wResult)
		return false;

	return true;
}


bool CApplication::ChangeRenderer(SRenderer::ERenderer a_newRenderer)
{
	bool wResult = false;

	// Delete old renderer, if One exists
	if (m_renderer != nullptr)
	{
		m_renderer->ShutdownGraphics();
		delete m_renderer;
		m_renderer = nullptr;
	}

	// Create a new Renderer
	currentRenderer = a_newRenderer;
	switch (currentRenderer)
	{
	case SRenderer::GDI:
		m_renderer = new CRendererGDI();
		break;
	case SRenderer::DirectX11:
		m_renderer = new CRendererDirectX11();
		break;
	case SRenderer::OpenGL:
		m_renderer = new CRendererOpenGL();
		break;
	default:
		m_renderer = nullptr;
		return false;
	}

	wResult = this->m_renderer->InitializeGraphics(window.GetWindowHandle());
	if (!wResult)
		return false;

	return true;
}


void CApplication::Run()
{
	MSG message;
	engineRunning = true;

	// Start "Gameloop"
	while (engineRunning)
	{
		// Go trought all events
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		// Update everything inside the scene
		scene->Update();

		//Draw scene
		scene->Draw();

		Sleep(1);
	}

	// Delete Renderer for shutdown
	m_renderer->ShutdownGraphics();
	delete m_renderer;
	m_renderer = nullptr;
}


LRESULT CApplication::WndProc(HWND a_Hwnd, unsigned int a_Message, WPARAM a_WParam, LPARAM a_LPARAM)
{
	//CApplication* thiz = reinterpret_cast<CApplication*>(GetWindowLongPtr(a_Hwnd, GWLP_USERDATA));

	switch (a_Message)
	{
	case WM_CREATE:
	{
		LPCREATESTRUCT sr = reinterpret_cast<LPCREATESTRUCT>(a_LPARAM);
		SetWindowLongPtr(a_Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(sr->lpCreateParams));
		break;
	}
	case WM_MOUSEMOVE:
		CMouse::x = GET_X_LPARAM(a_LPARAM);
		CMouse::y = GET_Y_LPARAM(a_LPARAM);
		break;

	case WM_LBUTTONDOWN:
		CMouse::isLeftMouseDown = true;
		break;

	case WM_LBUTTONUP:
		CMouse::isLeftMouseDown = false;
		break;

	case WM_RBUTTONDOWN:
		CMouse::isRightMouseDown = true;
		break;

	case WM_RBUTTONUP:
		CMouse::isRightMouseDown = false;
		break;
	case WM_QUIT:
	case WM_DESTROY:
	case WM_CLOSE:
		printf("Engine stopped\n");
		PostQuitMessage(0);
		engineRunning = false;
		break;
	default:
		break;
	}

	return DefWindowProc(a_Hwnd, a_Message, a_WParam, a_LPARAM);
}


bool CApplication::Failed(HRESULT a_aResult)
{
	if (FAILED(a_aResult))
	{
		LPTSTR buffer;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, (DWORD)a_aResult, LANG_USER_DEFAULT, (LPTSTR)&buffer, 0, nullptr);

		MessageBox(0, buffer, TEXT("Fatal error"), MB_OK | MB_ICONERROR);
		LocalFree(buffer);
		return true;
	}
	return false;
}

//CreateMemoryDC