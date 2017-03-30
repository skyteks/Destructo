#include "CTextureOpenGL.h"
#include "GlobalFunctions.h"

CTextureOpenGL::CTextureOpenGL(const char* a_path)
{
	char cwd[MAX_PATH + 1] = { 0 };
	GetCurrentDirectoryA(MAX_PATH, cwd);
	SBitmap bmp = LoadBitmapAndAddAlpha(a_path);

	m_width = bmp.m_header.m_width;
	m_height = bmp.m_header.m_height;

	m_data = reinterpret_cast<UINT*>(bmp.m_data);

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
	
	if (m_textureID == 2)
	{
		s_collisionTexture = this;
	}	
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


void * CTextureOpenGL::GetData() const
{
	return m_data;
}


int CTextureOpenGL::GetPitch()
{
	return m_pitch;
}


int CTextureOpenGL::GetBPP()
{
	return m_bitsPerPixel;
}


void CTextureOpenGL::SetPixel(int a_x, int a_y, int a_color)
{
	if (a_x < 0 || a_x > m_width || a_y < 0 || a_y > m_height)
		return;

	int index = a_x + ((m_height - a_y) * m_width);
	int* p = reinterpret_cast<int*>(m_data);
	*(p + index) = 0xFF000000; // ABGR
}

void CTextureOpenGL::AddOpacityMask()
{
	for (auto y = 0; y < m_height; y++)
	{
		for (auto x = 0; x < m_width; x++)
		{
			int index = x + y * m_width;

			// read mask
			int* pMask = reinterpret_cast<int*>(s_collisionTexture->m_data);
			//unsigned int value = *(pMask + index);
			if (*(pMask + index) == 0xFF000000) // black
			{
				// access to modify pixel data
				int* p = reinterpret_cast<int*>(m_data);
				*(p + index) = 0x00000000;
			}
		}
	}

	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
}

CTextureOpenGL* CTextureOpenGL::s_collisionTexture = nullptr;