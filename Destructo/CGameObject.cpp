#include "CGameObject.h"

CGameObject::CGameObject(SVector3 a_position, SVector3 a_scale, float a_rotation, ITexture* a_texture)
	: m_position(a_position)
	, m_scale(a_scale)
	, m_rotation(a_rotation)
	, m_texture(a_texture)
{
}

CGameObject::~CGameObject()
{
}
