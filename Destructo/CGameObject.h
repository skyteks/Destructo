#pragma once
#include "SVector3.h"
#include "ITexture.h"
#include "SRect.h"
#include "SMatrix4x4.h"
#include "GlobalFunctions.h"

class CGameObject
{
public:
	CGameObject();

	CGameObject(SVector3 a_position, SVector3 a_scale, float a_rotation, char* a_textureName, char* a_opacityMask = nullptr);

	~CGameObject();

	void SetPosition(SVector3 a_position);
	void SetRotation(float a_rotation);
	void AddRotation(float a_rotation);
	void SetScale(SVector3 a_scale);

	const SVector3& GetPosition();
	const SMatrix4x4& GetRotation();
	const SVector3& GetScale();
	const SRect& GetImageSection();

	char* GetTextureName();
	char* GetOpacityMaskName();

private:
	SVector3 m_position;
	SVector3 m_scale;
	char* m_textureName;
	char* m_opacityMask;
	SRect m_imageSection;
	float m_rotation;
	SMatrix4x4 m_rotationMatrix;
	
};

