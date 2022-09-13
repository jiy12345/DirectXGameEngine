#pragma once
#include"stdafx.h"

class JGameEngine: public JSingleton<JGameEngine>
{
	friend class JSingleton<JGameEngine>;
public:
	bool m_bGameRun = true;
private:
	bool engineInit();
	bool engineFrame();
	bool engineRender();
	bool engineRelease();
public:
	bool run();
private:
	JGameEngine() {};
	~JGameEngine() = default;
	JGameEngine(const JGameEngine&) = delete;
	JGameEngine& operator=(const JGameEngine&) = delete;
};
#define I_GameEngine JGameEngine::GetInstance()