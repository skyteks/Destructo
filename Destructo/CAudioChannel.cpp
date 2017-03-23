#include "CAudioChannel.h"

CAudioChannel::CAudioChannel()
  : m_channel(nullptr)
{
}

CAudioChannel::~CAudioChannel()
{
  m_channel = nullptr;
}

void CAudioChannel::SetMute(bool a_isMuted)
{
  if (m_channel)
  {
    m_channel->setMute(a_isMuted);
  }
}

void CAudioChannel::SetPaused(bool a_isPaused)
{
  if (m_channel)
  {
    m_channel->setPaused(a_isPaused);
  }
}

void CAudioChannel::SetPitch(float a_pitch)
{
  if (m_channel)
  {
    m_channel->setPitch(a_pitch);
  }
}

void CAudioChannel::SetVolume(float a_volume)
{
  if (m_channel)
  {
    m_channel->setVolume(a_volume);
  }
}

void CAudioChannel::SetChannel(FMOD::Channel* a_channel)
{
  m_channel = a_channel;
}

FMOD::Channel * CAudioChannel::GetChannel() const
{
  return m_channel;
}
