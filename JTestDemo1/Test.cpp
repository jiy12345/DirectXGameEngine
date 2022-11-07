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
	m_pJBox->init();

	m_pGunShots.resize(32);
	for (JSoundChannel*& curGunshot : m_pGunShots) {
		curGunshot = new JSoundChannel(L"Gun1.wav");
	}
	m_pBGM = new JSoundChannel(L"MyLove.mp3");

	I_Camera.m_vPosition = { 0, 0, -300 };
	I_Camera.m_vTarget = { 0, 0, 0 };

	if (m_FBXLoader.init())
	{
		m_FBXLoader.load("../data/fbx/SM_Rock.fbx");
	}

	for (int iObj = 0; iObj < m_FBXLoader.m_pDrawObjList.size(); iObj++)
	{
		JFbxObject* pObj = m_FBXLoader.m_pDrawObjList[iObj];
		pObj->init();
		pObj->m_cubeArea.m_vSize = { 1, 1, 1 };
	}

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
	I_Camera.setTarget(m_pJBox->m_cubeArea.m_vCenter);

	return true;
}

bool Test::render()
{
	if (I_Input.GetKey('V') == KEY_HOLD)
	{
		I_Device.m_pImmediateContext->RSSetState(JDXState::g_pDefaultRSWireFrame);
	}
	else {
		I_Device.m_pImmediateContext->RSSetState(JDXState::g_pDefaultRSSolid);
	}

	for (int iObj = 0; iObj < m_FBXLoader.m_pDrawObjList.size(); iObj++)
	{
		m_FBXLoader.m_pDrawObjList[iObj]->render();
	}

	//m_pJBox->render();
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