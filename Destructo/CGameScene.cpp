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
	CTextureManager::GetInstance().LoadTexture(TEXTURE_PLAYER_2);
	CTextureManager::GetInstance().LoadTexture(TEXTURE_FONT);

	SRigidbody* playerRigid = new SRigidbody();
	SCircleBB* playerCol = new SCircleBB(SVector3(0,0),100);

	SRigidbody* testRigid = new SRigidbody();
	SCircleBB* testCol = new SCircleBB(SVector3(0, 0), 100);

	m_objectPlayer = new CGameObject(SVector3(100.0f, 100.0f), SVector3(1.0f, 1.0f), 45.0f, TEXTURE_PLAYER, "", playerRigid, playerCol);
	m_objectTerrain = new CGameObject(SVector3(0.0f, 0.0f), SVector3(1.0f, 1.0f), 0.0f, TEXTURE_TERRAIN, TEXTURE_COLLISION, nullptr, nullptr);
	m_objectBackground = new CGameObject(SVector3(0.0f, 0.0f), SVector3(1.0f, 1.0f), 0.0f, TEXTURE_BACKGROUND, "", nullptr, nullptr);
	m_objectPlayer2 = new CGameObject(SVector3(150.0f, 100.0f), SVector3(1.0f, 1.0f), 0.0f, TEXTURE_PLAYER_2, "", testRigid, testCol);

	m_quadTree = new CQuadTree(SAABB(SVector3(400.0f, 400.0f), 800.0f));
	m_quadTree->Insert(m_objectPlayer);
	m_quadTree->Insert(m_objectPlayer2);

	return true;
}


void CGameScene::Update()
{
	speed = 500 * CTime::GetInstance().DeltaTime();

	float playerPosX = 0.0f;
	float playerPosY = 0.0f;

	if (m_objectPlayer->GetPosition().x < 800 - 32 && CInputManager::GetInstance().GetKey(EKeyCode::D))
		playerPosX += speed;
	if (m_objectPlayer->GetPosition().x >= 0 && CInputManager::GetInstance().GetKey(EKeyCode::A))
		playerPosX -= speed;
	if (m_objectPlayer->GetPosition().y < 600 - 32 && CInputManager::GetInstance().GetKey(EKeyCode::S))
		playerPosY += speed;
	if (m_objectPlayer->GetPosition().y >= 0 && CInputManager::GetInstance().GetKey(EKeyCode::W))
		playerPosY -= speed;

	m_objectPlayer->SetPosition(m_objectPlayer->GetPosition() + SVector3(playerPosX, playerPosY));

	float player2PosX = 0.0f;
	float player2PosY = 0.0f;

	if (m_objectPlayer2->GetPosition().x < 800 - 32 && CInputManager::GetInstance().GetKey(EKeyCode::Right))
		player2PosX += speed;
	if (m_objectPlayer2->GetPosition().x >= 0 && CInputManager::GetInstance().GetKey(EKeyCode::Left))
		player2PosX -= speed;
	if (m_objectPlayer2->GetPosition().y < 600 - 32 && CInputManager::GetInstance().GetKey(EKeyCode::Down))
		player2PosY += speed;
	if (m_objectPlayer2->GetPosition().y >= 0 && CInputManager::GetInstance().GetKey(EKeyCode::Up))
		player2PosY -= speed;

	m_objectPlayer2->SetPosition(m_objectPlayer2->GetPosition() + SVector3(playerPosX, playerPosY));

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

	m_quadTree->Update();
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

	a_renderer->DrawObject(*m_objectPlayer2);

	//a_renderer->DrawTexture(0, 0, 0, 0, buttonTexture, 0, 0, 0, 0);//DO NOT REMOVE (BUG)

	char buffer[200] = {};
	sprintf_s(buffer, "MouseX: %i\nMouseY: %i\nMouseL: %s\nMouseR: %s\nFPS: %i\n %f %f \n %f \n %f",
		CMouse::x,
		CMouse::y,
		CMouse::isLeftMouseDown ? "true" : "false",
		CMouse::isRightMouseDown ? "true" : "false",
		static_cast<int>(1 / CTime::GetInstance().DeltaTime()),
		m_objectPlayer->GetPosition().x,
		m_objectPlayer->GetPosition().y,
		m_objectPlayer->GetRigidbody()->GetVelocity().y,
		m_objectPlayer2->GetRigidbody()->GetVelocity().y
	);
	a_renderer->DrawString(10, 10, buffer, RGB(255, 255, 255), RGB(0, 0, 0), DT_TOP | DT_LEFT, fontTexture);
}




void CGameScene::Shutdown()
{
	SafeDelete(m_objectPlayer);
	SafeDelete(m_objectTerrain);
	SafeDelete(m_objectBackground);
	SafeDelete(m_objectPlayer2);

	SafeDelete(m_quadTree);
}
