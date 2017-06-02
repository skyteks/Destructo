#pragma once
#include "CGameObject.h"
class CGameObject;

class IComponent
{
public:
	virtual void Update(CGameObject& a_object) = 0;
};