#include "CRendererOpenGL.h"

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

	SRect source;
	source.m_x = a_imgX;
	source.m_y = a_imgWidth;
	source.m_width = a_imgY;
	source.m_height = a_imgHeight;

	SRect dest;
	dest.m_x = a_posX;
	dest.m_y = a_width;
	dest.m_width = a_posY;
	dest.m_height = a_height;

	float texWidth = static_cast<float>(a_texture->GetWidth());
	float texHeight = static_cast<float>(a_texture->GetHeight());

	dest.m_x = static_cast<float>(source.m_x / texWidth);
	dest.m_y = static_cast<float>(source.m_y / texWidth);
	dest.m_width = static_cast<float>(source.m_width / texHeight);
	dest.m_height = static_cast<float>(source.m_height / texHeight);

	glTexCoord2f(dest.m_x, 1 - dest.m_width); // bottom-left
	glVertex3f(dest.m_x, dest.m_width, 0); // top-left

	glTexCoord2f(dest.m_x + dest.m_y, 1 - dest.m_width); // bottom-right
	glVertex3f(dest.m_x + dest.m_y, dest.m_width, 0); // top-right

	glTexCoord2f(dest.m_x + dest.m_y, 1 - (dest.m_width + dest.m_height)); // top-right
	glVertex3f(dest.m_x + dest.m_y, dest.m_width + dest.m_height, 0); // bottom-right

	glTexCoord2f(dest.m_x, 1 - (dest.m_width + dest.m_height)); // top-left
	glVertex3f(dest.m_x, dest.m_width + dest.m_height, 0); // bottom-left

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

		source.m_x = (c % 16) * 16;
		source.m_y = (c / 16) * 16;
		source.m_width = 16;
		source.m_height = 16;

		dest.m_x = a_posX + counter * 16;
		dest.m_y = a_posY + (newLines * 16);
		dest.m_width = 16;
		dest.m_height = 16;

		if (c == '\n')
		{
			newLines++;
			counter = 0;
		}
		else
		{
			DrawTexture(dest.m_x, dest.m_y, dest.m_width, dest.m_height, a_fontTexture, source.m_x, source.m_y, source.m_width, source.m_height);
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