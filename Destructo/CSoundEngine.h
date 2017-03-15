#pragma once


#include "fmod.hpp"
#include "fmod_errors.h"

#include "ISoundEngine.h"

#define AUDIO_MAX_CHANNEL 128

#pragma comment(lib, "fmod_vc.lib")

class CSoundEngine : public ISoundEngine
{
public:
  CSoundEngine();
  ~CSoundEngine();

  // interface functions
  bool Initialize() override;
  void Shutdown() override;
  void* LoadSound(const char* a_file) override;
  void UnloadSound(void*& a_sound) override;
  bool PlaySoundOneShot(void* a_sound) override;
  void Update() override;

private:
  FMOD::System* m_system;
};