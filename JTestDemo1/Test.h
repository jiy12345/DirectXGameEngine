#pragma once
#include "stdafx.h"
#include "JGameEngine.h"
#include "JBox.h"

class Test : public JGameEngine
{
	JBox* m_pJBox;
	JSoundChannel* m_pBGM;
	std::vector<JSoundChannel*> m_pGunShots;

public:
	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};


