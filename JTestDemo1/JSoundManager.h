#pragma once
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#include "stdafx.h"

#pragma comment (lib, "fmod_vc.lib")

class JSoundChannel {
	std::wstring m_fileName;
	FMOD::Channel* m_pChannel;
public:
	JSoundChannel(std::wstring fileName) {
		m_fileName = fileName;
		m_pChannel = nullptr;
	}
	bool release() {
		m_pChannel->stop();
	}
};

class JSoundManager : public JSingleton<JSoundManager> {
	friend class JSingleton<JSoundManager>;
private:
	FMOD::System* m_pSystem = nullptr;
private:
	std::unordered_map<std::wstring, FMOD::Sound*> m_List;
public:
	bool init();
	bool load(FMOD::Sound* m_pSound, std::wstring fileName);
	void pause(FMOD::Channel*& m_pChannel);
	void resume(FMOD::Channel*& m_pChannel);
	void volumeUp(FMOD::Channel*& m_pChannel, float fVolume = 0.1f);
	void volumeDown(FMOD::Channel*& m_pChannel, float fVolume = 0.1f);
	bool play(std::wstring fileName, FMOD::Channel*& m_pChannel, bool bIsLoop = false);
	bool playEffect(std::wstring fileName, FMOD::Channel*& m_pChannel, bool bIsLoop = false);
	void stop(FMOD::Channel*& m_pChannel);
	void setLoop(FMOD::Sound* pSound, bool bIsLoop = false);
	bool isPlay(FMOD::Channel*& m_pChannel);
private:
	JSoundManager() {};
	~JSoundManager() = default;
	JSoundManager(const JSoundManager&) = delete;
	JSoundManager& operator=(const JSoundManager&) = delete;
};

#define I_Sound TSoundManager::GetInstance()