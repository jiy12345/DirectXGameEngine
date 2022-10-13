#pragma once
#include"stdafx.h"
#include"JTimer.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

class JWriter : public JSingleton<JWriter>
{
	friend class JSingleton<JWriter>;
public:
	ID2D1Factory*			m_d2dFactory;
	IDWriteFactory*			m_pDWriteFactory;
	ID2D1RenderTarget*		m_d2dRT;
	IDWriteTextFormat*		m_pTextFormat;
	ID2D1SolidColorBrush*	m_pColorBrush;
	std::wstring			m_szDefaultText;
public:
	virtual bool			init();
	virtual bool			frame();
	virtual bool			render();
	virtual bool			release();
public:
	virtual HRESULT			createDXResource();
	virtual HRESULT			deleteDXResource();
public:
	bool					set(IDXGISurface1* dxgiSurface);
	bool					draw(float x, float y, std::wstring text, D2D1_COLOR_F color = { 0, 0, 0, 1 });
private:
	JWriter() {};
	~JWriter() = default;
	JWriter(const JWriter&) = delete;
	JWriter& operator=(const JWriter&) = delete;
};

#define I_Writer JWriter::GetInstance()