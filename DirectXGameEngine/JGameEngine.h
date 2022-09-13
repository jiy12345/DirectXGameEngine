#pragma once
#include"stdafx.h"
#include "JTimer.h"
#include "JWriter.h"

class JGameEngine
{
public:
	JWriter m_Writer;
	bool	m_bGameRun = true;
private:
	bool engineInit();
	bool engineFrame();
	bool engineRender();
	bool engineRelease();
public:
	virtual bool init() { return true; };
	virtual bool frame() { return true; };
	virtual bool render() { return true; };
	virtual bool release() { return true; };
public:
	bool run();
};
#define I_GameEngine JGameEngine::GetInstance()