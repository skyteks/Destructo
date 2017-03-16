#include "CApplication.h"

bool CApplication::engineRunning = false;
SRenderer::ERenderer CApplication::currentRenderer;

CApplication::CApplication()
	: m_window()
	, m_renderer(nullptr)
	, m_instance(GetModuleHandle(nullptr))
	, m_soundEngine(nullptr)
	, m_timer(nullptr)
{

}


CApplication::~CApplication()
{

}


bool CApplication::Initialize(SRenderer::ERenderer a_chosenRenderer, ISoundEngine* a_soundEngine, IInput* a_input)
{
	printf("Engine Start\n");

	bool wResult = false;

	SetSoundEngine(a_soundEngine);
	CInputManager::GetInstance().Initialize(a_input);

	// Create m_window
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(wc));
	wc.lpfnWndProc = CApplication::WndProc;
	wc.hInstance = m_instance;
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(HOLLOW_BRUSH));
	wc.lpszClassName = m_wndDesc.WindowName.c_str();
	wc.style = CS_VREDRAW | CS_HREDRAW;

	RegisterClass(&wc);

	wResult = m_window.Initialize(m_wndDesc, this);
	if (!wResult)
		return false;

	// Create Timer
	m_timer = new CGameTimer();

	// Create Renderer
	wResult = ChangeRenderer(a_chosenRenderer);
	if (!wResult)
		return false;

	// initialize sound
	wResult = m_soundEngine->Initialize();
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

	// Delete old m_scene, if One exists
	if (m_scene != nullptr)
	{
		m_scene->Shutdown(m_soundEngine);
		SafeDelete(m_scene);
	}

	// Create newDeleteCounter new m_scene
	m_scene = new CScene();
	wResult = m_scene->Initialize(m_renderer, m_timer);
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
		m_renderer->Shutdown();
		SafeDelete(m_renderer);
	}

	// Create newDeleteCounter new Renderer
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

	wResult = this->m_renderer->Initialize(m_window.GetWindowHandle());
	if (!wResult)
		return false;

	if (m_scene != nullptr)
		m_scene->Initialize(m_renderer, m_timer);

	return true;
}


void CApplication::Run()
{
	MSG message;
	engineRunning = true;

	  // Start "Gameloop"
	while (engineRunning)
	{
		// A new frame has started, so do a tick
		m_timer->Tick();
		// Go trought all events
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		// Update everything inside the m_scene
		m_scene->Update();

		// update sound system
		m_soundEngine->Update();

		//Draw m_scene
		m_scene->Draw(m_renderer);

		//Sleep(1);
	}
}

void CApplication::Shutdown()
{
	m_scene->Shutdown(m_soundEngine);

	m_renderer->Shutdown();
	SafeDelete(m_scene);
	SafeDelete(m_renderer);

	; // unload sound from memory
	m_soundEngine->Shutdown(); // shutdown sound engine
	SafeDelete(m_soundEngine); // delete sound engine

	CInputManager::GetInstance().Shutdown();

	SafeDelete(m_timer);
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

	case WM_KEYDOWN:
		CInputManager::GetInstance().SetKeyDown(static_cast<EKeyCode>(a_WParam));
		break;

	case WM_KEYUP:
		CInputManager::GetInstance().SetKeyUp(static_cast<EKeyCode>(a_WParam));
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

void CApplication::SetSoundEngine(ISoundEngine * a_soundEngine)
{
	if (a_soundEngine == nullptr)
	{
		return;
	}

	if (m_soundEngine)
	{
		SafeDelete(m_soundEngine);
	}

	m_soundEngine = a_soundEngine;
}

//CreateMemoryDC