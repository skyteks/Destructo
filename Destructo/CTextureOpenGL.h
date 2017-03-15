#pragma once

#include "ITexture.h"
#include <gl\GL.h>

class CTextureOpenGL : public ITexture
{
public:
	CTextureOpenGL(char* a_path);

	~CTextureOpenGL();

	int GetWidth();

	int GetHeight();

	GLuint GetTextureID();

private:

	int m_width;
	int m_height;
	int m_pitch;
	int m_bitsPerPixel;
	bool m_isLocked;

	UINT* m_data = nullptr;

	GLuint m_textureID;
};

