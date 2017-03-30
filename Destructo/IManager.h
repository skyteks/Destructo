#pragma once

class IManager
{
	virtual ~IManager() {};

	virtual bool Initialize() = 0;

	virtual void Shutdown() = 0;
};
