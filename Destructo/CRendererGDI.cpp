#include "CRendererGDI.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CSprite.h"
#include "ERenderer.h"

CRendererGDI::CRendererGDI()
{
}


CRendererGDI::~CRendererGDI()
{
}


bool CRendererGDI::Initialize(HWND a_hwnd)
{
    m_windowHandle = a_hwnd;

    m_windowDC = GetDC(m_windowHandle);

    bool wResult = false;

    RECT rc;
    wResult = GetClientRect(m_windowHandle, &rc);
    if (!wResult)
        return false;
    m_windowWidth = rc.right;
    m_windowHeight = rc.bottom;



    m_backBufferBitmap = CreateCompatibleBitmap(m_windowDC, m_windowWidth, m_windowHeight);
    m_backbufferDC = CreateCompatibleDC(m_windowDC);
    HBITMAP tmpBmp = (HBITMAP)SelectObject(m_backbufferDC, m_backBufferBitmap);

    wResult = DeleteObject(tmpBmp);
    if (!wResult)
        return false;

    return true;
}


ITexture* CRendererGDI::LoadTextureFromFile(std::string a_path)
{
    return new CTextureGDI(a_path);
}


void CRendererGDI::DrawObject(CGameObject& a_gameObject)
{
    CSprite* tmpSprite = a_gameObject.GetComponent<CSprite>();
    CTransform* tmpTransform = a_gameObject.GetComponent<CTransform>();
    CTextureManager& tmpTextureManager = CTextureManager::GetInstance();

    const CTextureGDI* gdiTexture = static_cast<const CTextureGDI*>(tmpTextureManager.GetTextureByName(tmpSprite->GetTextureName()));
    const CTextureGDI* gdiOpacityMask = nullptr;
    if (tmpSprite->GetOpacityMaskName() != "")
    {
        gdiOpacityMask = static_cast<const CTextureGDI*>(tmpTextureManager.GetTextureByName(tmpSprite->GetOpacityMaskName()));
    }

    SVector3 position = tmpTransform->GetPosition();
    SVector3 scale = tmpTransform->GetScale();

    SRect<float> source = tmpSprite->GetImageSection();

    SRect<float> dest;
    dest.x1 = position.x;
    dest.y1 = position.y;
    dest.x2 = gdiTexture->GetWidth() * scale.x;
    dest.y2 = gdiTexture->GetHeight() * scale.y;

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

    POINT points[3];
    points[0].x = static_cast<long>(point1.x);
    points[0].y = static_cast<long>(point1.y);

    points[1].x = static_cast<long>(point2.x);
    points[1].y = static_cast<long>(point2.y);

    points[2].x = static_cast<long>(point4.x);
    points[2].y = static_cast<long>(point4.y);

    if (gdiOpacityMask != nullptr)
    {
        PlgBlt(m_backbufferDC, points, gdiTexture->GetBitmapDeviceContect(), static_cast<int>(source.x1), static_cast<int>(source.y1), static_cast<int>(source.x2), static_cast<int>(source.y2), gdiOpacityMask->GetBitmapHandle(), static_cast<int>(source.x1), static_cast<int>(source.y1));
    }
    else
    {
        PlgBlt(m_backbufferDC, points, gdiTexture->GetBitmapDeviceContect(), static_cast<int>(source.x1), static_cast<int>(source.y1), static_cast<int>(source.x2), static_cast<int>(source.y2), nullptr, 0, 0);
    }
    //PlgBlt(m_backbufferDC, points, gdiTexture->GetBitmapDeviceContect(), source.x1, source.y1, source.x2, source.y2, (gdiOpacityMask != nullptr ? gdiOpacityMask->GetBitmapHandle() : nullptr), 0, 0);
}


void CRendererGDI::DrawTexture(int a_posX, int a_posY, int a_width, int a_height, const ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight)
{
    const CTextureGDI* gdiTexture = static_cast<const CTextureGDI*>(a_texture);
    TransparentBlt(m_backbufferDC, a_posX, a_posY, a_width, a_height, gdiTexture->GetBitmapDeviceContect(), a_imgX, a_imgY, a_imgWidth, a_imgHeight, RGB(255, 0, 255));
}


