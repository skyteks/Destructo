#include "CScene.h"

#include "CRendererGDI.h"

CScene::CScene()
	: m_backgroundTexture(nullptr)
	, m_collisionTexture(nullptr)
	, m_terrainTexture(nullptr)
	, m_playerTexture(nullptr)
	, m_buttonTexture(nullptr)
	, m_fontTexture(nullptr)
{
}


CScene::~CScene()
{
}


bool CScene::Initialize(IRenderer* a_renderer)
{
	LoadTextures(a_renderer);
	LoadButtons();

	return true;
}


void CScene::Update()
{
	m_uiButtonGDI.UpdateState();
	m_uiButtonOpenGL.UpdateState();
	m_uiButtonDirectX11.UpdateState();
	m_uiButtonDirect2D.UpdateState();

	speed = 500 * CTime::GetInstance().DeltaTime();

	if (m_playerPosX < 800 - 32 && CInputManager::GetInstance().GetKeyDown(EKeyCode::D))
		m_playerPosX += static_cast<int>(speed);
	if (m_playerPosX >= 0 && CInputManager::GetInstance().GetKey(EKeyCode::A))
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

		//if (CMouse::isLeftMouseDown)
		//{
		//	reinterpret_cast<CRendererGDI*>(a_renderer)->MakeCircleInTexture(CMouse::x, CMouse::y, (CTextureGDI*)m_terrainTexture, 255, 20);
		//}

		a_renderer->DrawTexture(0, 0, 800, 600, m_backgroundTexture, 0, 0, m_backgroundTexture->GetWidth(), m_backgroundTexture->GetHeight());
		a_renderer->DrawTexture(0, 0, 800, 600, m_terrainTexture, 0, 0, m_terrainTexture->GetWidth(), m_terrainTexture->GetHeight());
		a_renderer->DrawTexture(m_playerPosX, m_playerPosY, 32, 32, m_playerTexture, 0, 0, m_playerTexture->GetWidth(), m_playerTexture->GetHeight());
		a_renderer->DrawTexture(0, 0, 0, 0, m_buttonTexture, 0, 0, 0, 0);

		a_renderer->DrawTexture(m_uiButtonGDI.GetDestination().x1, m_uiButtonGDI.GetDestination().y1, m_uiButtonGDI.GetDestination().x2, m_uiButtonGDI.GetDestination().y2, m_uiButtonGDI.GetTexture(), m_uiButtonGDI.GetSource().x1, m_uiButtonGDI.GetSource().y1, m_uiButtonGDI.GetSource().x2, m_uiButtonGDI.GetSource().y2);
		a_renderer->DrawTexture(m_uiButtonOpenGL.GetDestination().x1, m_uiButtonOpenGL.GetDestination().y1, m_uiButtonOpenGL.GetDestination().x2, m_uiButtonOpenGL.GetDestination().y2, m_uiButtonOpenGL.GetTexture(), m_uiButtonOpenGL.GetSource().x1, m_uiButtonOpenGL.GetSource().y1, m_uiButtonOpenGL.GetSource().x2, m_uiButtonOpenGL.GetSource().y2);
		a_renderer->DrawTexture(m_uiButtonDirectX11.GetDestination().x1, m_uiButtonDirectX11.GetDestination().y1, m_uiButtonDirectX11.GetDestination().x2, m_uiButtonDirectX11.GetDestination().y2, m_uiButtonDirectX11.GetTexture(), m_uiButtonDirectX11.GetSource().x1, m_uiButtonDirectX11.GetSource().y1, m_uiButtonDirectX11.GetSource().x2, m_uiButtonDirectX11.GetSource().y2);
		a_renderer->DrawTexture(m_uiButtonDirect2D.GetDestination().x1, m_uiButtonDirect2D.GetDestination().y1, m_uiButtonDirect2D.GetDestination().x2, m_uiButtonDirect2D.GetDestination().y2, m_uiButtonDirect2D.GetTexture(), m_uiButtonDirect2D.GetSource().x1, m_uiButtonDirect2D.GetSource().y1, m_uiButtonDirect2D.GetSource().x2, m_uiButtonDirect2D.GetSource().y2);

		a_renderer->DrawString(100 + 10, 530 + 10, "GDI", RGB(255, 0, 0), RGB(0, 0, 0), DT_TOP | DT_LEFT, m_fontTexture);
		a_renderer->DrawString(266 + 10, 530 + 10, "OpenGL", RGB(0, 255, 0), RGB(0, 0, 0), DT_TOP | DT_LEFT, m_fontTexture);
		a_renderer->DrawString(433 + 10, 530 + 10, "DirectX", RGB(0, 0, 255), RGB(0, 0, 0), DT_TOP | DT_LEFT, m_fontTexture);
		a_renderer->DrawString(600 + 10, 530 + 10, "Direct2D", RGB(0, 0, 255), RGB(0, 0, 0), DT_TOP | DT_LEFT, m_fontTexture);
		char buffer[200] = {};
		sprintf_s(buffer, "MouseX: %i\nMouseY: %i\nMouseL: %s\nMouseR: %s\nFPS: %i\nSpeed: %f", CMouse::x, CMouse::y, CMouse::isLeftMouseDown ? "true" : "false", CMouse::isRightMouseDown ? "true" : "false", static_cast<int>(1 / CTime::GetInstance().DeltaTime()), speed);
		a_renderer->DrawString(10, 10, buffer, RGB(255, 255, 255), RGB(0, 0, 0), DT_TOP | DT_LEFT, m_fontTexture);

		a_renderer->End();
	}
}


