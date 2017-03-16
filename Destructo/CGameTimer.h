#pragma once

class CGameTimer
{
public:
	CGameTimer();

	float TotalTime() const;  // in seconds
	float DeltaTime() const; // in seconds

	void Reset(); // Call before message loop.
	void Tick();  // Call every frame.
	void Pause(); // Unpause
	void Unpause(); // Pause

private:
	__int64 m_frequency;
	__int64 m_baseTime;
	__int64 m_deltaTime;
	__int64 m_pauseTimeStart;

	float m_pauseTime;
	float m_currentDeltaTime;

};

