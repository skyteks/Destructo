#include "CGameScene.h"
#include "DataNames.h"

CGameScene::CGameScene()
{
}


CGameScene::~CGameScene()
{
}


bool CGameScene::Initialize(IRenderer* a_renderer)
{

	CTextureManager::GetInstance().LoadTexture(TEXTURE_TERRAIN);
	CTextureManager::GetInstance().LoadTexture(TEXTURE_COLLISION);
	CTextureManager::GetInstance().LoadTexture(TEXTURE_BACKGROUND);
	CTextureManager::GetInstance().LoadTexture(TEXTURE_PLAYER);
	CTextureManager::GetInstance().LoadTexture(TEXTURE_FONT);

	m_objectPlayer = new CGameObject({ 100.0f, 100.0f }, { 1.0f, 1.0f }, 45.0f, TEXTURE_PLAYER);
	m_objectTerrain = new CGameObject({ 0.0f, 0.0f }, { 1.0f, 1.0f }, 0.0f, TEXTURE_TERRAIN, TEXTURE_COLLISION);
	m_objectBackground = new CGameObject({ 0.0f, 0.0f }, { 1.0f, 1.0f }, 0.0f, TEXTURE_BACKGROUND);

	return true;
}


void CGameScene::Update()
{
	speed = 500 * CTime::GetInstance().DeltaTime();

	m_playerPosX = m_objectPlayer->GetPosition().x;
	m_playerPosY = m_objectPlayer->GetPosition().y;

	if (m_playerPosX < 800 - 32 && CInputManager::GetInstance().GetKey(EKeyCode::D))
		m_playerPosX += static_cast<int>(speed);
	if (m_playerPosX >= 0 && CInputManager::GetInstance().GetKey(EKeyCode::A))
		m_playerPosX -= static_cast<int>(speed);
	if (m_playerPosY < 600 - 32 && CInputManager::GetInstance().GetKey(EKeyCode::S))
		m_playerPosY += static_cast<int>(speed);
	if (m_playerPosY >= 0 && CInputManager::GetInstance().GetKey(EKeyCode::W))
		m_playerPosY -= static_cast<int>(speed);

	m_objectPlayer->SetPosition(SVector3(m_playerPosX, m_playerPosY));

	if (CInputManager::GetInstance().GetKey(EKeyCode::E))
	{
		m_objectPlayer->AddRotation(CTime::GetInstance().DeltaTime());
	}
	if (CInputManager::GetInstance().GetKey(EKeyCode::Q))
	{
		m_objectPlayer->AddRotation(-1.0f * CTime::GetInstance().DeltaTime());
	}

	if (CInputManager::GetInstance().GetKey(EKeyCode::R))
	{
		m_objectPlayer->SetScale(m_objectPlayer->GetScale() + SVector3::One() * CTime::GetInstance().DeltaTime());
	}
	if (CInputManager::GetInstance().GetKey(EKeyCode::F))
	{
		m_objectPlayer->SetScale(m_objectPlayer->GetScale() - SVector3::One() * CTime::GetInstance().DeltaTime());
	}

	if (CMouse::isLeftMouseDown)
	{
		CTextureManager::GetInstance().GetTextureByName(TEXTURE_COLLISION)->SetPixel(CMouse::x, CMouse::y, 0xFF000000);
	}
}


void CGameScene::Draw(IRenderer* a_renderer)
{
	if (a_renderer == nullptr)
	{
		return;
	}

	auto backgroundTexture = CTextureManager::GetInstance().GetTextureByName(TEXTURE_BACKGROUND);
	auto terrainTexture = CTextureManager::GetInstance().GetTextureByName(TEXTURE_TERRAIN);
	auto collisionTexture = CTextureManager::GetInstance().GetTextureByName(TEXTURE_COLLISION);
	auto playerTexture = CTextureManager::GetInstance().GetTextureByName(TEXTURE_PLAYER);
	auto fontTexture = CTextureManager::GetInstance().GetTextureByName(TEXTURE_FONT);

	//a_renderer->DrawTexture(0, 0, 800, 600, backgroundTexture, 0, 0, backgroundTexture->GetWidth(), backgroundTexture->GetHeight());
	a_renderer->DrawObject(*m_objectBackground);
	//a_renderer->DrawTextureWithOpacityMask(0, 0, 800, 600, terrainTexture, 0, 0, terrainTexture->GetWidth(), terrainTexture->GetHeight(), collisionTexture);
	a_renderer->DrawObject(*m_objectTerrain);
	//a_renderer->DrawTexture(m_playerPosX, m_playerPosY, 32, 32, playerTexture, 0, 0, playerTexture->GetWidth(), playerTexture->GetHeight());
	a_renderer->DrawObject(*m_objectPlayer);

	//a_renderer->DrawTexture(0, 0, 0, 0, buttonTexture, 0, 0, 0, 0);//DO NOT REMOVE (BUG)

	char buffer[200] = {};
	sprintf_s(buffer, "MouseX: %i\nMouseY: %i\nMouseL: %s\nMouseR: %s\nFPS: %i\n %f %f",
		CMouse::x,
		CMouse::y,
		CMouse::isLeftMouseDown ? "true" : "false",
		CMouse::isRightMouseDown ? "true" : "false",
		static_cast<int>(1 / CTime::GetInstance().DeltaTime()),
		m_objectPlayer->GetPosition().x,
		m_objectPlayer->GetPosition().y
	);
	a_renderer->DrawString(10, 10, buffer, RGB(255, 255, 255), RGB(0, 0, 0), DT_TOP | DT_LEFT, fontTexture);
}




void CGameScene::Shutdown()
{
	SafeDelete(m_objectPlayer);
	SafeDelete(m_objectTerrain);
	SafeDelete(m_objectBackground);
}
