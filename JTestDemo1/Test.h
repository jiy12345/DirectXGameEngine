#pragma once
#include "stdafx.h"
#include "JGameEngine.h"
#include "JTestObject.h"

class Test : public JGameEngine
{
	JTestObject* m_pObject;
	JBaseObject* m_pMapObject;
	JSoundChannel* m_pBGM;
	std::vector<JSoundChannel*> m_pGunShots;
public:
	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};


