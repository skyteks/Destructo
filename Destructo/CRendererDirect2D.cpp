#include "CRendererDirect2D.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CSprite.h"

CRendererDirect2D::CRendererDirect2D()
    : m_imageFactory(nullptr)
    , m_renderTarget(nullptr)
    , m_writeFactory(nullptr)
    , m_writeTextFormat(nullptr)
    , m_colorBrush(nullptr)
    , m_clearColor(0)
{
}


CRendererDirect2D::~CRendererDirect2D()
{
}


bool CRendererDirect2D::Initialize(HWND a_hwnd)
{
    m_windowHandle = a_hwnd;
    m_windowDC = GetDC(a_hwnd);

    bool wResult = false;

    // create imageFactory
    HRESULT hResult = D2D1CreateFactory<ID2D1Factory>(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_imageFactory);
    if (m_imageFactory == nullptr)
    {
        return false;
    }

    // create render target
    //ComPtr<ID2D1Effect> blendEffect;
    //m_d2dContext->CreateEffect(CLSID_D2D1Blend, &blendEffect);

    //blendEffect->SetInput(0, bitmap);
    //blendEffect->SetInput(1, bitmapTwo);
    //blendEffect->SetValue(D2D1_BLEND_PROP_MODE, D2D1_BLEND_MODE_EXCLUSION);

    //m_d2dContext->BeginDraw();
    //m_d2dContext->DrawImage(blendEffect.Get());
    //m_d2dContext->EndDraw();


    // get window borders
    RECT rc;
    wResult = GetClientRect(m_windowHandle, &rc);
    if (!wResult)
        return false;
    m_windowWidth = rc.right;
    m_windowHeight = rc.bottom;

    D2D1_SIZE_U size = D2D1::SizeU(
        rc.right - rc.left,
        rc.bottom - rc.top);

    hResult = m_imageFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(m_windowHandle, size, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
        &m_renderTarget);

    if (m_renderTarget == nullptr)
        return false;
    else
    {
        // set global renderTarget to current renderTarget, to create bitmaps from it
        CTextureDirect2D::s_renderTarget = m_renderTarget;
    }

    // create brush
    hResult = m_renderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::Yellow),
        &m_colorBrush);
    if (m_colorBrush == nullptr)
        return false;

    // set clear color
    D2D1::ColorF clr(RGB(255, 0, 255), 255.0f);
    m_clearColor = clr;

    // create writefactory to create text
    hResult = DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(m_writeFactory),
        reinterpret_cast<IUnknown **>(&m_writeFactory));
    if (m_writeFactory == nullptr)
        return false;

    // create textformat object
    hResult = m_writeFactory->CreateTextFormat(
        L"OCR A Std", // font
        nullptr,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        14, // size
        L"",
        &m_writeTextFormat
    );

    return true;
}


ITexture* CRendererDirect2D::LoadTextureFromFile(std::string a_path)
{
    return new CTextureDirect2D(a_path);
}


void CRendererDirect2D::Begin()
{
    m_renderTarget->BeginDraw();
}

void CRendererDirect2D::DrawObject(CGameObject& a_gameObject)
{
    const CTextureDirect2D* direct2DTexture = reinterpret_cast<const CTextureDirect2D*>(CTextureManager::GetInstance().GetTextureByName(a_gameObject.GetComponent<CSprite>()->GetTextureName()));
    const CTextureDirect2D* direct2DOpacityMask = nullptr;
    if (a_gameObject.GetComponent<CSprite>()->GetOpacityMaskName() != "")
    {
        direct2DOpacityMask = reinterpret_cast<const CTextureDirect2D*>(CTextureManager::GetInstance().GetTextureByName(a_gameObject.GetComponent<CSprite>()->GetOpacityMaskName()));
    }

    SVector3 position = a_gameObject.GetComponent<CTransform>()->GetPosition();
    SVector3 scale = a_gameObject.GetComponent<CTransform>()->GetScale();
    SMatrix4x4 rotation = SMatrix4x4::RotationZ(a_gameObject.GetComponent<CTransform>()->GetRotation().z);

    D2D1_RECT_F direct2DSource;
    direct2DSource.left = a_gameObject.GetComponent<CSprite>()->GetImageSection().x1;
    direct2DSource.top = a_gameObject.GetComponent<CSprite>()->GetImageSection().y1;
    direct2DSource.right = a_gameObject.GetComponent<CSprite>()->GetImageSection().x2;
    direct2DSource.bottom = a_gameObject.GetComponent<CSprite>()->GetImageSection().y2;

    D2D1_RECT_F direct2DDest;
    direct2DDest.left = position.x;
    direct2DDest.top = position.y;
    direct2DDest.right = position.x + direct2DTexture->GetWidth() * scale.x;
    direct2DDest.bottom = position.y + direct2DTexture->GetHeight() * scale.y;

    D2D1_MATRIX_3X2_F direct2DRot;
    direct2DRot._11 = rotation.m11;
    direct2DRot._12 = rotation.m12;
    direct2DRot._21 = rotation.m21;
    direct2DRot._22 = rotation.m22;
    direct2DRot._31 = rotation.m31;
    direct2DRot._32 = rotation.m32;
    m_renderTarget->SetTransform(direct2DRot);

    m_renderTarget->DrawBitmap(direct2DTexture->GetBitmapHandle(), direct2DDest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, direct2DSource);
}


