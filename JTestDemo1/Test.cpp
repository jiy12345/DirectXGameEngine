#include "Test.h"
#include "stdafx.h"
#include "JGameEngine.h"
#include "JTimer.h"

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
	I_Timer.init();
	return true;
}

bool Test::frame()
{
	I_Timer.frame();
	return true;
}

bool Test::render()
{
	I_Timer.render();
	return true;
}

bool Test::release()
{
	I_Timer.release();
	return true;
}
