#pragma once
#include "stdafx.h"
#include "JDevice.h"
#include "JShaderManager.h"
#include "JTextureManager.h"
#include "JSpriteManager.h"
#include "JCamera.h"

#define IS_NOT_SPRITE -1

struct SimpleVertex
{
	JVector<3> p;
	JVector<3> n;
	JVector<4> c;
	JVector<2> t;
public:
	SimpleVertex() {};
	SimpleVertex(JVector<3> p, JVector<4> c, JVector<2> t) {
		this->p = p;
		this->c = c;
		this->t = t;
	};
	SimpleVertex(JVector<3> p, JVector<3> n, JVector<4> c, JVector<2> t) {
		this->p = p;
		this->n = n;
		this->c = c;
		this->t = t;
	};
};

class JBaseObject
{
public:
	int 					m_curSprite = IS_NOT_SPRITE;
	int						m_iIndexOfSprite = 0;
	float					m_fStep;
	float					m_fEffectTimer = 0.0f;
	std::vector<JSprite>*	m_vSpriteInfo;
public:
	nCube<2>				m_rtUV;
	nCube<2>				m_rtArea;
public:
	float					m_fSpeed = 500.0f;
public:
	std::wstring				m_wstrVSName = L"DefaultVertexShader.hlsl";
	std::wstring				m_wstrPSName = L"DefaultPixelShader.hlsl";
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
	virtual void		updateUVCoord();
	virtual void		updateVertexBuffer();
public:
	virtual bool		init();
	virtual bool		frame();
	virtual bool		render();
	virtual bool		release();
protected:
	virtual bool		preRender();
	virtual bool		postRender();
public:
	JBaseObject() {
		init();
	};
	virtual				 ~JBaseObject();
};