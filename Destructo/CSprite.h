#pragma once
#include "IComponent.h"
#include "IComponentManager.h"
#include "SRect.h"


class CSprite : public IComponent
{
public:
    CSprite(CGameObject* a_owner);
    virtual ~CSprite();
    
    void Initialize() override;
    void Update() override;
    bool AddRequiredComponents(IComponentManager* a_componentManager) override;

    void SetTextureName(std::string a_textureName);
    void SetOpacityMaskName(std::string a_opacityMaskName);

    const SRect& GetImageSection() const;
    const std::string GetTextureName() const;
    const std::string GetOpacityMaskName() const;

private:
    std::string m_textureName;
    std::string m_opacityMaskName;
    SRect m_imageSection;
};

