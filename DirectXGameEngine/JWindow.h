#pragma once
#include"stdafx.h"

class JWindow
{
public:
	HINSTANCE			m_hInstance;
	HWND				m_hWnd;
	RECT				m_rtWindow;
	DWORD				m_csStyle;
public:
	bool				setWindow(HINSTANCE hInst, const WCHAR* szTitle, UINT iWidth = 1024, UINT iHeight = 768);
	ATOM				registerWNDClass();
	BOOL				initInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight);
	bool				run();
	void				centerWindow();
public:
	virtual bool		init();
	virtual bool		frame();
	virtual bool		render();
	virtual bool		release();
	virtual LRESULT		msgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	JWindow();
};

