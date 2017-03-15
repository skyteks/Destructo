#include "CRendererOpenGL.h"

CRendererOpenGL::CRendererOpenGL()
{
}


CRendererOpenGL::~CRendererOpenGL()
{
}


bool CRendererOpenGL::InitializeGraphics(HWND a_hwnd)
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
	m_fontTexture = LoadTextureFromFile("Textures/font.bmp");

	return true;
}


ITexture* CRendererOpenGL::LoadTextureFromFile(char* a_path)
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
	glBindTexture(GL_TEXTURE_2D, openGLTexture->GetTextureID());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);

	float mappedPosX = a_imgX;
	float mappedPosY = a_imgWidth;
	float mappedWidth = a_imgY;
	float mappedHeight = a_imgHeight;

	float mappedImgX = a_posX;
	float mappedImgY = a_width;
	float mappedImgWidth = a_posY;
	float mappedImgHeight = a_height;

	float texWidth = static_cast<float>(a_texture->GetWidth());
	float texHeight = static_cast<float>(a_texture->GetHeight());

	float x1 = static_cast<float>(mappedPosX / texWidth);
	float x2 = static_cast<float>(mappedPosY / texWidth);
	float y1 = static_cast<float>(mappedWidth / texHeight);
	float y2 = static_cast<float>(mappedHeight / texHeight);

	glTexCoord2f(x1, 1 - y1); // bottom-left
	glVertex3i(mappedImgX, mappedImgWidth, 0); // top-left

	glTexCoord2f(x1 + x2, 1 - y1); // bottom-right
	glVertex3i(mappedImgX + mappedImgY, mappedImgWidth, 0); // top-right

	glTexCoord2f(x1 + x2, 1 - (y1 + y2)); // top-right
	glVertex3i(mappedImgX + mappedImgY, mappedImgWidth + mappedImgHeight, 0); // bottom-right

	glTexCoord2f(x1, 1 - (y1 + y2)); // top-left
	glVertex3i(mappedImgX, mappedImgWidth + mappedImgHeight, 0); // bottom-left

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

		source.m_x1 = (c % 16) * 16;
		source.m_y1 = (c / 16) * 16;
		source.m_x2 = 16;
		source.m_y2 = 16;

		dest.m_x1 = a_posX + counter * 16;
		dest.m_y1 = a_posY + (newLines * 16);
		dest.m_x2 = 16;
		dest.m_y2 = 16;

		if (c == '\n')
		{
			newLines++;
			counter = 0;
		}
		else
		{
			DrawTexture(dest.m_x1, dest.m_y1, dest.m_x2, dest.m_y2, a_fontTexture, source.m_x1, source.m_y1, source.m_x2, source.m_y2);
			counter++;
		}
	}
}


void CRendererOpenGL::End()
{
	SwapBuffers(m_windowDC);
}


void CRendererOpenGL::ShutdownGraphics()
{

}