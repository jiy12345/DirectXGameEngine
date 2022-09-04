#include "JWindow.h"
JWindow* g_pWindow = nullptr;
LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	_ASSERT(g_pWindow);
	return g_pWindow->msgProc(hWnd, message, wParam, lParam);
}

bool JWindow::setWindow(HINSTANCE hInst, const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{
	m_hInstance = hInst;
	WORD ret = registerWNDClass();

	return (!initInstance(szTitle, iWidth, iHeight)) ? false : true;
}

ATOM JWindow::registerWNDClass()
{
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance = m_hInstance;
	wcex.hbrBackground = CreateSolidBrush(RGB(7, 77, 7));
	wcex.lpszClassName = L"창";
	wcex.lpfnWndProc = WndProc;
	wcex.hCursor = LoadCursor(nullptr, IDC_UPARROW);
	return RegisterClassEx(&wcex);
}

BOOL JWindow::initInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{
	m_csStyle = WS_OVERLAPPEDWINDOW;

	RECT rc = { 0,0,iWidth , iHeight };
	AdjustWindowRect(&rc, m_csStyle, FALSE);

	HWND hWnd = CreateWindowW(
		L"창",
		szTitle,
		m_csStyle,
		0, 0,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr, nullptr,
		m_hInstance, nullptr);

	if (!hWnd) return FALSE;
	ShowWindow(hWnd, SW_SHOW);
	return TRUE;
}

bool JWindow::run()
{
	init();

	MSG msg = { 0, };
	while (WM_QUIT != msg.message)
	{
		// 장점 : 메세지큐에 메세지가 없어도 반환됨.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); // 메세지 번역
			DispatchMessage(&msg);  // 메세지 프로시져에 전달한다.
		}
		else
		{
			frame();
			render();
		}
	}
	release();

	return true;
}

void JWindow::centerWindow()
{
}

bool JWindow::init()
{
	return true;
}

bool JWindow::frame()
{
	return true;
}

bool JWindow::render()
{
	return true;
}

bool JWindow::release()
{
	return true;
}

LRESULT JWindow::msgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return  DefWindowProc(hWnd, message, wParam, lParam);
}

JWindow::JWindow()
{
	g_pWindow = this;
}
