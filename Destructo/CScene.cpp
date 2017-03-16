#include "CScene.h"



CScene::CScene()
	: m_backgroundTexture(nullptr)
	, m_collisionTexture(nullptr)
	, m_terrainTexture(nullptr)
	, m_playerTexture(nullptr)
	, m_buttonTexture(nullptr)
	, m_fontTexture(nullptr)
	, m_timer(nullptr)
	, m_soundEngine(nullptr)
{
}


CScene::~CScene()
{
}


bool CScene::Initialize(IRenderer* a_renderer, CGameTimer* a_timer)
{
	m_timer = a_timer;

	LoadTextures(a_renderer);
	LoadButtons();

	return true;
}


void CScene::Update()
{
	m_uiButtonGDI.UpdateState();
	m_uiButtonOpenGL.UpdateState();
	m_uiButtonDirectX11.UpdateState();

	float speed = 100 * m_timer->DeltaTime();

	if (m_playerPosX < 800 - 32 && CInputManager::GetInstance().GetKeyDown(EKeyCode::D))
		m_playerPosX += static_cast<int>(speed);
	if (m_playerPosX >= 0 && CInputManager::GetInstance().GetKeyDown(EKeyCode::A))
		m_playerPosX -= static_cast<int>(speed);
	if (m_playerPosY < 600 - 32 && CInputManager::GetInstance().GetKeyDown(EKeyCode::S))
		m_playerPosY += static_cast<int>(speed);
	if (m_playerPosY >= 0 && CInputManager::GetInstance().GetKeyDown(EKeyCode::W))
		m_playerPosY -= static_cast<int>(speed);

	//m_arrowPosX = CMouse::x;
	//m_arrowPosY = CMouse::y;
}


void CScene::Draw(IRenderer* a_renderer)
{
	if (a_renderer != nullptr)
	{
		a_renderer->Begin();

		a_renderer->DrawTexture(0, 0, 800, 600, m_backgroundTexture, 0, 0, m_backgroundTexture->GetWidth(), m_backgroundTexture->GetHeight());
		a_renderer->DrawTexture(0, 0, 800, 600, m_terrainTexture, 0, 0, m_terrainTexture->GetWidth(), m_terrainTexture->GetHeight());
		a_renderer->DrawTexture(m_playerPosX, m_playerPosY, 32, 32, m_playerTexture, 0, 0, m_playerTexture->GetWidth(), m_playerTexture->GetHeight());
		a_renderer->DrawTexture(0, 0, 0, 0, m_buttonTexture, 0, 0, 0, 0);

		a_renderer->DrawTexture(m_uiButtonGDI.GetDestination().m_x, m_uiButtonGDI.GetDestination().m_y, m_uiButtonGDI.GetDestination().m_width, m_uiButtonGDI.GetDestination().m_height, m_uiButtonGDI.GetTexture(), m_uiButtonGDI.GetSource().m_x, m_uiButtonGDI.GetSource().m_y, m_uiButtonGDI.GetSource().m_width, m_uiButtonGDI.GetSource().m_height);
		a_renderer->DrawTexture(m_uiButtonOpenGL.GetDestination().m_x, m_uiButtonOpenGL.GetDestination().m_y, m_uiButtonOpenGL.GetDestination().m_width, m_uiButtonOpenGL.GetDestination().m_height, m_uiButtonOpenGL.GetTexture(), m_uiButtonOpenGL.GetSource().m_x, m_uiButtonOpenGL.GetSource().m_y, m_uiButtonOpenGL.GetSource().m_width, m_uiButtonOpenGL.GetSource().m_height);
		a_renderer->DrawTexture(m_uiButtonDirectX11.GetDestination().m_x, m_uiButtonDirectX11.GetDestination().m_y, m_uiButtonDirectX11.GetDestination().m_width, m_uiButtonDirectX11.GetDestination().m_height, m_uiButtonDirectX11.GetTexture(), m_uiButtonDirectX11.GetSource().m_x, m_uiButtonDirectX11.GetSource().m_y, m_uiButtonDirectX11.GetSource().m_width, m_uiButtonDirectX11.GetSource().m_height);

		a_renderer->DrawString(110, 540, "GDI", RGB(255, 0, 0), RGB(0, 0, 0), DT_TOP | DT_LEFT, m_fontTexture);
		a_renderer->DrawString(310, 540, "OpenGL", RGB(0, 255, 0), RGB(0, 0, 0), DT_TOP | DT_LEFT, m_fontTexture);
		a_renderer->DrawString(510, 540, "DirectX", RGB(0, 0, 255), RGB(0, 0, 0), DT_TOP | DT_LEFT, m_fontTexture);
		char buffer[200] = {};
		sprintf_s(buffer, "MouseX: %i\nMouseY: %i\nMouseL: %s\nMouseR: %s\nFPS: %i", CMouse::x, CMouse::y, CMouse::isLeftMouseDown ? "true" : "false", CMouse::isRightMouseDown ? "true" : "false", static_cast<int>(1 / m_timer->DeltaTime()));
		a_renderer->DrawString(10, 10, buffer, RGB(255, 255, 255), RGB(0, 0, 0), DT_TOP | DT_LEFT, m_fontTexture);

		a_renderer->End();
	}
}


