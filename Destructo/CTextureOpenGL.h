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

	int GetPitch();

	int GetBPP();

	void SetPixel(int a_x, int a_y, int a_color);

	void AddOpacityMask();

	GLuint GetTextureID();

	void* GetData() const;

	static CTextureOpenGL* s_collisionTexture;

private:

	int m_width;
	int m_height;
	int m_pitch;
	int m_bitsPerPixel;
	bool m_isLocked;
	char* m_path = nullptr;
	
	UINT* m_data = nullptr;

	GLuint m_textureID;
};

