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

	return true;
}

bool Test::frame()
{
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
	return true;
}
