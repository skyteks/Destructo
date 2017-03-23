#pragma once

#include <string>

#include "IAudioChannel.h"

class IAudio
{
public:
  virtual bool Initialize() = 0;
  virtual void Shutdown() = 0;
  virtual void Update() = 0;

  virtual bool Load(const std::string& a_path) = 0;
  virtual IAudioChannel* Play(const std::string& a_path) = 0;

  virtual ~IAudio() {};
};