void CScene::LoadButtons()
{
	m_buttonMapButtonGDI.insert(ButtonPair(EButtonState::OnNormal, SButtonData{ 0, 0, 127, 38, nullptr })); // x,y,width,height from source
	m_buttonMapButtonGDI.insert(ButtonPair(EButtonState::OnHover, SButtonData{ 0, 40, 127, 38, nullptr })); // x,y,width,height from source
	m_buttonMapButtonGDI.insert(ButtonPair(EButtonState::OnPress, SButtonData{ 0, 80, 127, 38, CUISystem::EventHandler_OnPressButtonGDI })); // x,y,width,height from source
	m_uiButtonGDI = CUIButton(m_buttonTexture, { 100, 530, 127, 38 }, m_buttonMapButtonGDI); // x, y, width, height for dest

	m_buttonMapButtonOpenGL.insert(ButtonPair(EButtonState::OnNormal, SButtonData{ 0, 0, 127, 38, nullptr })); // m_x,y,width,height from source
	m_buttonMapButtonOpenGL.insert(ButtonPair(EButtonState::OnHover, SButtonData{ 0, 40, 127, 38, nullptr })); // m_x,y,width,height from source
	m_buttonMapButtonOpenGL.insert(ButtonPair(EButtonState::OnPress, SButtonData{ 0, 80, 127, 38, CUISystem::EventHandler_OnPressButtonOpenGL })); // x,y,width,height from source
	m_uiButtonOpenGL = CUIButton(m_buttonTexture, { 300, 530, 127, 38 }, m_buttonMapButtonOpenGL); // x, y, width, height for dest

	m_buttonMapButtonDirectX11.insert(ButtonPair(EButtonState::OnNormal, SButtonData{ 0, 0, 127, 38, nullptr })); // x,y,width,height from source
	m_buttonMapButtonDirectX11.insert(ButtonPair(EButtonState::OnHover, SButtonData{ 0, 40, 127, 38, nullptr })); // x,y,width,height from source
	m_buttonMapButtonDirectX11.insert(ButtonPair(EButtonState::OnPress, SButtonData{ 0, 80, 127, 38, CUISystem::EventHandler_OnPressButtonDirectX11 })); // x,y,width,height from source
	m_uiButtonDirectX11 = CUIButton(m_buttonTexture, { 500, 530, 127, 38 }, m_buttonMapButtonDirectX11); // x, y, width, height for dest
}


void CScene::LoadTextures(IRenderer* a_renderer)
{
	ReleaseTextures();

	m_backgroundTexture = a_renderer->LoadTextureFromFile("Textures/background.bmp");//("Textures/goblin.bmp");
	m_collisionTexture = a_renderer->LoadTextureFromFile("Textures/collision.bmp");
	m_terrainTexture = a_renderer->LoadTextureFromFile("Textures/terrain.bmp");
	m_playerTexture = a_renderer->LoadTextureFromFile("Textures/player.bmp");

	m_buttonTexture = a_renderer->LoadTextureFromFile("Textures/button.bmp");
	m_fontTexture = a_renderer->LoadTextureFromFile("Textures/font.bmp");
}

void CScene::LoadSounds(ISoundEngine * a_soundEngine)
{
	// just a sound-test
	m_testSound = m_soundEngine->LoadSound("Audio/throw.mp3"); // load sound into memory
}


void CScene::ReleaseTextures()
{
	SafeDelete(m_backgroundTexture);
	SafeDelete(m_collisionTexture);
	SafeDelete(m_terrainTexture);
	SafeDelete(m_playerTexture);
	SafeDelete(m_buttonTexture);
	SafeDelete(m_fontTexture);
}

void CScene::ReleaseSound(ISoundEngine* a_soundEngine)
{
	a_soundEngine->UnloadSound(m_testSound);
}


void CScene::Shutdown(ISoundEngine* a_soundEngine)
{
	ReleaseTextures();
	ReleaseSound(a_soundEngine);
}
