#pragma once
#include "stdafx.h"
#include "JBaseObject.h"
class JTestObject : public JBaseObject
{
public:
	nCube<2>		m_rtUV;
	nCube<2>		m_rtArea;
public:
	float			m_fSpeed = 1000.0f;
public:
	bool			frame() override;
	virtual void	updateVertexBuffer() override;
public:
	nCube<2>		getNDC();
public:
	JTestObject() {
		m_wstrTextureName = L"../data/sprites/pilot.png";
		//m_rtUV.Set({ 24 / 811.0f, 0 / 988.0f }, { 22 / 811.0f + 0.05f, 15 / 988.0f + 0.05f });
		m_rtUV.Set({ 0 / 988.0f, 24 / 811.0f }, { 15 / 988.0f, 22 / 811.0f });
		// m_rtUV.Set({ 0, 0 }, { 1, 1 });
		
		m_rtArea.Set({ 0, 0 }, { m_rtUV.m_vSize[0]* 3000, m_rtUV.m_vSize[1] * 3000 });
	}
};

