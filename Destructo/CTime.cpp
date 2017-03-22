#include "CTime.h"

CTime& CTime::GetInstance()
{
	static CTime g_time;
	return g_time;
}
float CTime::DeltaTime()
{
	return m_deltaTime;
}

float CTime::TotalTime()
{
	return m_gameTimer.TotalTime();
}

void CTime::Tick()
{
	m_gameTimer.Tick();
}

void CTime::Reset()
{
	m_gameTimer.Reset();
}

void CTime::SetDeltaTime(float a_dt)
{
	m_deltaTime = a_dt;
}

CTime::CTime()
	: m_deltaTime(0.0f)
{

}