void CRendererGDI::DrawTextureWithOpacityMask(int a_posX, int a_posY, int a_width, int a_height, const ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight, const ITexture* a_opacityMask)
{
    const CTextureGDI* gdiTexture = static_cast<const CTextureGDI*>(a_texture);
    const CTextureGDI* gdiOpacityMask = nullptr;
    if (a_opacityMask != nullptr)
    {
        gdiOpacityMask = static_cast<const CTextureGDI*>(a_opacityMask);
    }

    int texWidth = gdiTexture->GetWidth();
    int texHeight = gdiTexture->GetHeight();

    SRect<int> tex;
    tex.x1 = a_imgX / texWidth;
    tex.x2 = a_imgWidth / texWidth;
    tex.y1 = a_imgY / texHeight;
    tex.y2 = a_imgWidth / texHeight;

    POINT points[3];
    points[0].x = a_posX;
    points[0].y = a_posY;

    points[1].x = a_posX + a_width;
    points[1].y = a_posY;

    points[2].x = a_posX;
    points[2].y = a_posY + a_height;

    PlgBlt(m_backbufferDC, points, gdiTexture->GetBitmapDeviceContect(), tex.x1, tex.y1, tex.x2, tex.y2, (gdiOpacityMask != nullptr ? gdiOpacityMask->GetBitmapHandle() : nullptr), 0, 0);
    TransparentBlt(m_backbufferDC, a_posX, a_posY, a_width, a_height, gdiTexture->GetBitmapDeviceContect(), a_imgX, a_imgY, a_imgWidth, a_imgHeight, RGB(255, 0, 255));
}


//void CRendererGDI::MakeCircleInTexture(int a_posX, int a_posY, CTextureGDI* a_texture, int a_color, int a_radius)
//{
//	if (a_texture->GetWidth() < a_posX - a_radius || a_texture->GetHeight() < a_posY - a_radius || a_posX + a_radius < 0 || a_posY + a_radius < 0 || a_radius == 0)
//		return;
//
//	Ellipse(a_texture->GetBitmapDeviceContect(), a_posX, a_posY, a_posX - a_radius, a_posY - a_radius);
//	//for (int y = a_posY; y < a_posY - a_radius; y++)
//	//{
//	//	for (int x = a_posX; x < a_posX - a_radius; x++)
//	//	{
//	//		//SetPixel(a_texture->GetBitmapDeviceContect(), x, y, 255 * 255 * 255);
//	//	}
//	//}
//}


void CRendererGDI::DrawString(int a_posX, int a_posY, const char* a_string, int a_textColor, int a_backgroundColor, UINT a_format, const ITexture* a_fontTexture)
{
    if (a_string == nullptr)
        return;

    if (a_fontTexture == nullptr)
    {
        RECT rc;
        rc.top = a_posY;
        rc.left = a_posX;
        rc.right = m_windowWidth;
        rc.bottom = m_windowHeight;

        int oldTextColor = GetTextColor(m_backbufferDC);
        int oldBkMode = GetBkMode(m_backbufferDC);

        SetBkMode(m_backbufferDC, TRANSPARENT);
        SetTextColor(m_backbufferDC, a_textColor);

        //DrawText(backbufferDC, string, -1, &rc, DT_TOP | DT_LEFT);
        DrawText(m_backbufferDC, a_string, -1, &rc, DT_CALCRECT);
        DrawText(m_backbufferDC, a_string, -1, &rc, a_format);

        SetBkColor(m_backbufferDC, oldBkMode);
        SetTextColor(m_backbufferDC, oldTextColor);
    }
    else
    {
        SRect<int> source;
        SRect<int> dest;

        uint32_t counter = 0;
        uint32_t newLines = 0;

        while (*a_string)
        {
            unsigned char c = *a_string++;

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
}


void CRendererGDI::Begin()
{
    BitBlt(m_windowDC, 0, 0, m_windowWidth, m_windowHeight, m_backbufferDC, 0, 0, SRCCOPY);
}


void CRendererGDI::End()
{

}


void CRendererGDI::Shutdown()
{

}


ERenderer CRendererGDI::GetRendererType()
{
    return ERenderer::GDI;
}