void CScene::LoadButtons()
{
	m_buttonMapButtonGDI.insert(ButtonPair(EButtonState::OnNormal, SButtonData{ 0, 0, 127, 38, nullptr })); // x,y,width,height from source
	m_buttonMapButtonGDI.insert(ButtonPair(EButtonState::OnHover, SButtonData{ 0, 40, 127, 38, nullptr })); // x,y,width,height from source
	m_buttonMapButtonGDI.insert(ButtonPair(EButtonState::OnPress, SButtonData{ 0, 80, 127, 38, CUISystem::EventHandler_OnPressButtonGDI })); // x,y,width,height from source
	m_uiButtonGDI = CUIButton(m_buttonTexture, { 100, 530, 150, 38 }, m_buttonMapButtonGDI); // x, y, width, height for dest

	m_buttonMapButtonOpenGL.insert(ButtonPair(EButtonState::OnNormal, SButtonData{ 0, 0, 127, 38, nullptr })); // m_x,y,width,height from source
	m_buttonMapButtonOpenGL.insert(ButtonPair(EButtonState::OnHover, SButtonData{ 0, 40, 127, 38, nullptr })); // m_x,y,width,height from source
	m_buttonMapButtonOpenGL.insert(ButtonPair(EButtonState::OnPress, SButtonData{ 0, 80, 127, 38, CUISystem::EventHandler_OnPressButtonOpenGL })); // x,y,width,height from source
	m_uiButtonOpenGL = CUIButton(m_buttonTexture, { 266, 530, 150, 38 }, m_buttonMapButtonOpenGL); // x, y, width, height for dest

	m_buttonMapButtonDirectX11.insert(ButtonPair(EButtonState::OnNormal, SButtonData{ 0, 0, 127, 38, nullptr })); // x,y,width,height from source
	m_buttonMapButtonDirectX11.insert(ButtonPair(EButtonState::OnHover, SButtonData{ 0, 40, 127, 38, nullptr })); // x,y,width,height from source
	m_buttonMapButtonDirectX11.insert(ButtonPair(EButtonState::OnPress, SButtonData{ 0, 80, 127, 38, CUISystem::EventHandler_OnPressButtonDirectX11 })); // x,y,width,height from source
	m_uiButtonDirectX11 = CUIButton(m_buttonTexture, { 433, 530, 150, 38 }, m_buttonMapButtonDirectX11); // x, y, width, height for dest

	m_buttonMapButtonDirect2D.insert(ButtonPair(EButtonState::OnNormal, SButtonData{ 0, 0, 127, 38, nullptr })); // x,y,width,height from source
	m_buttonMapButtonDirect2D.insert(ButtonPair(EButtonState::OnHover, SButtonData{ 0, 40, 127, 38, nullptr })); // x,y,width,height from source
	m_buttonMapButtonDirect2D.insert(ButtonPair(EButtonState::OnPress, SButtonData{ 0, 80, 127, 38, CUISystem::EventHandler_OnPressButtonDirect2D })); // x,y,width,height from source
	m_uiButtonDirect2D = CUIButton(m_buttonTexture, { 600, 530, 150, 38 }, m_buttonMapButtonDirect2D); // x, y, width, height for dest
}


void CScene::LoadTextures(IRenderer* a_renderer)
{
	ReleaseTextures();
	//.\\data\\graphics\\Wall.bmp
	m_backgroundTexture = a_renderer->LoadTextureFromFile("Textures/background.bmp");//("Textures/goblin.bmp");
	m_collisionTexture = a_renderer->LoadTextureFromFile("Textures/collision.bmp");
	m_terrainTexture = a_renderer->LoadTextureFromFile("Textures/terrain.bmp");
	m_playerTexture = a_renderer->LoadTextureFromFile("Textures/player.bmp");

	m_buttonTexture = a_renderer->LoadTextureFromFile("Textures/button.bmp");
	m_fontTexture = a_renderer->LoadTextureFromFile("Textures/font.bmp");
}

//void CScene::LoadSounds(ISoundEngine * a_soundEngine)
//{
//	// just a sound-test
//	m_testSound = m_soundEngine->LoadSound("Audio/throw.mp3"); // load sound into memory
//}


void CScene::ReleaseTextures()
{
	SafeDelete(m_backgroundTexture);
	SafeDelete(m_collisionTexture);
	SafeDelete(m_terrainTexture);
	SafeDelete(m_playerTexture);
	SafeDelete(m_buttonTexture);
	SafeDelete(m_fontTexture);
}

//void CScene::ReleaseSound(ISoundEngine* a_soundEngine)
//{
//	a_soundEngine->UnloadSound(m_testSound);
//}


void CScene::Shutdown()
{
	ReleaseTextures();
	//ReleaseSound(a_soundEngine);
}
