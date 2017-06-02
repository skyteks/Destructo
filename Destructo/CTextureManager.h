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
	bool LoadTexture(const std::string a_path);
	ITexture* GetTextureByName(const std::string a_path) const;
	const char* GetNameByTexture(const ITexture* a_texture) const;

private:
	TextureMap m_textureMap;
	IRenderer** m_renderer = nullptr;
};

