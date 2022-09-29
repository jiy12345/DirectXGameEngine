#pragma once
#include "stdafx.h"
#include "JGameEngine.h"
#include "JTestObject.h"

class Test : public JGameEngine
{
	JTestObject* m_pObject;
	JTestObject* m_pMapObject;
	JSoundChannel* m_pBGM;
	std::vector<JSoundChannel*> m_pGunShots;
public:
	nCube<2> m_rtCamera;
public:
	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
public:
	void getCameraCoord(nCube<2>& rtArea);
};


