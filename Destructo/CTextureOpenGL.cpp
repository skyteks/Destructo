#include "CTextureOpenGL.h"
#include "GlobalFunctions.h"

CTextureOpenGL::CTextureOpenGL(char* a_path)
{
	char cwd[MAX_PATH + 1] = { 0 };
	GetCurrentDirectoryA(MAX_PATH, cwd);
	SBitmap bmp = LoadBitmapAndAddAlpha(a_path);

	m_width = bmp.m_header.m_width;
	m_height = bmp.m_header.m_height;

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bmp.m_header.m_width, bmp.m_header.m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bmp.m_data);
}


CTextureOpenGL::~CTextureOpenGL()
{

}


int CTextureOpenGL::GetWidth()
{
	return m_width;
}


int CTextureOpenGL::GetHeight()
{
	return m_height;
}


GLuint CTextureOpenGL::GetTextureID()
{
	return m_textureID;
}

