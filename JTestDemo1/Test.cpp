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
	m_Writer.init();
	IDXGISurface1* m_pBackBuffer;
	I_Device.m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1),
		(void**)&m_pBackBuffer);
	m_Writer.set(m_pBackBuffer);
	return true;
}

bool Test::frame()
{
	m_Writer.frame();
	return true;
}

bool Test::render()
{
	m_Writer.render();
	return true;
}

bool Test::release()
{
	m_Writer.release();
	return true;
}
