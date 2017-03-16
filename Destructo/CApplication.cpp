#include "CApplication.h"

bool CApplication::engineRunning = false;
SRenderer::ERenderer CApplication::currentRenderer;

CApplication::CApplication()
	: window()
	, m_renderer(nullptr)
	, instance(GetModuleHandle(nullptr))
  , m_soundEngine(nullptr)
{

}


CApplication::~CApplication()
{

}


bool CApplication::InitializeApplication(SRenderer::ERenderer a_chosenRenderer, ISoundEngine* a_soundEngine, IInput* a_input)
{
	printf("Engine Start\n");

	bool wResult = false;

  SetSoundEngine(a_soundEngine);
  InputManager::GetInstance().Initialize(a_input);

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

  // initialize sound
  m_soundEngine->Initialize();

	return true;
}


bool CApplication::ChangeScene()
{
	bool wResult = false;

	// Delete old m_scene, if One exists
	if (m_scene != nullptr)
	{
		m_scene->ShutdownScene();
		SafeDelete(m_scene);
	}

	// Create newDeleteCounter new m_scene
	m_scene = new CScene();
	wResult = m_scene->InitializeScene(m_renderer);
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

	wResult = this->m_renderer->InitializeGraphics(window.GetWindowHandle());
	if (!wResult)
		return false;

	return true;
}


void CApplication::Run()
{
	MSG message;
	engineRunning = true;

  // just a sound-test
  auto sound = m_soundEngine->LoadSound("Audio\\throw.mp3"); // load sound into memory

	// Start "Gameloop"
	while (engineRunning)
	{
		// Go trought all events
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
    
		// Update everything inside the m_scene
    if (InputManager::GetInstance().GetKeyDown(EKeyCode::A))
    {
      m_soundEngine->PlaySoundOneShot(sound);
    }

		m_scene->Update();

    // update sound system
    m_soundEngine->Update();

		//Draw m_scene
		m_scene->Draw(m_renderer);

		Sleep(1);
	}

	// Delete Renderer for shutdown
	m_scene->ShutdownScene();
	m_renderer->ShutdownGraphics();
	SafeDelete(m_scene);
	SafeDelete(m_renderer);

  m_soundEngine->UnloadSound(sound); // unload sound from memory
  m_soundEngine->Shutdown(); // shutdown sound engine
  SafeDelete(m_soundEngine); // delete sound engine

  InputManager::GetInstance().Shutdown();
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
    InputManager::GetInstance().SetKeyDown(static_cast<EKeyCode>(a_WParam));
    break;

  case WM_KEYUP:
    InputManager::GetInstance().SetKeyUp(static_cast<EKeyCode>(a_WParam));
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