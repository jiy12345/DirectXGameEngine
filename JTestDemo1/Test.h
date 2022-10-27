#pragma once
#include "stdafx.h"
#include "JGameEngine.h"
#include "J3DObject.h"

class Test : public JGameEngine
{
	JBaseObject* m_pMapObject;
	JSoundChannel* m_pBGM;
	std::vector<JSoundChannel*> m_pGunShots;

public:
	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};


