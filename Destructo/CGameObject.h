#pragma once
#include "SVector3.h"
#include "ITexture.h"
#include "SRect.h"
#include "SMatrix4x4.h"
#include "GlobalFunctions.h"
#include "IComponentManager.h"
#include "CTransform.h"

class CGameObject : IComponentManager
{
public:
    CGameObject();

    CGameObject(SVector3 a_position, SVector3 a_scale, float a_rotation, std::string a_textureName, std::string a_opacityMask);

    virtual ~CGameObject();

    void SetPosition(SVector3 a_position);
    void SetRotation(float a_rotation);
    void AddRotation(float a_rotation);
    void SetScale(SVector3 a_scale);

    const SVector3& GetPosition() const;
    const SMatrix4x4& GetRotation() const;
    float GetRotationAngle() const;
    const SVector3& GetScale() const;
    const SRect& GetImageSection() const;

    const std::string GetTextureName() const;
    const std::string GetOpacityMaskName() const;

    void Start();
    void Update();

private:
    SVector3 m_position;
    SVector3 m_scale;
    std::string m_textureName;
    std::string m_opacityMaskName;
    SRect m_imageSection;
    float m_rotationAngle;
    SMatrix4x4 m_rotationMatrix;
};