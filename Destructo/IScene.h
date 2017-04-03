#pragma once
#include "IRenderer.h"

class IScene
{
public:
	virtual ~IScene() {};

	virtual bool Initialize(IRenderer* a_renderer) = 0;

	virtual void Update() = 0;

	virtual void Draw(IRenderer* a_renderer) = 0;

	virtual void Shutdown() = 0;
};