#define _CRT_SECURE_NO_WARNINGS
#include "Test.h"

#define WINDOW_SIZE_X 1024
#define WINDOW_SIZE_Y 768
#define WINDOW_NAME L"DirectXGameEngine"

int APIENTRY wWinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPWSTR		lpCmdLine,
	int			nCmdShow) {
#ifdef _DEBUG
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
#endif
	I_Window.setWindow(hInstance, WINDOW_NAME, WINDOW_SIZE_X, WINDOW_SIZE_Y);
	Test test;
	test.run();
#ifdef _DEBUG
	FreeConsole();
#endif
	return 0;
}

bool Test::init()
{
	m_pJBox = new JBox;
	m_pJBox->m_wstrTextureName = L"_RAINBOW.bmp";
	m_pJBox->m_rtUV.Set({ 0, 0 }, { 1, 1 });
	m_pJBox->init();

	m_pGunShots.resize(32);
	for (JSoundChannel*& curGunshot : m_pGunShots) {
		curGunshot = new JSoundChannel(L"Gun1.wav");
	}
	m_pBGM = new JSoundChannel(L"MyLove.mp3");

	I_Camera.m_vPosition = { 0, 0, -30 };
	I_Camera.m_vTarget = { 0, 0, 0 };
	I_Camera.m_fNearPlane = 1.0f;
	I_Camera.m_fFarPlane = 1000.0f;
	I_Camera.m_fovy = T_PI * 0.25f;
	I_Camera.m_Aspect = (float)I_Window.m_rtClient.right / (float)I_Window.m_rtClient.bottom;

	return true;
}

bool Test::frame()
{
	if (I_Input.GetKey(VK_HOME) == KEY_PUSH)
	{
		for (JSoundChannel*& curGunshot : m_pGunShots) {
			Sleep(10);
			I_Sound.playEffect(curGunshot, false);
		}
	}
	if (I_Input.GetKey(VK_INSERT) == KEY_PUSH)
	{
		I_Sound.play(m_pBGM, true);
	}
	if (I_Input.GetKey(VK_END) == KEY_PUSH)
	{
		I_Sound.stop(m_pBGM);
	}
	if (I_Input.GetKey(VK_F1) == KEY_PUSH)
	{
		I_Sound.pause(m_pBGM);
	}
	if (I_Input.GetKey(VK_F2) == KEY_PUSH)
	{
		I_Sound.resume(m_pBGM);
	}
	m_pJBox->frame();
	
	return true;
}

bool Test::render()
{
	m_pJBox->render();
	return true;
}

bool Test::release()
{
	m_pJBox->release();
	I_Sound.stop(m_pBGM);
	for (JSoundChannel*& curGunshot : m_pGunShots) {
		I_Sound.stop(curGunshot);
	}
	m_pGunShots.clear();
	return true;
}