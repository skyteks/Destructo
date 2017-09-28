#include "CSprite.h"
#include "ITexture.h"
#include "CTextureManager.h"

CSprite::CSprite(CGameObject* a_owner)
    : IComponent(a_owner)
    , m_textureName("")
    , m_opacityMaskName("")
    , m_imageSection()
{
}


CSprite::~CSprite()
{
}


const SRect<float> CSprite::GetImageSection() const
{
    return m_imageSection;
}


const std::string CSprite::GetTextureName() const
{
    return m_textureName;
}


const std::string CSprite::GetOpacityMaskName() const
{
    return m_opacityMaskName;
}

void CSprite::Initialize()
{
}

void CSprite::Update()
{
}

bool CSprite::AddRequiredComponents(IComponentManager* a_componentManager)
{
    return true;
}

void CSprite::SetTextureName(std::string a_textureName)
{
    m_textureName = a_textureName;

    const ITexture* texture = CTextureManager::GetInstance().GetTextureByName(a_textureName);
    if (texture != nullptr)
    {
        m_imageSection.x1 = 0.0f;
        m_imageSection.y1 = 0.0f;
        m_imageSection.x2 = static_cast<float>(texture->GetWidth());
        m_imageSection.y2 = static_cast<float>(texture->GetHeight());
    }
}

void CSprite::SetOpacityMaskName(std::string a_opacityMaskName)
{
    m_opacityMaskName = a_opacityMaskName;
}
