#pragma once

#include <fmod.hpp>
#include <fmod_errors.h>

#include "IAudioChannel.h"

class CAudioChannel : public IAudioChannel
{
public:
  CAudioChannel();
  ~CAudioChannel();

  // Interface functions
  void SetMute(bool a_isMuted) override;
  void SetPaused(bool a_isPaused) override;
  void SetPitch(float a_pitch) override;
  void SetVolume(float a_volume) override;

  // Custom functions
  void SetChannel(FMOD::Channel* a_channel);
  FMOD::Channel* GetChannel() const;

private:
  FMOD::Channel* m_channel;
};
