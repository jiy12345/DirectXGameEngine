#pragma once
#include "stdafx.h"

struct SimpleVertex
{
	JVector<3> p;
	JVector<4> c;
	JVector<2> t;
};

class JShader
{
public:
	ID3D11VertexShader*			m_pVS;
	ID3D11PixelShader*			m_pPS;
	ID3DBlob*					m_pVSCode = nullptr;
	ID3DBlob*					m_pPSCode = nullptr;
	ID3D11Buffer*				m_pVertexBuffer;
	ID3D11Buffer*				m_pIndexBuffer;
	ID3D11InputLayout*			m_pVertexLayout;
	std::vector<SimpleVertex>   m_VertexList;
	std::vector<DWORD>			m_IndexList;
public:
	bool	init();
	bool	frame();
	bool	render();
	bool	release();
public:
	void	setVertexData();
	void	setIndexData();
	HRESULT createVertexBuffer();
	HRESULT createIndexBuffer();
	HRESULT load(std::wstring name);
};