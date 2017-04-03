#include "CGameObject.h"

#include "CTextureManager.h"

CGameObject::CGameObject()
	: m_position(SVector3::One())
	, m_scale(SVector3::One())
	, m_rotation(0.0f)
	, m_rotationMatrix(SMatrix4x4::Identity())
	, m_textureName(nullptr)
	, m_opacityMask(nullptr)
{
}

CGameObject::CGameObject(SVector3 a_position, SVector3 a_scale, float a_rotation, char* a_textureName, char* a_opacityMask)
	: m_position(a_position)
	, m_scale(a_scale)
	, m_rotation(a_rotation)
	, m_rotationMatrix(SMatrix4x4::RotationZ(a_rotation))
	, m_textureName(nullptr)
	, m_opacityMask(nullptr)
{
	ITexture* texture = CTextureManager::GetInstance().GetTextureByName(a_textureName);
	if (texture)
	{
		m_imageSection.x1 = 0.0f;
		m_imageSection.y1 = 0.0f;
		m_imageSection.x2 = texture->GetWidth();
		m_imageSection.y2 = texture->GetHeight();
	}

	if (a_textureName)
	{
		size_t strLen = strlen(a_textureName) + 1;
		m_textureName = new char[strLen];
		strcpy_s(m_textureName, strLen, a_textureName);
	}
	if (a_opacityMask)
	{
		size_t strLen = strlen(a_opacityMask) + 1;
		m_opacityMask = new char[strLen];
		strcpy_s(m_opacityMask, strLen, a_opacityMask);
	}
}

CGameObject::~CGameObject()
{
	SafeDelete(m_textureName);
}

void CGameObject::SetPosition(SVector3 a_position)
{
	m_position = a_position;
}

void CGameObject::SetRotation(float a_rotation)
{
	m_rotation = a_rotation;
	m_rotationMatrix = SMatrix4x4::RotationZ(m_rotation);
}

void CGameObject::AddRotation(float a_rotation)
{
	m_rotation += a_rotation;
	m_rotationMatrix = SMatrix4x4::RotationZ(m_rotation);
}

void CGameObject::SetScale(SVector3 a_scale)
{
	m_scale = a_scale;
}

const SVector3& CGameObject::GetPosition()
{
	return m_position;
}

const SVector3& CGameObject::GetScale()
{
	return m_scale;
}

const SRect& CGameObject::GetImageSection()
{
	return m_imageSection;
}

const SMatrix4x4& CGameObject::GetRotation()
{
	return m_rotationMatrix;
}

char * CGameObject::GetTextureName()
{
	return m_textureName;
}

char * CGameObject::GetOpacityMaskName()
{
	return m_opacityMask;
}
