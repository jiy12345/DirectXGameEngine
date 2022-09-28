#pragma once
#include "stdafx.h"
#include "JBaseObject.h"
class JTestObject : public JBaseObject
{
public:
	nCube<2>		m_rtUV;
	nCube<2>		m_rtArea;
public:
	float			m_fSpeed;
public:
	bool			frame() override;
	virtual void	updateVertexBuffer() override;
public:
	nCube<2>		getNDC();
public:
	JTestObject() {
		m_rtUV.Set({ 0, 0 }, { 1, 1 });
		m_rtArea.Set({ 0, 0 }, { 100, 100 });
	}
};

