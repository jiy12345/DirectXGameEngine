#pragma once
#include "stdafx.h"
class JShader
{
public:
	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader*	m_pPS;
	ID3DBlob*			m_pVSCode = nullptr;
	ID3DBlob*			m_pPSCode = nullptr;
	ID3D11InputLayout*	m_pVertexLayout;
public:
	bool	init();
	bool	frame();
	bool	render();
	bool	release();

	HRESULT load(std::wstring name);
};