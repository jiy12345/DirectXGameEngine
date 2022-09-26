#pragma once
#include "stdafx.h"
#include "JGameEngine.h"
#include "JBaseObject.h"

class Test : public JGameEngine
{
	JBaseObject* m_pObject;
	JSoundChannel* m_pBGM;
	JSoundChannel* m_pGunShot;
public:
	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};


