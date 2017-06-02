#include "CGameObject.h"

#include "CTextureManager.h"

CGameObject::CGameObject()
	: m_position(SVector3::One())
	, m_scale(SVector3::One())
	, m_rotationAngle(0.0f)
	, m_rotationMatrix(SMatrix4x4::Identity())
	, m_textureName(nullptr)
	, m_opacityMaskName(nullptr)
	, m_rigid(nullptr)
	, m_col(nullptr)
{
}

CGameObject::CGameObject(SVector3 a_position, SVector3 a_scale, float a_rotation, std::string a_textureName, std::string a_opacityMaskName, CRigidbody* a_rigid, CCollider* a_collider)
	: m_position(a_position)
	, m_scale(a_scale)
	, m_rotationAngle(a_rotation)
	, m_rotationMatrix(SMatrix4x4::RotationZ(a_rotation))
	, m_textureName(a_textureName)
	, m_opacityMaskName(a_opacityMaskName)
	, m_rigid(a_rigid)
	, m_col(a_collider)
{
	const ITexture* texture = CTextureManager::GetInstance().GetTextureByName(a_textureName);
	if (texture != nullptr)
	{
		m_imageSection.x1 = 0.0f;
		m_imageSection.y1 = 0.0f;
		m_imageSection.x2 = texture->GetWidth();
		m_imageSection.y2 = texture->GetHeight();
	}

	//if (a_textureName != nullptr)
	//{
		//size_t strLen = strlen(a_textureName) + 1;
		//m_textureName = new char[strLen];
		//strcpy_s(m_textureName, strLen, a_textureName);
		//m_textureName[strLen] = '\0';
		m_textureName = a_textureName;
	//}
	//if (a_opacityMaskName != nullptr)
	//{
		//size_t strLen = strlen(a_opacityMaskName) + 1;
		//m_opacityMaskName = new char[strLen];
		//strcpy_s(m_opacityMaskName, strLen, a_opacityMaskName);
		//m_opacityMaskName[strLen] = '\0';
		m_opacityMaskName = a_opacityMaskName;
	//}
}

CGameObject::~CGameObject()
{
	//SafeDelete(m_textureName);
	//SafeDelete(m_opacityMaskName);

	SafeDelete(m_rigid);
	SafeDelete(m_col);
}

void CGameObject::SetPosition(SVector3 a_position)
{
	m_position = a_position;
}

void CGameObject::SetRotation(float a_rotation)
{
	m_rotationAngle = a_rotation;
	m_rotationMatrix = SMatrix4x4::RotationZ(m_rotationAngle);
}

void CGameObject::AddRotation(float a_rotation)
{
	m_rotationAngle += a_rotation;
	m_rotationMatrix = SMatrix4x4::RotationZ(m_rotationAngle);
}

void CGameObject::SetScale(SVector3 a_scale)
{
	m_scale = a_scale;
}

const SVector3& CGameObject::GetPosition() const
{
	return m_position;
}

const SVector3& CGameObject::GetScale() const
{
	return m_scale;
}

const SRect& CGameObject::GetImageSection() const
{
	return m_imageSection;
}

CRigidbody* CGameObject::GetRigidbody() const
{
	return m_rigid;
}

CCollider* CGameObject::GetCollider() const
{
	return m_col;
}

const SMatrix4x4& CGameObject::GetRotation() const
{
	return m_rotationMatrix;
}

float CGameObject::GetRotationAngle() const
{
	return m_rotationAngle;
}

const std::string CGameObject::GetTextureName() const
{
	return m_textureName;
}

const std::string CGameObject::GetOpacityMaskName() const
{
	return m_opacityMaskName;
}

void CGameObject::Update()
{
	if (m_rigid != nullptr)
	{
		m_rigid->Update(*this);
	}
}
