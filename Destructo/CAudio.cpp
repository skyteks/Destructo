#include "CAudio.h"

CAudio::CAudio()
{
}

CAudio::~CAudio()
{
}

bool CAudio::Initialize()
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

void CAudio::Shutdown()
{
    for (auto& e : m_soundMap)
    {
        e.second->release();
    }

    if (m_system)
    {
        m_system->release();
        m_system = nullptr;
    }
}

void CAudio::Update()
{
    m_system->update();
}

bool CAudio::Load(const std::string& a_path)
{
    if (m_system == nullptr)
    {
        return false;
    }

    // create new sound with default settings
    FMOD::Sound* sound = nullptr;
    if (m_system->createSound(a_path.c_str(), FMOD_DEFAULT, 0, &sound) != FMOD_OK)
    {
        return false;
    }

    if (sound)
    {
        m_soundMap[a_path] = sound;
        return true;
    }

    return false;
}

IAudioChannel* CAudio::Play(const std::string& a_path)
{
    if (m_system == nullptr)
    {
        return nullptr;
    }

    FMOD::Sound* sound = m_soundMap[a_path];


    if (!sound)
    {
        return nullptr;
    }

    // make sure the sound has loaded
    FMOD_OPENSTATE openState = FMOD_OPENSTATE_ERROR;
    bool disk = false;
    sound->getOpenState(&openState, nullptr, nullptr, &disk);
    if (openState != FMOD_OPENSTATE_READY && openState != FMOD_OPENSTATE_PLAYING)
    {
        return nullptr;
    }

    FMOD::Channel* channel = nullptr;

    // play sound, for now just one channel...
    if (m_system->playSound(sound, 0, false, &channel) != FMOD_OK)
    {
        return nullptr;
    }

    CAudioChannel* audioChannel = &m_channelMap[channel];
    audioChannel->SetChannel(channel);

    // RETURN SOUND
    return audioChannel;
}