#include "CRendererOpenGL.h"
#include "DataNames.h"

CRendererOpenGL::CRendererOpenGL()
{
}


CRendererOpenGL::~CRendererOpenGL()
{
}


bool CRendererOpenGL::Initialize(HWND a_hwnd)
{
	m_windowHandle = a_hwnd;

	m_windowDC = GetDC(m_windowHandle);

	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | LPD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int iPixelFormat = ChoosePixelFormat(m_windowDC, &pfd);

	bool wResult = false;

	wResult = SetPixelFormat(m_windowDC, iPixelFormat, &pfd) != 0;
	if (!wResult)
		return false;

	HGLRC renderContext = wglCreateContext(m_windowDC);

	wResult = wglMakeCurrent(m_windowDC, renderContext) != 0;
	if (!wResult)
		return false;

	RECT rc;
	wResult = GetClientRect(m_windowHandle, &rc) != 0;
	if (!wResult)
		return false;
	m_windowWidth = rc.right;
	m_windowHeight = rc.bottom;


	glViewport(0, 0, m_windowWidth, m_windowHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(0, windowWidth, 0, windowHeight, 0, 1);
	glOrtho(rc.left, rc.right, rc.bottom, rc.top, 0, 1);

	glEnable(GL_TEXTURE_2D);

	// alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// load font
	//m_fontTexture = LoadTextureFromFile("Textures/font.bmp");

	return true;
}


ITexture* CRendererOpenGL::LoadTextureFromFile(const char* a_path)
{
	return new CTextureOpenGL(a_path);
}


void CRendererOpenGL::Begin()
{
	//SwapBuffers(windowDC);

	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


void CRendererOpenGL::DrawTexture(int a_posX, int a_posY, int a_width, int a_height, ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight)
{
	CTextureOpenGL* openGLTexture = reinterpret_cast<CTextureOpenGL*>(a_texture);

	// Singleton
	// char* => ITexture*
	// GetTextureByName(char*) => ITexture*


	const char* name = CTextureManager::GetInstance().GetNameByTexture(a_texture);
	
	if (strcmp(name, TEXTURE_TERRAIN) == 0) //if (openGLTexture->GetTextureID() == 1)
	{
		openGLTexture->AddOpacityMask();
	}

	glBindTexture(GL_TEXTURE_2D, openGLTexture->GetTextureID());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);

	SRect source;
	source.x1 = a_imgX;
	source.x2 = a_imgWidth;
	source.y1 = a_imgY;
	source.y2 = a_imgHeight;

	SRect dest;
	dest.x1 = a_posX;
	dest.x2 = a_width;
	dest.y1 = a_posY;
	dest.y2 = a_height;

	float texWidth = static_cast<float>(a_texture->GetWidth());
	float texHeight = static_cast<float>(a_texture->GetHeight());

	SRect tex;
	tex.x1 = source.x1 / texWidth;
	tex.x2 = source.x2 / texWidth;
	tex.y1 = source.y1 / texHeight;
	tex.y2 = source.y2 / texHeight;


	// x,y
	// scale
	// rotationZ
	// ITexture*
	// GetCoordinates(); return => 4 vectoren

	if (strcmp(name, TEXTURE_PLAYER) == 0) //if (openGLTexture->GetTextureID() == 4)
	{
		static float rotValue = 0.0f;

		rotValue += 0.01f;

		dest.x1 -= a_posX + a_width / 2;
		dest.y1 -= a_posY + a_height / 2;

		// rotate
		SVector3 vec1(dest.x1, dest.y1, 0.0f);
		SVector3 vec2(dest.x1 + dest.x2, dest.y1, 0.0f);
		SVector3 vec3(dest.x1 + dest.x2, dest.y1 + dest.y2, 0.0f);
		SVector3 vec4(dest.x1, dest.y1 + dest.y2, 0.0f);
		SMatrix4x4 rotation = SMatrix4x4::RotationZ(rotValue);

		auto result1 = rotation * vec1;
		auto result2 = rotation * vec2;
		auto result3 = rotation * vec3;
		auto result4 = rotation * vec4;

		dest.x1 += a_posX + a_width / 2;
		dest.y1 += a_posY + a_height / 2;

		result1.x += dest.x1;
		result2.x += dest.x1;
		result3.x += dest.x1;
		result4.x += dest.x1;

		result1.y += dest.y1;
		result2.y += dest.y1;
		result3.y += dest.y1;
		result4.y += dest.y1;

		glTexCoord2f(tex.x1, 1 - tex.y1); // bottom-left
		glVertex3f(result1.x, result1.y, 0); // topleft

		glTexCoord2f(tex.x1 + tex.x2, 1 - tex.y1); // bottom-right
		glVertex3f(result2.x, result2.y, 0); // topright ==> Vector2 * rotationmatrix ==> rotated Vector2

		glTexCoord2f(tex.x1 + tex.x2, 1 - (tex.y1 + tex.y2)); // top-right
		glVertex3f(result3.x, result3.y, 0); // bottomright

		glTexCoord2f(tex.x1, 1 - (tex.y1 + tex.y2)); // top-left
		glVertex3f(result4.x, result4.y, 0); // bottomleft

		glEnd();
		return;
	}

	//BACKUP
	glTexCoord2f(tex.x1, 1 - tex.y1); // bottom-left
	glVertex3f(dest.x1, dest.y1, 0); // topleft

	glTexCoord2f(tex.x1 + tex.x2, 1 - tex.y1); // bottom-right
	glVertex3f(dest.x1 + dest.x2, dest.y1, 0); // topright ==> Vector2 * rotationmatrix ==> rotated Vector2

	glTexCoord2f(tex.x1 + tex.x2, 1 - (tex.y1 + tex.y2)); // top-right
	glVertex3f(dest.x1 + dest.x2, dest.y1 + dest.y2, 0); // bottomright

	glTexCoord2f(tex.x1, 1 - (tex.y1 + tex.y2)); // top-left
	glVertex3f(dest.x1, dest.y1 + dest.y2, 0); // bottomleft

	glEnd();
}


void CRendererOpenGL::DrawString(int a_posX, int a_posY, const char* a_string, int a_textColor, int a_backgroundColor, UINT a_format, ITexture* a_fontTexture)
{
	if (a_string == nullptr)
		return;

	SRect source;
	SRect dest;

	unsigned int counter = 0;
	unsigned int newLines = 0;

	while (*a_string)
	{
		char c = *a_string++;

		source.x1 = (c % 16) * 16;
		source.y1 = (c / 16) * 16;
		source.x2 = 16;
		source.y2 = 16;

		dest.x1 = a_posX + counter * 16;
		dest.y1 = a_posY + (newLines * 16);
		dest.x2 = 16;
		dest.y2 = 16;

		if (c == '\n')
		{
			newLines++;
			counter = 0;
		}
		else
		{
			DrawTexture(dest.x1, dest.y1, dest.x2, dest.y2, a_fontTexture, source.x1, source.y1, source.x2, source.y2);
			counter++;
		}
	}
}


void CRendererOpenGL::End()
{
	SwapBuffers(m_windowDC);
}


void CRendererOpenGL::Shutdown()
{

}