void CRendererDirect2D::DrawTexture(int a_posX, int a_posY, int a_width, int a_height, const ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight)
{
    const CTextureDirect2D* direct2DTexture = reinterpret_cast<const CTextureDirect2D*>(a_texture);

    D2D1_RECT_F direct2DSource;
    direct2DSource.left = static_cast<float>(a_imgX);
    direct2DSource.top = static_cast<float>(a_imgY);
    direct2DSource.right = static_cast<float>(a_imgWidth);
    direct2DSource.bottom = static_cast<float>(a_imgHeight);

    D2D1_RECT_F direct2DDest;
    direct2DDest.left = static_cast<float>(a_posX);
    direct2DDest.top = static_cast<float>(a_posY);
    direct2DDest.right = static_cast<float>(a_posX + a_width);
    direct2DDest.bottom = static_cast<float>(a_posY + a_height);

    SMatrix4x4 rotation = SMatrix4x4::Identity();

    D2D1_MATRIX_3X2_F direct2DRot;
    direct2DRot._11 = rotation.m11;
    direct2DRot._12 = rotation.m12;
    direct2DRot._21 = rotation.m21;
    direct2DRot._22 = rotation.m22;
    direct2DRot._31 = rotation.m31;
    direct2DRot._32 = rotation.m32;
    m_renderTarget->SetTransform(direct2DRot);

    m_renderTarget->DrawBitmap(direct2DTexture->GetBitmapHandle(), direct2DDest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, direct2DSource);
}

void CRendererDirect2D::DrawTextureWithOpacityMask(int a_posX, int a_posY, int a_width, int a_height, const ITexture* a_texture, int a_imgX, int a_imgY, int a_imgWidth, int a_imgHeight, const ITexture* a_opacityMask)
{

}


void CRendererDirect2D::DrawString(int a_posX, int a_posY, const char* a_string, int a_textColor, int a_backgroundColor, UINT a_format, const ITexture* a_fontTexture)
{
    if (a_string == nullptr)
        return;

    if (a_fontTexture == nullptr)
    {
        RECT rect;
        GetClientRect(m_windowHandle, &rect);

        uint32_t textLength = strlen(a_string);

        D2D1_RECT_F layoutRect = D2D1::RectF(
            static_cast<float>(a_posX),
            static_cast<float>(a_posY),
            static_cast<float>(a_posX + textLength * m_writeTextFormat->GetFontSize()), // X +  chars count * charactersize
            static_cast<float>(a_posY + textLength * m_writeTextFormat->GetFontSize()));

        // convert color to D2D1_COLOR_F
        D2D1::ColorF colorConverter = D2D1::ColorF(a_textColor, 1.0f);

        // set new brush color        
        m_colorBrush->SetColor(NewColor(a_textColor));


        wchar_t wtext[MAX_PATH] = {};
        mbstowcs(wtext, a_string, textLength + 1);//Plus null

        m_renderTarget->DrawText(
            wtext,
            textLength,
            m_writeTextFormat,
            layoutRect,
            m_colorBrush);
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


void CRendererDirect2D::End()
{
    m_renderTarget->EndDraw();
}


void CRendererDirect2D::Shutdown()
{
    SafeRelease(m_imageFactory);
    SafeRelease(m_renderTarget);
    SafeRelease(m_colorBrush);
    SafeRelease(m_writeFactory);
    SafeRelease(m_writeTextFormat);
}

D2D1_COLOR_F CRendererDirect2D::NewColor(int a_color)
{
    // convert color to D2D1_COLOR_F
    D2D1::ColorF colorConverter = D2D1::ColorF(a_color, 1.0f);

    // rotating BGR to RGB
    if (true)// for easy toggle
    {
        float newR = colorConverter.b;
        colorConverter.b = colorConverter.r;
        colorConverter.r = newR;
    }

    D2D1_COLOR_F newColor;
    newColor.a = colorConverter.a;
    newColor.r = colorConverter.r;
    newColor.g = colorConverter.g;
    newColor.b = colorConverter.b;
    return newColor;
}

void CRendererDirect2D::Clear(int a_color)
{
    m_renderTarget->Clear(NewColor(a_color));
}
