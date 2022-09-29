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
	m_rtCamera.Set({ 0, 0 }, { I_Window.m_rtClient.right, I_Window.m_rtClient.bottom });

	m_pObject = new JTestObject;
	m_pMapObject = new JTestObject;
	m_pMapObject->m_wstrTextureName = L"_RAINBOW.bmp";
	m_pMapObject->m_rtUV.Set({ 0, 0 }, { 1, 1 });
	m_pMapObject->m_rtArea.Set({ 0, 0 }, { 1024, 768 });
	m_pObject->init();
	m_pMapObject->init();

	m_pGunShots.resize(32);
	for (JSoundChannel*& curGunshot : m_pGunShots) {
		curGunshot = new JSoundChannel(L"Gun1.wav");
	}
	m_pBGM = new JSoundChannel(L"MyLove.mp3");

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
	m_pObject->frame();
	//m_pMapObject->frame();
	m_rtCamera.m_vLeftTop = m_pObject->m_rtArea.vCenter() - (JVector<2>{ I_Window.m_rtClient.right, I_Window.m_rtClient.bottom } / 2);
	return true;
}

bool Test::render()
{
	getCameraCoord(m_pMapObject->m_rtArea);
	getCameraCoord(m_pObject->m_rtArea);
	m_pMapObject->render();
	m_pObject->render();
	return true;
}

bool Test::release()
{
	m_pObject->release();
	m_pMapObject->release();
	I_Sound.stop(m_pBGM);
	for (JSoundChannel*& curGunshot : m_pGunShots) {
		I_Sound.stop(curGunshot);
	}
	m_pGunShots.clear();
	return true;
}

void Test::getCameraCoord(nCube<2>& rtArea)
{
	rtArea.m_vLeftTop -= m_rtCamera.m_vLeftTop;
}
