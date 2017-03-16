#include "CSoundEngine.h"

CSoundEngine::CSoundEngine()
	: m_system(nullptr)
{

}

CSoundEngine::~CSoundEngine()
{
	Shutdown();
}

bool CSoundEngine::Initialize()
{
	if (FMOD::System_Create(&m_system) != FMOD_OK)
	{
		// error on initialize
		return false;
	}

	int driverCount = 0;
	m_system->getNumDrivers(&driverCount);

	if (driverCount == 0)
	{
		// no driver...
		return false;
	}

	if (m_system->init(AUDIO_MAX_CHANNEL, FMOD_INIT_NORMAL, nullptr) != FMOD_OK)
	{
		// init failed
		return false;
	}

	return true;
}

void CSoundEngine::Shutdown()
{
	if (m_system)
	{
		m_system->close();
		m_system->release();
		m_system = nullptr;
	}
}

void* CSoundEngine::LoadSound(const char * a_file)
{
	if (m_system == nullptr || a_file == nullptr)
	{
		return nullptr;
	}

	// create new sound with default settings
	FMOD::Sound* sound = nullptr;
	m_system->createSound(a_file, FMOD_DEFAULT, 0, &sound);

	return sound;
}

void CSoundEngine::UnloadSound(void*& a_sound)
{
	if (a_sound == nullptr)
	{
		return;
	}

	FMOD::Sound* sound = reinterpret_cast<FMOD::Sound*>(a_sound);

	sound->release();
	a_sound = nullptr;
}

bool CSoundEngine::PlaySoundOneShot(void* a_sound)
{
	if (a_sound == nullptr || m_system == nullptr)
	{
		return false;
	}

	FMOD::Sound* sound = reinterpret_cast<FMOD::Sound*>(a_sound);

	// play sound, for now just one channel...
	if (m_system->playSound(sound, 0, false, nullptr) != FMOD_OK)
	{
		return false;
	}

	return true;
}

void CSoundEngine::Update()
{
	if (m_system)
	{
		m_system->update();
	}


}

