#pragma once
#include "stdafx.h"
#include "JWriter.h"
#include "JSoundManager.h"
#include "JSpriteManager.h"
#include "JCamera.h"

class JGameEngine
{
public:
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
	virtual HRESULT createDXResource();
	virtual HRESULT deleteDXResource();
public:
	bool run();
};
#define I_GameEngine JGameEngine::GetInstance()