#pragma once
#include "SVector3.h"
#include "ITexture.h"
#include "SRect.h"
#include "SMatrix4x4.h"
#include "GlobalFunctions.h"
#include "SRigidbody.h"
#include "SCircleBB.h"

class SRigidbody;

class CGameObject
{
public:
	CGameObject();

	CGameObject(SVector3 a_position, SVector3 a_scale, float a_rotation, std::string a_textureName, std::string a_opacityMask, SRigidbody* a_rigid, SCircleBB* a_collider);

	~CGameObject();

	void SetPosition(SVector3 a_position);
	void SetRotation(float a_rotation);
	void AddRotation(float a_rotation);
	void SetScale(SVector3 a_scale);

	const SVector3& GetPosition();
	const SMatrix4x4& GetRotation();
	float GetRotationAngle();
	const SVector3& GetScale();
	const SRect& GetImageSection();
	SRigidbody* GetRigidbody();
	SCircleBB* GetCircleCollider();

	std::string GetTextureName();
	std::string GetOpacityMaskName();

	void Update();

private:
	SVector3 m_position;
	SVector3 m_scale;
	std::string m_textureName;
	std::string m_opacityMaskName;
	SRect m_imageSection;
	float m_rotationAngle;
	SMatrix4x4 m_rotationMatrix;
	
	SRigidbody* m_rigid;
	SCircleBB* m_collider;
};

