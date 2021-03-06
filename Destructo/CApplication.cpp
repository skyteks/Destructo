﻿#include "CApplication.h"

bool CApplication::s_engineRunning = false;

CApplication::CApplication()
    : m_currentRenderer(ERenderer::NONE)
    , m_wndDesc({"Destructo", 800, 600 })
    , m_window()
    , m_instance(GetModuleHandle(nullptr))
{
}


CApplication::~CApplication()
{
}


bool CApplication::Initialize(ERenderer a_chosenRenderer, IAudio* a_soundEngine, IInput* a_input)
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

    // initialize texture manager
    CTextureManager::GetInstance().Initialize(&m_renderer);

    // Create Renderer
    wResult = ChangeRenderer(a_chosenRenderer);
    if (!wResult)
        return false;

    // initialize sound
    wResult = m_soundEngine->Initialize();
    if (!wResult)
        return false;

    // Create Scene
    wResult = ChangeScene(EScenes::MENU);
    if (!wResult)
        return false;

    return true;
}


bool CApplication::ChangeScene(EScenes a_newScene)
{
    bool wResult = false;

    // Delete old m_scene, if One exists
    if (m_scene != nullptr)
    {
        m_scene->Shutdown();
        SafeDelete(m_scene);
    }

    // Create newDeleteCounter new m_scene
    switch (a_newScene)
    {
    case MENU:
        m_scene = new CMenuScene();
        break;
    case GAME:
        m_scene = new CGameScene();
        break;
    default:
        break;
    }

    wResult = m_scene->Initialize(*m_renderer);
    if (!wResult)
        return false;

    return true;
}


bool CApplication::ChangeRenderer(ERenderer a_newRenderer)
{
    bool wResult = false;

    // Delete old renderer, if One exists
    if (m_renderer != nullptr)
    {
        CTextureManager::GetInstance().Shutdown();
        m_renderer->Shutdown();
        SafeDelete(m_renderer);
    }


    // Create newDeleteCounter new Renderer
    m_currentRenderer = a_newRenderer;

    switch (m_currentRenderer)
    {
    case GDI:
        m_renderer = new CRendererGDI();
        break;
    case OpenGL:
        m_renderer = new CRendererOpenGL();
        break;
    case DirectX11:
        m_renderer = new CRendererDirectX11();
        break;
    case Direct2D:
        m_renderer = new CRendererDirect2D();
        break;
    default:
        return false;
    }

    wResult = this->m_renderer->Initialize(m_window.GetWindowHandle());
    if (!wResult)
        return false;

    if (m_scene != nullptr)
        m_scene->Initialize(*m_renderer);

    return true;
}


void CApplication::Run()
{
    MSG message;
    s_engineRunning = true;

    CTime::GetInstance().Reset();
    float totalTime = CTime::GetInstance().TotalTime();
    const uint32_t capFPS = 1000;
    uint32_t currentFPS = 0;

    float frameTime = 1.0f / capFPS;


    m_soundEngine->Load("Audio/Throw.mp3");
    m_soundEngine->Load("Audio/t.mp3");

    CGameTimer m_timer;
    m_timer.Reset();

    CGameTimer deltaTimer;
    deltaTimer.Reset();

    // Start "Gameloop"
    while (s_engineRunning)
    {
        // Go trought all events
        while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        if (CInputManager::GetInstance().GetKeyDown(EKeyCode::Escape))
        {
            auto channel = m_soundEngine->Play("Audio/Throw.mp3");
            //channel->SetPitch(2.0f); // funny how this changes the sound lol try 10, 50, 100
            channel->SetVolume(0.4f);
        }

        if (CInputManager::GetInstance().GetKeyDown(EKeyCode::x))
        {
            auto channel = m_soundEngine->Play("Audio/t.mp3");
            //channel->SetPitch(5.0f); // funny how this changes the sound lol try 10, 50, 100
            channel->SetVolume(0.6f);
        }

        // Update everything inside the scene
        m_scene->Update();

        // update sound system
        m_soundEngine->Update();

        // Draw scene
        m_renderer->Begin();
        m_scene->Draw(*m_renderer);
        m_renderer->End();

        deltaTimer.Tick();
        CTime::GetInstance().SetDeltaTime(deltaTimer.DeltaTime());

        m_timer.Tick();
        m_timer.Pause();
        if (m_timer.DeltaTime() < frameTime)
        {
            float currentTime = CTime::GetInstance().TotalTime();

            float sleep = abs(frameTime - m_timer.DeltaTime());

            while (CTime::GetInstance().TotalTime() - currentTime < sleep)
            {
                // wait
                //Sleep(static_cast<DWORD>(sleep));
            }
        }

        CTime::GetInstance().Tick();
        m_timer.Unpause();
        CInputManager::GetInstance().Clear();
    }
}

void CApplication::Shutdown()
{
    m_scene->Shutdown();

    CTextureManager::GetInstance().Shutdown();

    m_renderer->Shutdown();
    SafeDelete(m_scene);
    SafeDelete(m_renderer);

    // unload sound from memory
    m_soundEngine->Shutdown(); // shutdown sound engine
    SafeDelete(m_soundEngine); // delete sound engine

    CInputManager::GetInstance().Shutdown();

    s_engineRunning = false;
}


LRESULT CApplication::WndProc(HWND a_Hwnd, uint32_t a_Message, WPARAM a_WParam, LPARAM a_LPARAM)
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
    {
        bool isBitSet = a_LPARAM & (1 << 30); // if bit 30 is set in lparam then it is a repeadingly message, which must be ignored.
        if (isBitSet)
        {
            break;
        }
        else
        {
            CInputManager::GetInstance().SetKeyDown(static_cast<EKeyCode>(a_WParam));
            break;
        }
    }

    case WM_KEYUP:
    {
        bool isBitSet = a_LPARAM & (1 << 30); // not required, but is fine... WM_KEYUP only occoures once
        if (isBitSet)
        {
            CInputManager::GetInstance().SetKeyUp(static_cast<EKeyCode>(a_WParam));
        }
        break;
    }

    case WM_QUIT:
    case WM_DESTROY:
    case WM_CLOSE:
        printf("Engine stopped\n");
        PostQuitMessage(0);
        s_engineRunning = false;
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

void CApplication::SetSoundEngine(IAudio* a_soundEngine)
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