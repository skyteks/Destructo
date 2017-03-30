#pragma once

#include <string>
#include <unordered_map>

//#include "IManager.h"
#include "IRenderer.h"
#include "GlobalFunctions.h"

typedef std::unordered_map<std::string, ITexture*> TextureMap;

class CTextureManager //: public IManager
{
public:
	CTextureManager();
	~CTextureManager();
	void Initialize(IRenderer** a_renderer);
	void Shutdown();
	
	static CTextureManager& GetInstance();
	bool LoadTexture(const char* a_path);
	ITexture* GetTexture(const char* a_path);
	const char* GetNameByTexture(ITexture* a_texture);
private:
	TextureMap m_textureMap;
	IRenderer** m_renderer = nullptr;
};

