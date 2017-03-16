#pragma once


class ISoundEngine
{
public:
	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual void* LoadSound(const char* a_file) = 0;
	virtual void UnloadSound(void*& a_sound) = 0;
	virtual bool PlaySoundOneShot(void* a_sound) = 0;
	virtual void Update() = 0;
	virtual ~ISoundEngine() {}
};
