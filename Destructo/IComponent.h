#pragma once
#include "CGameObject.h"
class CGameObject;

struct IComponent
{
public:
	virtual void Update(CGameObject* a_object) = 0;
};