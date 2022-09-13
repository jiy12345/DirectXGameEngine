#pragma once
#include"stdafx.h"

class JGameEngine
{
public:
	bool m_bGameRun = true;
private:
	bool engineInit();
	bool engineFrame();
	bool engineRender();
	bool engineRelease();
public:
	bool run();
};
#define I_GameEngine JGameEngine::GetInstance()