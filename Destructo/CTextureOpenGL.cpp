#include "CTextureOpenGL.h"
#include "GlobalFunctions.h"

CTextureOpenGL::CTextureOpenGL(char* a_path)
{
	char cwd[MAX_PATH + 1] = { 0 };
	GetCurrentDirectoryA(MAX_PATH, cwd);
	SBitmap bmp = LoadBitmapAndAddAlpha(a_path);

	x2 = bmp.m_header.x2;
	y2 = bmp.m_header.y2;

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bmp.m_header.x2, bmp.m_header.y2, 0, GL_RGBA, GL_UNSIGNED_BYTE, bmp.m_data);
}


CTextureOpenGL::~CTextureOpenGL()
{

}


int CTextureOpenGL::GetWidth()
{
	return x2;
}


int CTextureOpenGL::GetHeight()
{
	return y2;
}


GLuint CTextureOpenGL::GetTextureID()
{
	return m_textureID;
}

