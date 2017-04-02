#pragma once
#include "SVector3.h"
#include "ITexture.h"

class CGameObject
{
public:
	CGameObject(SVector3 a_position, SVector3 a_scale, float a_rotation, ITexture* a_texture);

	~CGameObject();

private:
	SVector3 m_position;
	SVector3 m_scale;
	float m_rotation;
	ITexture* m_texture;
};

