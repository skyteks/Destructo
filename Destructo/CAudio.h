#pragma once

#include <fmod.hpp>
#include <fmod_errors.h>
#include <map>
#include <string>

#define AUDIO_MAX_CHANNEL 128

#pragma comment(lib, "fmod_vc.lib")

#include "IAudio.h"
#include "CAudioChannel.h"
#include "GlobalFunctions.h"

typedef std::map<std::string, FMOD::Sound*> SoundMap;
typedef std::map<FMOD::Channel*, CAudioChannel> ChannelMap;

class CAudio : public IAudio
{
public:
    CAudio();
    ~CAudio();

    // Interface functions
    bool Initialize() override;
    void Shutdown() override;
    void Update() override;
    bool Load(const std::string& a_path) override;
    IAudioChannel* Play(const std::string& a_path) override;

private:
    SoundMap m_soundMap;
    ChannelMap m_channelMap;
    FMOD::System* m_system;
};