#pragma once
#include "stdafx.h"
enum KeyState
{
	KEY_FREE = 0,
	KEY_UP,
	KEY_PUSH,
	KEY_HOLD,
};
class JInput : public JSingleton<JInput>
{
private:
	DWORD		m_dwKeyState[256];
public:
	POINT		m_ptPos;
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
public:
	DWORD  GetKey(DWORD dwKey);
private:
	JInput() {};
	~JInput() = default;
	JInput(const JInput&) = delete;
	JInput& operator=(const JInput&) = delete;
};
#define I_Input JInput::GetInstance()
