#pragma once
#include "stdafx.h"
#include "JBaseObject.h"

struct VS_CONSTANT_BUFFER
{
	JMatrix<4, 4>  m_matWorld;
	JMatrix<4, 4>  m_matView;
	JMatrix<4, 4>  m_matProj;
	float    x;
	float    y;
	float    fTimer = 0.0f;
	float    d;
};

class J3DObject: public JBaseObject
{
public:
	nCube<3>			m_cubeArea;
	float				m_fXAngle = 0.0f;
	float				m_fYAngle = 0.0f;
	float				m_fZAngle = 0.0f;
public:
	VS_CONSTANT_BUFFER  m_cbData;
	JMatrix<4, 4>		m_matWorld;
	JMatrix<4, 4>		m_matView;
	JMatrix<4, 4>		m_matProj;
public:
	ID3D11Buffer*	m_pConstantBuffer;
public:
	virtual HRESULT	CreateConstantBuffer();
	virtual void	UpdateConstantBuffer();
public:
	virtual bool	init() override;
	virtual bool	frame() override;
	virtual bool	render() override;
	virtual bool	release() override;
public:
	virtual void	setVertexData() override;
};

