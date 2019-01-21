#include "CRendererOpenGL.h"
#include "DataNames.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CSprite.h"
#include "ERenderer.h"

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


ITexture* CRendererOpenGL::LoadTextureFromFile(std::string a_path)
{
    return new CTextureOpenGL(a_path);
}


void CRendererOpenGL::Begin()
{
    //SwapBuffers(windowDC);

    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void CRendererOpenGL::DrawObject(CGameObject& a_gameObject)
{
    CSprite* tmpSprite = a_gameObject.GetComponent<CSprite>();
    CTransform* tmpTransform = a_gameObject.GetComponent<CTransform>();
    CTextureManager& tmpTextureManager = CTextureManager::GetInstance();

    const CTextureOpenGL* openGLTexture = reinterpret_cast<const CTextureOpenGL*>(tmpTextureManager.GetTextureByName(tmpSprite->GetTextureName()));
    const CTextureOpenGL* openGLOpacityMask = nullptr;
    if (tmpSprite->GetOpacityMaskName() != "")
    {
        openGLOpacityMask = reinterpret_cast<const CTextureOpenGL*>(tmpTextureManager.GetTextureByName(tmpSprite->GetOpacityMaskName()));
        openGLTexture->AddOpacityMask(openGLOpacityMask);
    }

    SVector3 position = tmpTransform->GetPosition();
    SVector3 scale = tmpTransform->GetScale();

    glBindTexture(GL_TEXTURE_2D, openGLTexture->GetTextureID());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    SRect<float> source = tmpSprite->GetImageSection();

    SRect<float> dest;
    dest.x1 = position.x;
    dest.y1 = position.y;
    dest.x2 = openGLTexture->GetWidth() * scale.x;
    dest.y2 = openGLTexture->GetHeight() * scale.y;

    float texWidth = static_cast<float>(openGLTexture->GetWidth());
    float texHeight = static_cast<float>(openGLTexture->GetHeight());

    SRect<float> tex;
    tex.x1 = source.x1 / texWidth;
    tex.x2 = source.x2 / texWidth;
    tex.y1 = source.y1 / texHeight;
    tex.y2 = source.y2 / texHeight;

    // rotate
    if (dest.x1 != 0.0f && dest.y1 != 0.0f)
    {
        dest.x1 -= position.x + dest.x2 / 2;
        dest.y1 -= position.y + dest.y2 / 2;
    }

    SVector3 vec1(dest.x1, dest.y1);
    SVector3 vec2(dest.x1 + dest.x2, dest.y1);
    SVector3 vec3(dest.x1 + dest.x2, dest.y1 + dest.y2);
    SVector3 vec4(dest.x1, dest.y1 + dest.y2);
    SMatrix4x4 rotation = SMatrix4x4::RotationZ(tmpTransform->GetRotation().z);

    SVector4 point1 = rotation * vec1;
    SVector4 point2 = rotation * vec2;
    SVector4 point3 = rotation * vec3;
    SVector4 point4 = rotation * vec4;

    if (dest.x1 != 0.0f && dest.y1 != 0.0f)
    {
        dest.x1 += position.x + dest.x2 / 2;
        dest.y1 += position.y + dest.y2 / 2;
    }

    point1.x += dest.x1;
    point2.x += dest.x1;
    point3.x += dest.x1;
    point4.x += dest.x1;

    point1.y += dest.y1;
    point2.y += dest.y1;
    point3.y += dest.y1;
    point4.y += dest.y1;

    glTexCoord2f(tex.x1, 1 - tex.y1); // bottom-left
    glVertex3f(point1.x, point1.y, 0); // topleft

    glTexCoord2f(tex.x1 + tex.x2, 1 - tex.y1); // bottom-right
    glVertex3f(point2.x, point2.y, 0); // topright ==> Vector2 * rotationmatrix ==> rotated Vector2

    glTexCoord2f(tex.x1 + tex.x2, 1 - (tex.y1 + tex.y2)); // top-right
    glVertex3f(point3.x, point3.y, 0); // bottomright

    glTexCoord2f(tex.x1, 1 - (tex.y1 + tex.y2)); // top-left
    glVertex3f(point4.x, point4.y, 0); // bottomleft

    glEnd();
}

void CRendererOpenGL::DrawTexture(int a_posX, int a_posY, int a_width, int a_height, const ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight)
{
    const CTextureOpenGL* openGLTexture = static_cast<const CTextureOpenGL*>(a_texture);

    glBindTexture(GL_TEXTURE_2D, openGLTexture->GetTextureID());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    SRect<float> source;
    source.x1 = static_cast<float>(a_imgX);
    source.x2 = static_cast<float>(a_imgWidth);
    source.y1 = static_cast<float>(a_imgY);
    source.y2 = static_cast<float>(a_imgHeight);

    SRect<float> dest;
    dest.x1 = static_cast<float>(a_posX);
    dest.x2 = static_cast<float>(a_width);
    dest.y1 = static_cast<float>(a_posY);
    dest.y2 = static_cast<float>(a_height);

    float texWidth = static_cast<float>(a_texture->GetWidth());
    float texHeight = static_cast<float>(a_texture->GetHeight());

    SRect<float> tex;
    tex.x1 = source.x1 / texWidth;
    tex.x2 = source.x2 / texWidth;
    tex.y1 = source.y1 / texHeight;
    tex.y2 = source.y2 / texHeight;

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

void CRendererOpenGL::DrawTextureWithOpacityMask(int a_posX, int a_posY, int a_width, int a_height, const ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight, const ITexture* a_opacityMask)
{
    const CTextureOpenGL* openGLTexture = static_cast<const CTextureOpenGL*>(a_texture);
    const CTextureOpenGL* openGLOpacityMask = static_cast<const CTextureOpenGL*>(a_opacityMask);

    openGLTexture->AddOpacityMask(openGLOpacityMask);

    glBindTexture(GL_TEXTURE_2D, openGLTexture->GetTextureID());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    SRect<float> source;
    source.x1 = static_cast<float>(a_imgX);
    source.x2 = static_cast<float>(a_imgWidth);
    source.y1 = static_cast<float>(a_imgY);
    source.y2 = static_cast<float>(a_imgHeight);

    SRect<float> dest;
    dest.x1 = static_cast<float>(a_posX);
    dest.x2 = static_cast<float>(a_width);
    dest.y1 = static_cast<float>(a_posY);
    dest.y2 = static_cast<float>(a_height);

    float texWidth = static_cast<float>(a_texture->GetWidth());
    float texHeight = static_cast<float>(a_texture->GetHeight());

    SRect<float> tex;
    tex.x1 = source.x1 / texWidth;
    tex.x2 = source.x2 / texWidth;
    tex.y1 = source.y1 / texHeight;
    tex.y2 = source.y2 / texHeight;

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

void CRendererOpenGL::DrawString(int a_posX, int a_posY, const char* a_string, int a_textColor, int a_backgroundColor, UINT a_format, const ITexture* a_fontTexture)
{
    if (a_string == nullptr)
        return;

    SRect<int> source;
    SRect<int> dest;

    uint32_t counter = 0;
    uint32_t newLines = 0;

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


ERenderer CRendererOpenGL::GetRendererType()
{
    return ERenderer::OpenGL;
}