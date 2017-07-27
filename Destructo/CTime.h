#pragma once

#include "CGameTimer.h"

class CTime
{
public:
    static CTime& GetInstance();
    float DeltaTime();
    float TotalTime();
    void Tick();
    void Reset();

    void SetDeltaTime(float a_dt);

private:
    CTime();
    CTime(const CTime&);
    CGameTimer m_gameTimer;

    float m_deltaTime;
};

