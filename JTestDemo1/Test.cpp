#include "Test.h"

#define WINDOW_SIZE_X 1024
#define WINDOW_SIZE_Y 768
#define WINDOW_NAME L"DirectXGameEngine"

int APIENTRY wWinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPWSTR		lpCmdLine,
	int			nCmdShow) {

	I_Window.setWindow(hInstance, WINDOW_NAME, WINDOW_SIZE_X, WINDOW_SIZE_Y);
	Test test;
	test.run();

	return 0;
}

bool Test::init()
{
	m_pObject = new JBaseObject;
	m_pObject->init();

	m_pGunShot = new JSoundChannel(L"Gun1.wav");
	m_pBGM = new JSoundChannel(L"MyLove.mp3");

	return true;
}

bool Test::frame()
{
	if (I_Input.GetKey(VK_HOME) == KEY_PUSH)
	{
		I_Sound.playEffect(m_pGunShot, false);
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
	m_pObject->frame();
	return true;
}

bool Test::render()
{
	m_pObject->render();
	return true;
}

bool Test::release()
{
	m_pObject->release();
	I_Sound.stop(m_pBGM);
	I_Sound.stop(m_pGunShot);
	return true;
}
