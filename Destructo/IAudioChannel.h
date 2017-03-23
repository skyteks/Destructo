#pragma once

class IAudioChannel
{
public:

  virtual void SetMute(bool a_isMuted) = 0;
  virtual void SetPaused(bool a_isPaused) = 0;
  virtual void SetPitch(float a_pitch) = 0;
  virtual void SetVolume(float a_volume) = 0;

  virtual ~IAudioChannel() {};
};
