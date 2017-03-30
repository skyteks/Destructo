#include "CTextureManager.h"

CTextureManager::CTextureManager()
{
}


CTextureManager::~CTextureManager()
{

}

void CTextureManager::Initialize(IRenderer ** a_renderer)
{
	m_renderer = a_renderer;
}

void CTextureManager::Shutdown()
{
	for (auto& element : m_textureMap)
	{
		if (element.second)
		{
			SafeDelete(element.second);
		}
	}

	m_textureMap.clear();
}

CTextureManager& CTextureManager::GetInstance()
{
	static CTextureManager s_textureManager;
	return s_textureManager;
}

bool CTextureManager::LoadTexture(const char* a_path)
{
	// is present in map? ==> return false;
	//auto found = m_textureMap.find(a_path);

	//if (found == m_textureMap.end())
	//{
	//	return false;
	//}

	ITexture* texture = (*m_renderer)->LoadTextureFromFile(a_path);
	m_textureMap[a_path] = texture;

	return true;
}

ITexture* CTextureManager::GetTexture(const char* a_path)
{
	return m_textureMap[a_path];
}

const char * CTextureManager::GetNameByTexture(ITexture* a_texture)
{
	for (auto& element : m_textureMap)
	{
		if (element.second == a_texture)
		{
			return element.first.c_str();
		}
	}

	return nullptr;
}
