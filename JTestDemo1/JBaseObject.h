#pragma once
#include "stdafx.h"
#include "JDevice.h"
#include "JShaderManager.h"
#include "JTextureManager.h"

struct SimpleVertex
{
	JVector<3> p;
	JVector<4> c;
	JVector<2> t;
};

class JBaseObject
{
public:
	std::wstring				m_wstrVSName = L"DefaultShapeMask.hlsl";
	std::wstring				m_wstrPSName = L"DefaultShapeMask.hlsl";
	std::string					m_strVSFuncName = "VS";
	std::string					m_strPSFuncName = "PS";
	std::wstring				m_wstrTextureName = L"_RAINBOW.bmp";
	ID3D11Buffer*				m_pVertexBuffer;
	ID3D11Buffer*				m_pIndexBuffer;
	ID3D11InputLayout*			m_pVertexLayout;
	std::vector<SimpleVertex>   m_VertexList;
	std::vector<DWORD>			m_IndexList;
public:
	void				setVSName(std::wstring wstrVSName);
	void				setPSName(std::wstring wstrPSName);
	void				setVSFuncName(std::string strVSFuncName);
	void				setPSFuncName(std::string strPSFuncName);
	void				setTextureName(std::wstring strTextureName);
public:
	virtual void		setVertexData();
	virtual void		setIndexData();
	virtual HRESULT		createVertexBuffer();
	virtual HRESULT		createIndexBuffer();
	virtual HRESULT     createVertexLayout();
	virtual void		updateVertexBuffer();
public:
	virtual bool		init();
	virtual bool		frame();
	virtual bool		render();
	virtual bool		release();
protected:
	bool				preRender();
	bool				postRender();
public:
	virtual				 ~JBaseObject();
};