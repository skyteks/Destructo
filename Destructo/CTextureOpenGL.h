#pragma once

#include "ITexture.h"
#include <gl\GL.h>
#include <string>

class CTextureOpenGL : public ITexture
{
public:
	CTextureOpenGL(std::string a_path);
	
	~CTextureOpenGL() override;

	int GetWidth() const override;

	int GetHeight() const override;

	int GetPitch() const override;

	int GetBPP() const override;

	void SetPixel(int a_x, int a_y, int a_color) override;

	void AddOpacityMask(const CTextureOpenGL* a_opacityMask) const;

	GLuint GetTextureID() const;

	void* GetData() const;

	static CTextureOpenGL* s_collisionTexture;

private:

	int m_width;
	int m_height;
	int m_pitch;
	int m_bitsPerPixel;
	bool m_isLocked;
	
	UINT* m_data = nullptr;

	GLuint m_textureID;
};

