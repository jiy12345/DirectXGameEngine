#include "JSoundManager.h"

bool JSoundManager::init()
{
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
}

bool JSoundManager::load(FMOD::Sound* m_pSound, std::wstring fileName)
{
	auto iter = m_List.find(fileName);
	if (iter != m_List.end())
	{
		return iter->second;
	}
	FMOD::Sound* pSound = nullptr;
	FMOD_RESULT hr = m_pSystem->createSound(
		to_wm(fileName).c_str(),
		FMOD_DEFAULT, nullptr,
		&pSound);

	return (hr == FMOD_OK) ? true : false;
}

void JSoundManager::pause(FMOD::Channel*& m_pChannel)
{
	if (m_pChannel == nullptr) return;
	bool isPaused;
	m_pChannel->getPaused(&isPaused);
	if(isPaused == false)m_pChannel->setPaused(true);
}

void JSoundManager::resume(FMOD::Channel*& m_pChannel)
{
	if (m_pChannel == nullptr) return;
	bool isPaused;
	m_pChannel->getPaused(&isPaused);
	if (isPaused == true)m_pChannel->setPaused(false);
}

void JSoundManager::volumeUp(FMOD::Channel*& m_pChannel, float fVolume)
{
	float fCurVolume = 0.0f;
	m_pChannel->getVolume(&fCurVolume);
	fCurVolume += fVolume;
	fCurVolume = min(1.0f, fCurVolume);
	m_pChannel->setVolume(fCurVolume);
}

void JSoundManager::volumeDown(FMOD::Channel*& m_pChannel, float fVolume)
{
	float fCurVolume = 0.0f;
	m_pChannel->getVolume(&fCurVolume);
	fCurVolume -= fVolume;
	fCurVolume = min(1.0f, fCurVolume);
	m_pChannel->setVolume(fCurVolume);
}

bool JSoundManager::play(std::wstring fileName, FMOD::Channel*& m_pChannel, bool bIsLoop)
{
	FMOD::Sound* pSound = nullptr;
	load(pSound, fileName);
	if (isPlay(m_pChannel) == false)
	{
		FMOD_RESULT hr =
			m_pSystem->playSound(pSound, nullptr, false,
				&m_pChannel);
		if (hr == FMOD_OK)
		{
			m_pChannel->setVolume(0.5f);
			setLoop(pSound, bIsLoop);
		}
	}
	return true;
}

bool JSoundManager::playEffect(std::wstring fileName, FMOD::Channel*& m_pChannel, bool bIsLoop)
{
	FMOD::Sound* pSound = nullptr;
	load(pSound, fileName);
	FMOD_RESULT hr =
		m_pSystem->playSound(pSound, nullptr, false,
			&m_pChannel);
	if (hr == FMOD_OK)
	{
		m_pChannel->setVolume(0.5f);
		setLoop(pSound, bIsLoop);
	}
	return true;
}

void JSoundManager::stop(FMOD::Channel*& m_pChannel)
{
	m_pChannel->stop();
}

void JSoundManager::setLoop(FMOD::Sound* pSound, bool bIsLoop)
{
	if (bIsLoop)
		pSound->setMode(FMOD_LOOP_NORMAL);
	else
		pSound->setMode(FMOD_LOOP_OFF);
}

bool JSoundManager::isPlay(FMOD::Channel*& m_pChannel)
{
	bool playing = false;
	if (m_pChannel != nullptr)
	{
		m_pChannel->isPlaying(&playing);
	}
	return playing;
}
