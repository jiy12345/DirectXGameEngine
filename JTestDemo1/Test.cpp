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
	m_pShader = new JShader;
	m_pShader->init();
	m_pShader->load(L"DefaultShapeMask.hlsl");
	return true;
}

bool Test::frame()
{
	m_pShader->frame();
	return true;
}

bool Test::render()
{
	m_pShader->render();
	return true;
}

bool Test::release()
{
	m_pShader->release();
	return true;
}
