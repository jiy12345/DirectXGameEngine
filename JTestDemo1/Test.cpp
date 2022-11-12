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
	m_pGunShots.resize(32);
	for (JSoundChannel*& curGunshot : m_pGunShots) {
		curGunshot = new JSoundChannel(L"Gun1.wav");
	}
	m_pBGM = new JSoundChannel(L"MyLove.mp3");

	I_Camera.m_vPosition = { 0, 0, -300 };
	I_Camera.m_vTarget = { 0, 0, 0 };

	JFbxLoader* pFbxLoaderC = new JFbxLoader;
	if (pFbxLoaderC->init())
	{
		pFbxLoaderC->load("../data/fbx/MultiCameras.fbx");
	}
	m_fbxList.push_back(pFbxLoaderC);
	
	for (auto fbx : m_fbxList)
	{
		for (int iObj = 0; iObj < fbx->m_pDrawObjList.size(); iObj++)
		{
			JFbxObject* pObj = fbx->m_pDrawObjList[iObj];
			pObj->init();
		}
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

	for (int iModel = 0; iModel < m_fbxList.size(); iModel++)
	{
		for (int iObj = 0; iObj < m_fbxList[iModel]->m_pDrawObjList.size(); iObj++)
		{
			JFbxObject* pObj = m_fbxList[iModel]->m_pDrawObjList[iObj];
			JMatrix<4, 4> matWorld;
			matWorld[3][0] = 100 * iModel;
			pObj->render();
		}
	}

	return true;
}

bool Test::release()
{
	I_Sound.stop(m_pBGM);
	for (JSoundChannel*& curGunshot : m_pGunShots) {
		I_Sound.stop(curGunshot);
	}
	m_pGunShots.clear();
	return true;
}